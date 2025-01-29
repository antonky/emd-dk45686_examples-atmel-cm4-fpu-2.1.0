/*
 *
 * Copyright (c) [2020] by InvenSense, Inc.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/* Driver */
#include "imu/inv_imu_driver_advanced.h"

/* Utils */
#include "Invn/EmbUtils/RingBuffer.h"

/* Frontend */
#include "frontend.h"

/* Magnetometer drivers */
#include "Ak0991x/Ak0991x.h"

/* Board drivers */
#include "system_interface.h"

/* std */
#include <stdio.h>

/*
 * This example showcases how to integrate and feed a 6 or 9 axis fusion algorithm from IMU
 * It retrieves AG sensor data at 400Hz from the FIFO using the advanced driver.
 * It allows to configure AG in either Low-Power or Low-Noise mode,
 * with the possibility to enable IMU high-resolution mode.
 * Magnetometer data can be retrieved from host MCU through its own I2C to feed AGM fusion algorithm
 * to output 9-axis quaternion.
 * A sanity test can be requested from UART to validate algorithm integration with test vector.
 */

/*
 * Select communication link between SmartMotion and IMU.
 * SPI4: `UI_SPI4`
 * I2C:  `UI_I2C`
 */
#define SERIF_TYPE UI_SPI4

/*
 * Mag output data rate
 */
#define MAG_ODR_US 10000 /* 100 Hz */

/*
 * Period after which the algo biases will be saved in flash
 */
#define BIASES_SAVE_PERIOD_US 3600000000ULL /* 1 h */

/* Driver structures for IMU and mag */
static inv_imu_device_t imu_dev; /* IMU driver structure */
static inv_ak0991x_t    ak_driver; /* Ak0991x driver structure */

/* Variables required for the example logic */
static uint8_t  fifo_data[FIFO_MIRRORING_SIZE]; /* Memory where to store FIFO data */
static uint8_t  mag_init_successful; /* Indicates mag initialized properly */
static uint32_t imu_odr_us; /* Contains the current IMU's ODR */
static uint32_t imu_sample_count; /* Used to trigger mag acquisition */
static uint8_t  cal_save_en; /* Indicates if calibration shall be saved in flash */

/* Interrupt flags */
static volatile int int1_flag; /* INT1 is asserted */
static volatile int int_mag_flag; /* Mag INT is asserted */

/* 
 * Variables to collect timestamp, taken in interrupt handler
 *  * Use a buffer for IMU as we have a FIFO which possibly contains multiple packet
 *  * Use a variable for mag as we read data from register
 */
RINGBUFFER_VOLATILE(timestamp_buffer_imu, 64, uint64_t);
volatile uint64_t timestamp_mag;

/* Variables required for AGM algo */
static InvnAlgoAGMStruct agm;
static InvnAlgoAGMInput  input;
static InvnAlgoAGMOutput output;

/*
 * Magnetometer mounting matrix to align AK09915 with IMU reference frame.
 * Coefficients are coded as Q30 integer.
 */
#if defined(USE_EVB)
static int32_t mag_matrix[9] = { (1 << 30), 0, 0, 0, (1 << 30), 0, 0, 0, (1 << 30) }; /* for EVB */
#elif defined(USE_DB)
static int32_t mag_matrix[9] = { -(1 << 30), 0, 0, 0, -(1 << 30), 0, 0, 0, (1 << 30) }; /* for DB */
#else
static int32_t mag_matrix[9] = { 0, (1 << 30), 0, -(1 << 30), 0, 0, 0, 0, (1 << 30) }; /* for DK */
#endif

/* Crystal on SmartMotion board is at 32768Hz, not 32000Hz, so is RTC/CLKIN input to IMU,
 * so if CLKIN is enabled, IMU sensor ODR will be shifted accordingly as ODR is indicated
 * for 32000Hz CLKIN input
 */
#define ODR_WITH_CLKIN_32768HZ(odr_us) (uint32_t)(((odr_us)*32000) / 32768)

/* Accel, Gyro and Mag biases */
static int32_t acc_bias[3];
static int32_t gyr_bias[3];
static int32_t mag_bias[3];

/* Accel, Gyro and Mag accuracies */
static int32_t acc_accuracy;
static int32_t gyr_accuracy;
static int32_t mag_accuracy;

/* Static functions definition */
static int  setup_mcu();
static int  setup_imu();
static int  setup_mag();
static int  init_agm_algo();
static int  reset_vars();
static void int_cb(void *context, unsigned int int_num);
static void sensor_event_cb(inv_imu_sensor_event_t *event);
static int  get_mag_data();
static int  load_calibration();
static int  save_calibration();
static int  print_current_biases();
static int  on_command_received_cb(inv_commands cmd);
static void apply_mounting_matrix(const int32_t matrix[9], int32_t raw[3]);

/* Main function implementation */
int main(void)
{
	int rc = 0;

	/* Setup MCU peripherals */
	rc |= setup_mcu();
	SI_CHECK_RC(rc);

	/* Setup message facility (log) and set callback to be called when a command is received */
	init_frontend(on_command_received_cb);

	INV_MSG(INV_MSG_LEVEL_INFO, "###");
	INV_MSG(INV_MSG_LEVEL_INFO, "### Example Algo AGM");
	INV_MSG(INV_MSG_LEVEL_INFO, "###");

	/* Initialize variables */
	cal_save_en = 1;

	/* Initialize and configure IMU */
	rc |= setup_imu();
	SI_CHECK_RC(rc);

	/* Initialize and configure mag */
	rc |= setup_mag();
	mag_init_successful = rc < 0 ? 0 : 1;
	rc                  = 0; /* reset `rc` as we wouldn't consider an error here to be blocking */

	/* Initialize algo */
	rc |= load_calibration();
	rc |= init_agm_algo();
	SI_CHECK_RC(rc);

	/* Reset timestamp and interrupt flags */
	rc |= reset_vars();
	SI_CHECK_RC(rc);

	do {
		/* Check IMU flag */
		if (int1_flag) {
			inv_imu_int_state_t int_state;

			si_disable_irq();
			int1_flag = 0; /* Clear interrupt flag */
			si_enable_irq();

			/* Read interrupt status */
			rc |= inv_imu_get_int_status(&imu_dev, INV_IMU_INT1, &int_state);
			SI_CHECK_RC(rc);

			/* Read and process FIFO data */
			if (int_state.INV_FIFO_THS) {
				uint16_t fifo_count = 0;

				/* Read data from FIFO */
				rc |= inv_imu_adv_get_data_from_fifo(&imu_dev, fifo_data, &fifo_count);
				SI_CHECK_RC(rc);

				/* Trigger mag acquisition in sync with IMU data */
				if (mag_init_successful) {
					uint32_t mag_acq_ths = (uint32_t)MAG_ODR_US / imu_odr_us;

					imu_sample_count += fifo_count;

					if (imu_sample_count >= mag_acq_ths) {
						/* 
						 * The `imu_sample_count` should always be incremented by one, except if 
						 * the firmware was busy and several packets were pushed in the FIFO (should 
						 * not happen in mission mode). 
						 * To get the proper ODR in average, subtract the `mag_acq_ths` (the
						 * following interrupt will occur slightly sooner to recover). If the
						 * difference exceed `mag_acq_ths / 2`, don't try to recover and reset
						 * the logic.
						 * This could result in a jitter on mag ODR up to 50%. 
						 */
						if (imu_sample_count - mag_acq_ths <= (uint32_t)(mag_acq_ths / 2)) {
							imu_sample_count -= mag_acq_ths;
						} else {
							INV_MSG(INV_MSG_LEVEL_WARNING, "Resetting mag acquisition logic");
							imu_sample_count = 0;
						}

						/* Trigger mag acquisition only if it is not already ongoing */
						if (!ak_driver.compass_en) {
							rc |= inv_ak0991x_enable_sensor(&ak_driver, 1);
							SI_CHECK_RC(rc);
						}
					}
				}

				/* Process FIFO data */
				rc |= inv_imu_adv_parse_fifo_data(&imu_dev, fifo_data, fifo_count);
				SI_CHECK_RC(rc);

				/*
				 * The FIFO threshold condition is re-evaluated after a FIFO read operation.
				 * If an interrupt is asserted between FIFO count read and FIFO data read, one
				 * packet will remain in the FIFO after the read operation, therefore asserting an
				 * additional interrupt. Once we parsed all packets, if we serviced all pending
				 * interrupt (`int1_flag` is 0) and if a timestamp remains in the buffer, then we
				 * can safely clear it as it doesn't match with a new sample but simply with a
				 * re-evaluation of the FIFO threshold condition.
				 */
				si_disable_irq();
				if (int1_flag == 0)
					RINGBUFFER_VOLATILE_CLEAR(&timestamp_buffer_imu);
				si_enable_irq();
			}
			/* 
		 * Check AKM flag
		 * Use `else if` instead of `if` to give priority to IMU's interrupt. 
		 * In case the processing of the IMU data takes longer than 1 ODR, both IMU and AKM 
		 * interrupt flag might be set. Since IMU's ODR is faster or equal to AKM's ODR, 
		 * let's process IMU first by restarting the loop. AKM will be processed in the 
		 * next iteration.
		 */
		} else if (mag_init_successful && int_mag_flag) {
			si_disable_irq();
			int_mag_flag = 0;
			si_enable_irq();

			/* Read and process mag data */
			rc = get_mag_data();
			SI_CHECK_RC(rc);
		}

		rc |= check_received_command();
	} while (rc == 0);

	return rc;
}

/* Initializes MCU peripherals. */
static int setup_mcu()
{
	int rc = 0;

	rc |= si_board_init();

	/* Configure GPIO to call `int_cb` when INT1 is asserted */
	rc |= si_init_gpio_int(SI_GPIO_INT1, int_cb);

	/* Configure GPIO to call `int_cb` when mag's INT is asserted */
	rc |= si_init_gpio_int(SI_GPIO_INT_MAG, int_cb);

	/* Init timer peripheral for sleep and get_time */
	rc |= si_init_timers();

	/* Initialize serial interface between MCU and IMU */
	rc |= si_io_imu_init(SERIF_TYPE);

#if INV_IMU_CLKIN_SUPPORTED
	/* When CLKIN is enabled, need to feed CLKIN pin with 32768Hz RTC from SmartMotion */
	rc |= si_init_clkin();
#endif

	rc |= si_flash_storage_init();

	return rc;
}

/* Initializes IMU device and apply configuration. */
static int setup_imu()
{
	int                       rc = 0;
	inv_imu_int_pin_config_t  int_pin_config;
	inv_imu_int_state_t       int_config;
	inv_imu_adv_fifo_config_t fifo_config;
	inv_imu_adv_var_t *       e = (inv_imu_adv_var_t *)imu_dev.adv_var;

	/* Init transport layer */
	imu_dev.transport.read_reg   = si_io_imu_read_reg;
	imu_dev.transport.write_reg  = si_io_imu_write_reg;
	imu_dev.transport.serif_type = SERIF_TYPE;
	imu_dev.transport.sleep_us   = si_sleep_us;

	/* Init sensor event callback */
	e->sensor_event_cb = sensor_event_cb;

	/* In SPI, configure slew-rate to prevent bus corruption on DK-SMARTMOTION-REVG */
	if (imu_dev.transport.serif_type == UI_SPI3 || imu_dev.transport.serif_type == UI_SPI4) {
		drive_config0_t drive_config0;
		drive_config0.pads_spi_slew = DRIVE_CONFIG0_PADS_SPI_SLEW_TYP_10NS;
		rc |= inv_imu_write_reg(&imu_dev, DRIVE_CONFIG0, 1, (uint8_t *)&drive_config0);
		SI_CHECK_RC(rc);
		si_sleep_us(2); /* Takes effect 1.5 us after the register is programmed */
	}

	rc |= inv_imu_adv_init(&imu_dev);
	SI_CHECK_RC(rc);

	/*
	 * Configure interrupts pins
	 * - Polarity High
	 * - Pulse mode
	 * - Push-Pull drive
	 */
	int_pin_config.int_polarity = INTX_CONFIG2_INTX_POLARITY_HIGH;
	int_pin_config.int_mode     = INTX_CONFIG2_INTX_MODE_PULSE;
	int_pin_config.int_drive    = INTX_CONFIG2_INTX_DRIVE_PP;
	rc |= inv_imu_set_pin_config_int(&imu_dev, INV_IMU_INT1, &int_pin_config);
	SI_CHECK_RC(rc);

	/* Interrupts configuration */
	memset(&int_config, INV_IMU_DISABLE, sizeof(int_config));
	int_config.INV_FIFO_THS = INV_IMU_ENABLE;
	rc |= inv_imu_set_config_int(&imu_dev, INV_IMU_INT1, &int_config);
	SI_CHECK_RC(rc);

#if INV_IMU_CLKIN_SUPPORTED
	/* CLKIN configuration */
	rc |= inv_imu_adv_set_int2_pin_usage(&imu_dev, IOC_PAD_SCENARIO_OVRD_INT2_CFG_OVRD_VAL_CLKIN);
	rc |= inv_imu_adv_enable_clkin_rtc(&imu_dev);
	SI_CHECK_RC(rc);
#endif

	/* FIFO configuration */
	rc |= inv_imu_adv_get_fifo_config(&imu_dev, &fifo_config);
	SI_CHECK_RC(rc);
	fifo_config.base_conf.gyro_en    = 1;
	fifo_config.base_conf.accel_en   = 1;
	fifo_config.base_conf.hires_en   = 1;
	fifo_config.base_conf.fifo_wm_th = 1;
	fifo_config.base_conf.fifo_mode  = FIFO_CONFIG0_FIFO_MODE_SNAPSHOT;
	fifo_config.tmst_fsync_en        = INV_IMU_ENABLE;
	fifo_config.fifo_wr_wm_gt_th     = FIFO_CONFIG2_FIFO_WR_WM_EQ_OR_GT_TH;
	rc |= inv_imu_adv_set_fifo_config(&imu_dev, &fifo_config);
	SI_CHECK_RC(rc);

	/* Set ODR */
	rc |= inv_imu_set_accel_frequency(&imu_dev, ACCEL_CONFIG0_ACCEL_ODR_400_HZ);
	rc |= inv_imu_set_gyro_frequency(&imu_dev, GYRO_CONFIG0_GYRO_ODR_400_HZ);
	imu_odr_us = 2500;
	SI_CHECK_RC(rc);

	/* Set BW = ODR/4 */
	rc |= inv_imu_set_accel_ln_bw(&imu_dev, IPREG_SYS2_REG_131_ACCEL_UI_LPFBW_DIV_4);
	rc |= inv_imu_set_gyro_ln_bw(&imu_dev, IPREG_SYS1_REG_172_GYRO_UI_LPFBW_DIV_4);
	SI_CHECK_RC(rc);

	/* Enable sensors */
	rc |= inv_imu_adv_enable_accel_ln(&imu_dev);
	rc |= inv_imu_adv_enable_gyro_ln(&imu_dev);
	SI_CHECK_RC(rc);

	/* Discard all samples until both accel and gyro are up and running */
	si_sleep_us(GYR_STARTUP_TIME_US);

	INV_MSG(INV_MSG_LEVEL_INFO, "IMU successfully initialized");

	return rc;
}

static int setup_mag()
{
	int                      rc = 0;
	uint8_t                  whoami;
	struct inv_ak0991x_serif akm_serif;

	akm_serif.read_reg  = si_io_akm_read_reg;
	akm_serif.write_reg = si_io_akm_write_reg;
	akm_serif.max_read  = 64;
	akm_serif.max_write = 64;
	rc |= si_io_akm_init(&akm_serif);
	SI_CHECK_RC(rc);

	/* Reset Ak09915 driver states */
	inv_ak0991x_reset_states(&ak_driver, &akm_serif);

	/* Init ak09915 device */
	rc |= inv_ak0991x_soft_reset(&ak_driver);
	if (rc != INV_ERROR_SUCCESS) {
		/* 
		 * Print error and return `rc` but do not stop execution.
		 * Error will be handled by caller. 
		 */
		INV_MSG(INV_MSG_LEVEL_ERROR, "Failed to initialize Ak09915");
		return rc;
	}

	/* Check WHOAMI */
	rc |= inv_ak0991x_get_whoami(&ak_driver, &whoami);
	SI_CHECK_RC(rc);

	if (whoami != AK0991x_COMPANY_ID) {
		INV_MSG(INV_MSG_LEVEL_ERROR,
		        "Wrong WHOAMI for Mag device (read 0x%02x while expecting 0x%02x)", whoami,
		        AK0991x_COMPANY_ID);
		rc |= INV_IMU_ERROR;
	}
	SI_CHECK_RC(rc);

	/* register sensitivity adjustment values */
	rc |= inv_ak0991x_retrieve_asa_values(&ak_driver);
	SI_CHECK_RC(rc);

	INV_MSG(INV_MSG_LEVEL_INFO, "Mag (AK09915) successfully initialized");

	return rc;
}

static int init_agm_algo(void)
{
	int               rc = 0;
	InvnAlgoAGMConfig config;

	memset(&input, 0, sizeof(input));
	memset(&output, 0, sizeof(output));
	memset(&config, 0, sizeof(config));

	rc |= invn_algo_agm_generate_config(&config, INVN_ALGO_AGM_MOBILE);

	/* FSR configuration */
	config.acc_fsr = 32;
	config.gyr_fsr = 4000;

	/* ODR configuration */
#if INV_IMU_CLKIN_SUPPORTED
	config.acc_odr_us = ODR_WITH_CLKIN_32768HZ(imu_odr_us);
	config.gyr_odr_us = ODR_WITH_CLKIN_32768HZ(imu_odr_us);
#else
	config.acc_odr_us = imu_odr_us;
	config.gyr_odr_us = imu_odr_us;
#endif

	/* Temperature sensor configuration */
	config.temp_sensitivity = (int32_t)((int64_t)((int64_t)1 << 30) / 128); // high-res;
	config.temp_offset      = 25 << 16;

	if (mag_init_successful) {
		/* Mag configuration */
		config.mag_sc_q16 = 9830; //0.15
		config.mag_odr_us = 10000; // 100Hz
	}

	/* Biases configuration */
	config.acc_bias_q16 = acc_bias;
	config.gyr_bias_q16 = gyr_bias;
	config.acc_accuracy = acc_accuracy;
	config.gyr_accuracy = gyr_accuracy;
	if (mag_init_successful) {
		config.mag_bias_q16 = mag_bias;
		config.mag_accuracy = mag_accuracy;
	}

	/* Initialize algorithm */
	rc |= invn_algo_agm_init(&agm, &config);

	if (rc == 0)
		INV_MSG(INV_MSG_LEVEL_INFO, "Algo AGM %s successfully initialized",
		        invn_algo_agm_version());

	return rc;
}

static int reset_vars()
{
	int     rc = 0;
	int16_t raw_mag[3];

	/* Clear IMU related variables */
	si_disable_irq();
	RINGBUFFER_VOLATILE_CLEAR(&timestamp_buffer_imu);
	int1_flag        = 0;
	imu_sample_count = 0;
	si_enable_irq();

	/* Flush FIFO to make sure there is no old data */
	rc |= inv_imu_flush_fifo(&imu_dev);
	SI_CHECK_RC(rc);

	/* Clear mag-related variables */
	si_disable_irq();
	timestamp_mag = 0;
	int_mag_flag  = 0;
	si_enable_irq();

	/* Read AK09915 data to make sure it is cleared and ready for next acquisition */
	rc |= inv_ak0991x_poll_data(&ak_driver, raw_mag);
	if (rc == 1) /* Indicates mag is not enabled, not an issue in this context */
		rc = 0;
	SI_CHECK_RC(rc);

	return rc;
}

static void int_cb(void *context, unsigned int int_num)
{
	(void)context;

	uint64_t timestamp = si_get_time_us();

	if (int_num == SI_GPIO_INT1) {
		int1_flag = 1;
		if (!RINGBUFFER_VOLATILE_FULL(&timestamp_buffer_imu))
			RINGBUFFER_VOLATILE_PUSH(&timestamp_buffer_imu, &timestamp);
	} else if (int_num == SI_GPIO_INT_MAG) {
		int_mag_flag  = 1;
		timestamp_mag = timestamp;
	}
}

static void sensor_event_cb(inv_imu_sensor_event_t *event)
{
	uint64_t        time_us             = 0;
	uint64_t        last_time_us        = 0;
	static uint16_t last_fifo_timestamp = 0;

	/* Retrieve timestamp from interrupt handler */
	si_disable_irq();
	if (!RINGBUFFER_VOLATILE_EMPTY(&timestamp_buffer_imu))
		RINGBUFFER_VOLATILE_POP(&timestamp_buffer_imu, &time_us);
	si_enable_irq();

	/*
	 * If no timestamp has been retrieved from interrupt handler (e.g. time_us == 0), then
	 * reconstruct the expected time using time from FIFO packet.
	 * This can happen if the firmware is busy, for instance while writing biases into flash.
	 */
	if (time_us == 0) {
		uint64_t dt_fifo = event->timestamp_fsync > last_fifo_timestamp ?
                               event->timestamp_fsync - last_fifo_timestamp :
                               event->timestamp_fsync + (UINT16_MAX + 1) - last_fifo_timestamp;
		time_us          = last_time_us + dt_fifo;
		INV_MSG(INV_MSG_LEVEL_WARNING,
		        "No timestamp available in buffer. Using delta time from FIFO: %llu us", dt_fifo);
	}
	last_time_us        = time_us;
	last_fifo_timestamp = event->timestamp_fsync;

	/* Extracts raw data from FIFO data */
	/* converts raw data (FSR g = 1<<15) to algo input format (FSR g = 1<<19) */
	input.mask = 0;

	if (event->sensor_mask & (1 << INV_SENSOR_ACCEL)) {
		input.sRacc_data[0] = event->accel[0] << 4 | event->accel_high_res[0];
		input.sRacc_data[1] = event->accel[1] << 4 | event->accel_high_res[1];
		input.sRacc_data[2] = event->accel[2] << 4 | event->accel_high_res[2];
		input.mask |= INVN_ALGO_AGM_INPUT_MASK_ACC;
	}

	if (event->sensor_mask & (1 << INV_SENSOR_GYRO)) {
		input.sRgyr_data[0] = event->gyro[0] << 4 | event->gyro_high_res[0];
		input.sRgyr_data[1] = event->gyro[1] << 4 | event->gyro_high_res[1];
		input.sRgyr_data[2] = event->gyro[2] << 4 | event->gyro_high_res[2];
		input.mask |= INVN_ALGO_AGM_INPUT_MASK_GYR;
	}

	if (event->sensor_mask & (1 << INV_SENSOR_TEMPERATURE))
		input.sRtemp_data = event->temperature;
	else
		input.sRtemp_data = 0;

	input.sRimu_time_us = time_us;

	/* Process the AGM Algo */
	invn_algo_agm_process(&agm, &input, &output);

	if (input.mask) {
		save_calibration();

		/* Notify data to frontend for print */
		notify_data(input.sRimu_time_us, &input, &output);
	}
}

static int get_mag_data()
{
	int      rc = 0;
	int16_t  raw_mag[3];
	uint64_t time_us;

	si_disable_irq();
	time_us = timestamp_mag;
	si_enable_irq();

	/* Read Ak09915 data */
	rc = inv_ak0991x_poll_data(&ak_driver, raw_mag);
	if (rc != 0)
		return rc;

	input.sRmag_data[0] = (int32_t)raw_mag[0];
	input.sRmag_data[1] = (int32_t)raw_mag[1];
	input.sRmag_data[2] = (int32_t)raw_mag[2];
	input.sRmag_time_us = time_us;
	input.mask          = INVN_ALGO_AGM_INPUT_MASK_MAG;

	/*
	 * Apply the mounting matrix configuration to the mag data polled
	 */
	apply_mounting_matrix(mag_matrix, input.sRmag_data);

	invn_algo_agm_process(&agm, &input, &output);

	/* Notify data to frontend for print */
	notify_data(input.sRmag_time_us, &input, &output);

	return rc;
}

static int load_calibration(void)
{
	int     rc = 0;
	uint8_t data[84];

	/* Retrieve bias stored in NV memory */
	if (cal_save_en && si_flash_storage_read(data) == 0) {
		/* Biases found in flash */
		uint8_t idx = 0;

		/* Fill `acc_bias`, `gyr_bias` and `mag_bias` with data from flash */
		memcpy(acc_bias, &data[idx], sizeof(acc_bias[0]) * 3);
		idx += sizeof(acc_bias[0]) * 3;
		memcpy(gyr_bias, &data[idx], sizeof(gyr_bias[0]) * 3);
		idx += sizeof(gyr_bias[0]) * 3;
		memcpy(mag_bias, &data[idx], sizeof(mag_bias[0]) * 3);

		/* Notify user */
		INV_MSG(INV_MSG_LEVEL_INFO, "Loading calibration from flash:");
		rc |= print_current_biases();

		/* Configure accuracies for known biases */
		acc_accuracy = 3;
		gyr_accuracy = 2;
		mag_accuracy = 1;
	} else {
		/* No biases found in flash, or `save_calibration` is false */
		memset(acc_bias, 0, sizeof(acc_bias));
		memset(gyr_bias, 0, sizeof(gyr_bias));
		memset(mag_bias, 0, sizeof(mag_bias));
		acc_accuracy = 0;
		gyr_accuracy = 0;
		mag_accuracy = 0;
	}

	return rc;
}

static int save_calibration(void)
{
	int             rc           = 0;
	static uint64_t last_save_us = 0;
	uint64_t        current_us   = si_get_time_us();

	/* Copy biases in static variables */
	memcpy(acc_bias, output.acc_bias_q16, sizeof(output.acc_bias_q16));
	memcpy(gyr_bias, output.gyr_bias_q16, sizeof(output.gyr_bias_q16));
	memcpy(mag_bias, output.mag_bias_q16, sizeof(output.mag_bias_q16));

	/* 
	 * If calibration save is enabled and
	 * no biases have been saved so far, or they are older than a predefined period 
	 */
	if (cal_save_en && (last_save_us == 0 || current_us - last_save_us >= BIASES_SAVE_PERIOD_US)) {
		/* 
		 * Will be saved only if all accuracies are 3, ignoring mag if it wasn't successfully
		 * initialized
		 */
		int save_condition = (output.acc_accuracy_flag == 3) && (output.gyr_accuracy_flag == 3) &&
		                     ((mag_init_successful == 0) || (output.mag_accuracy_flag == 3));

		if (save_condition) {
			/* 
			 * With this configuration, the bias can be stored up to 186 iterations in flash 
			 * before erase sector. The erase procedure with the first write, can take up to 250 ms.
			 * In this example, the erase is done dynamically (when needed).
			 */
			uint8_t data[84] = { 0 };
			uint8_t idx      = 0;

			memcpy(&data[idx], acc_bias, sizeof(acc_bias));
			idx += sizeof(acc_bias);
			memcpy(&data[idx], gyr_bias, sizeof(gyr_bias));
			idx += sizeof(gyr_bias);
			memcpy(&data[idx], mag_bias, sizeof(mag_bias));

			INV_MSG(INV_MSG_LEVEL_INFO, "Saving calibration in flash:");
			rc |= print_current_biases();

			rc |= si_flash_storage_write(data);
			last_save_us = current_us;
		}
	}

	return rc;
}

static int print_current_biases()
{
	INV_MSG(INV_MSG_LEVEL_INFO, "   - Accel: [%f %f %f] g", (float)acc_bias[0] / (1 << 16),
	        (float)acc_bias[1] / (1 << 16), (float)acc_bias[2] / (1 << 16));

	INV_MSG(INV_MSG_LEVEL_INFO, "   - Gyro:  [%f %f %f]dps", (float)gyr_bias[0] / (1 << 16),
	        (float)gyr_bias[1] / (1 << 16), (float)gyr_bias[2] / (1 << 16));

	INV_MSG(INV_MSG_LEVEL_INFO, "   - Mag:   [%f %f %f]uT", (float)mag_bias[0] / (1 << 16),
	        (float)mag_bias[1] / (1 << 16), (float)mag_bias[2] / (1 << 16));

	return 0;
}

static void apply_mounting_matrix(const int32_t matrix[9], int32_t raw[3])
{
	unsigned i;
	int64_t  data_q30[3];

	for (i = 0; i < 3; i++) {
		data_q30[i] = ((int64_t)matrix[3 * i + 0] * raw[0]);
		data_q30[i] += ((int64_t)matrix[3 * i + 1] * raw[1]);
		data_q30[i] += ((int64_t)matrix[3 * i + 2] * raw[2]);
	}
	raw[0] = (int32_t)(data_q30[0] >> 30);
	raw[1] = (int32_t)(data_q30[1] >> 30);
	raw[2] = (int32_t)(data_q30[2] >> 30);
}

/* Get command from user through UART */
static int on_command_received_cb(inv_commands cmd)
{
	int rc = 0;

	switch (cmd) {
	case RESET_AGM:
		INV_MSG(INV_MSG_LEVEL_INFO, "Resetting AGM algo and biases.");
		/* clear biases and accuracy */
		memset(acc_bias, 0, sizeof(acc_bias));
		memset(gyr_bias, 0, sizeof(gyr_bias));
		memset(mag_bias, 0, sizeof(mag_bias));
		acc_accuracy = 0;
		gyr_accuracy = 0;
		mag_accuracy = 0;
		rc |= init_agm_algo();
		SI_CHECK_RC(rc);
		rc |= reset_vars();
		SI_CHECK_RC(rc);
		break;

	case IS_MAG_INIT_SUCCESSFUL:
		return mag_init_successful;

	case ENABLE_CALIBRATION_SAVING:
		INV_MSG(INV_MSG_LEVEL_INFO, "Enable calibration saving in flash.");
		cal_save_en = 1;
		break;

	case DISABLE_CALIBRATION_SAVING:
		INV_MSG(INV_MSG_LEVEL_INFO, "Disable calibration saving in flash.");
		cal_save_en = 0;
		break;

	default:
		INV_MSG(INV_MSG_LEVEL_INFO, "Unknown command : %c", (char)cmd);
		break;
	}

	return rc;
}
