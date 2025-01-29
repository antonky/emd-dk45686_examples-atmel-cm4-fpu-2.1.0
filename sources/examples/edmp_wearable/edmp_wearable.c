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
#include "imu/inv_imu_driver.h"
#include "imu/inv_imu_driver_advanced.h"
#include "imu/inv_imu_edmp.h"
#include "imu/inv_imu_edmp_wearable.h"

/* Board drivers */
#include "system_interface.h"

/* std */
#include <stdio.h>

/*
 * This example showcases how to configure and use wearable features.
 * It enables accelerometer in Low-Power mode at 50Hz.
 * It loads extended features RAM image, handling B2S, and starts eDMP to detect
 * B2S and reverse B2S events.
 */

/*
 * Select communication link between SmartMotion and IMU.
 * SPI4: `UI_SPI4`
 * I2C:  `UI_I2C`
 */
#define SERIF_TYPE UI_SPI4

/*
 * WOM threshold value in mg.
 * 1g/256 resolution (wom_th = mg * 256 / 1000)
 */
#define DEFAULT_WOM_THS_MG 52 >> 2 // 52 mg

/* Static variables */
static inv_imu_device_t imu_dev; /* Driver structure */
static volatile int int1_flag;   /* Flag set when INT1 is received */
static volatile uint64_t
    int1_timestamp; /* Store timestamp when int from IMU fires */

/* Static variables for command interface */
static uint8_t power_save_en; /* Indicates power save mode state */

/* Static functions definition */
static int setup_mcu();
static int setup_imu();
static int configure_and_enable_edmp_wearable(void);
static void int_cb(void *context, unsigned int int_num);
static int get_uart_command();
static int print_help();
static int print_current_config();

/* Main function implementation */
int main(void) {
  int rc = 0;

  rc |= setup_mcu();
  SI_CHECK_RC(rc);

  INV_MSG(INV_MSG_LEVEL_INFO, "###");
  INV_MSG(INV_MSG_LEVEL_INFO, "### Example EDMP WEARABLE B2S");
  INV_MSG(INV_MSG_LEVEL_INFO, "###");

  /* Reset commands interface states */
  power_save_en = 0;

  rc |= setup_imu();
  SI_CHECK_RC(rc);

  /* Reset timestamp and interrupt flag */
  int1_flag = 0;
  int1_timestamp = 0;

  do {
    /* Poll device for data */
    if (int1_flag) {
      uint64_t timestamp;
      inv_imu_int_state_t int_state;
      inv_imu_edmp_int_state_t apex_state = {0};

      si_disable_irq();
      /* Clear interrupt flag */
      int1_flag = 0;
      /* Retrieve timestamp */
      timestamp = int1_timestamp;
      si_enable_irq();

      /* Read interrupt status */
      rc |= inv_imu_get_int_status(&imu_dev, INV_IMU_INT1, &int_state);
      SI_CHECK_RC(rc);

      /* If APEX status is set */
      if (int_state.INV_EDMP_EVENT) {
        /* Read APEX interrupt status */
        rc |= inv_imu_edmp_get_int_apex_status(&imu_dev, &apex_state);
        SI_CHECK_RC(rc);

        /* B2S */
        if (apex_state.INV_R2W_SLEEP) {
          INV_MSG(INV_MSG_LEVEL_INFO, "   %10llu us   B2S REVERSE", timestamp);
        }
        if (apex_state.INV_R2W) {
          INV_MSG(INV_MSG_LEVEL_INFO, "   %10llu us   B2S", timestamp);
        }
      }
    }
    rc |= get_uart_command();
  } while (rc == 0);

  return rc;
}

/* Initializes MCU peripherals. */
static int setup_mcu() {
  int rc = 0;

  rc |= si_board_init();

  /* Configure UART for log */
  rc |= si_config_uart_for_print(SI_UART_ID_FTDI, INV_MSG_LEVEL_DEBUG);

  /* Configure GPIO to call `int_cb` when INT1 fires. */
  rc |= si_init_gpio_int(SI_GPIO_INT1, int_cb);

  /* Init timer peripheral for sleep and get_time */
  rc |= si_init_timers();

  /* Initialize serial interface between MCU and IMU */
  rc |= si_io_imu_init(SERIF_TYPE);

  return rc;
}

/* Initializes IMU device and apply configuration. */
static int setup_imu() {
  int rc = 0;
  uint8_t whoami = 0;
  inv_imu_int_pin_config_t int_pin_config;
  inv_imu_int_state_t int_config;

  /* Init transport layer */
  imu_dev.transport.read_reg = si_io_imu_read_reg;
  imu_dev.transport.write_reg = si_io_imu_write_reg;
  imu_dev.transport.serif_type = SERIF_TYPE;
  imu_dev.transport.sleep_us = si_sleep_us;

  /* Wait 3 ms to ensure device is properly supplied  */
  si_sleep_us(3000);

  /* In SPI, configure slew-rate to prevent bus corruption on
   * DK-SMARTMOTION-REVG */
  if (imu_dev.transport.serif_type == UI_SPI3 ||
      imu_dev.transport.serif_type == UI_SPI4) {
    drive_config0_t drive_config0;
    drive_config0.pads_spi_slew = DRIVE_CONFIG0_PADS_SPI_SLEW_TYP_10NS;
    rc |= inv_imu_write_reg(&imu_dev, DRIVE_CONFIG0, 1,
                            (uint8_t *)&drive_config0);
    SI_CHECK_RC(rc);
    si_sleep_us(2); /* Takes effect 1.5 us after the register is programmed */
  }

  /* Check whoami */
  rc |= inv_imu_get_who_am_i(&imu_dev, &whoami);
  SI_CHECK_RC(rc);
  if (whoami != INV_IMU_WHOAMI) {
    INV_MSG(INV_MSG_LEVEL_ERROR, "Erroneous WHOAMI value.");
    INV_MSG(INV_MSG_LEVEL_ERROR, "  - Read 0x%02x", whoami);
    INV_MSG(INV_MSG_LEVEL_ERROR, "  - Expected 0x%02x", INV_IMU_WHOAMI);
    return -1;
  }

  rc |= inv_imu_soft_reset(&imu_dev);
  SI_CHECK_RC(rc);

  /*
   * Configure interrupts pins
   * - Polarity High
   * - Pulse mode
   * - Push-Pull drive
   */
  int_pin_config.int_polarity = INTX_CONFIG2_INTX_POLARITY_HIGH;
  int_pin_config.int_mode = INTX_CONFIG2_INTX_MODE_PULSE;
  int_pin_config.int_drive = INTX_CONFIG2_INTX_DRIVE_PP;
  rc |= inv_imu_set_pin_config_int(&imu_dev, INV_IMU_INT1, &int_pin_config);
  SI_CHECK_RC(rc);

  /* Interrupts configuration: Enable only EDMP interrupt */
  memset(&int_config, INV_IMU_DISABLE, sizeof(int_config));
  int_config.INV_EDMP_EVENT = INV_IMU_ENABLE;
  rc |= inv_imu_set_config_int(&imu_dev, INV_IMU_INT1, &int_config);
  SI_CHECK_RC(rc);

  rc |= configure_and_enable_edmp_wearable();
  SI_CHECK_RC(rc);

  return rc;
}

static int configure_and_enable_edmp_wearable(void) {
  int rc = 0;
  inv_imu_edmp_apex_parameters_t apex_parameters;
  inv_imu_edmp_b2s_parameters_t b2s_params;
  inv_imu_edmp_int_state_t apex_int_config;

  rc |= inv_imu_edmp_disable(&imu_dev);
  SI_CHECK_RC(rc);

  /* Set EDMP ODR */
  rc |=
      inv_imu_edmp_set_frequency(&imu_dev, DMP_EXT_SEN_ODR_CFG_APEX_ODR_50_HZ);
  SI_CHECK_RC(rc);

  /* Set accelerometer sensor ODR */
  rc |= inv_imu_set_accel_frequency(&imu_dev, ACCEL_CONFIG0_ACCEL_ODR_50_HZ);
  SI_CHECK_RC(rc);

  /* Select WUOSC clock to have accel in ULP (lowest power mode) */
  rc |= inv_imu_select_accel_lp_clk(&imu_dev, SMC_CONTROL_0_ACCEL_LP_CLK_WUOSC);
  SI_CHECK_RC(rc);

  /* Set AVG to 1x */
  rc |= inv_imu_set_accel_lp_avg(&imu_dev, IPREG_SYS2_REG_129_ACCEL_LP_AVG_1);
  SI_CHECK_RC(rc);

  /* Initialize APEX for B2S */
  rc |= inv_imu_edmp_b2s_init(&imu_dev);
  SI_CHECK_RC(rc);

  /* Configure APEX parameters */
  rc |= inv_imu_edmp_get_apex_parameters(&imu_dev, &apex_parameters);
  apex_parameters.power_save_en = power_save_en;
  if (power_save_en) {
    rc |= inv_imu_adv_configure_wom(
        &imu_dev, DEFAULT_WOM_THS_MG, DEFAULT_WOM_THS_MG, DEFAULT_WOM_THS_MG,
        TMST_WOM_CONFIG_WOM_INT_MODE_ANDED, TMST_WOM_CONFIG_WOM_INT_DUR_1_SMPL);
    rc |= inv_imu_adv_enable_wom(&imu_dev);
  } else {
    rc |= inv_imu_adv_disable_wom(&imu_dev);
  }
  rc |= inv_imu_edmp_set_apex_parameters(&imu_dev, &apex_parameters);
  SI_CHECK_RC(rc);

  rc |= inv_imu_edmp_b2s_get_parameters(&imu_dev, &b2s_params);
  b2s_params.b2s_mounting_matrix = 0; /* identity matrix */
  rc |= inv_imu_edmp_b2s_set_parameters(&imu_dev, &b2s_params);
  SI_CHECK_RC(rc);

  /* Set accel in low-power mode */
  rc |= inv_imu_set_accel_mode(&imu_dev, PWR_MGMT0_ACCEL_MODE_LP);
  SI_CHECK_RC(rc);

  /* Wait for accel startup time */
  si_sleep_us(ACC_STARTUP_TIME_US);

  /* Enable wearable */
  rc |= inv_imu_edmp_b2s_enable(&imu_dev);

  /* Disable all APEX interrupt and enable only the one we need */
  memset(&apex_int_config, INV_IMU_DISABLE, sizeof(apex_int_config));
  apex_int_config.INV_R2W = INV_IMU_ENABLE;
  apex_int_config.INV_R2W_SLEEP = INV_IMU_ENABLE;
  rc |= inv_imu_edmp_set_config_int_apex(&imu_dev, &apex_int_config);
  SI_CHECK_RC(rc);

  /* Enable EDMP */
  rc |= inv_imu_edmp_enable(&imu_dev);
  SI_CHECK_RC(rc);

  return rc;
}

/* IMU interrupt handler. */
static void int_cb(void *context, unsigned int int_num) {
  (void)context;

  if (int_num == SI_GPIO_INT1) {
    int1_timestamp = si_get_time_us();
    int1_flag = 1;
  }
}

/* Get command from user through UART */
static int get_uart_command() {
  int rc = 0;
  char cmd = 0;

  rc |= si_get_uart_command(SI_UART_ID_FTDI, &cmd);
  SI_CHECK_RC(rc);

  switch (cmd) {
  case 'c':
    rc |= print_current_config();
    break;
  case 'o':
    power_save_en = !power_save_en;
    INV_MSG(INV_MSG_LEVEL_INFO, "%s Power Save mode.",
            power_save_en ? "Enabling" : "Disabling");
    rc |= configure_and_enable_edmp_wearable();
    SI_CHECK_RC(rc);
    break;
  case 'h':
  case 'H':
    rc |= print_help();
    break;
  case 0:
    break; /* No command received */
  default:
    INV_MSG(INV_MSG_LEVEL_INFO, "Unknown command : %c", cmd);
    rc |= print_help();
    break;
  }

  return rc;
}

/* Help for UART command interface */
static int print_help() {
  INV_MSG(INV_MSG_LEVEL_INFO, "#");
  INV_MSG(INV_MSG_LEVEL_INFO, "# Help");
  INV_MSG(INV_MSG_LEVEL_INFO, "#");
  INV_MSG(INV_MSG_LEVEL_INFO, "# 'o' : Toggle Power Save mode");
  INV_MSG(INV_MSG_LEVEL_INFO, "# 'c' : Print current configuration");
  INV_MSG(INV_MSG_LEVEL_INFO, "# 'h' : Print this helper");
  INV_MSG(INV_MSG_LEVEL_INFO, "#");

  si_sleep_us(2000000); /* Give user some time to read */

  return 0;
}

/* Print current sample configuration */
static int print_current_config() {
  INV_MSG(INV_MSG_LEVEL_INFO, "#");
  INV_MSG(INV_MSG_LEVEL_INFO, "# Current configuration");
  INV_MSG(INV_MSG_LEVEL_INFO, "#");
  INV_MSG(INV_MSG_LEVEL_INFO, "# Power Save mode: %s",
          power_save_en ? "Enabled" : "Disabled");
  INV_MSG(INV_MSG_LEVEL_INFO, "#");

  si_sleep_us(2000000); /* Give user some time to read */

  return 0;
}