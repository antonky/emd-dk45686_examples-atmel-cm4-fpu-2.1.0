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

#include "system_interface.h"

/* Standard includes */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* IMU drivers */
#include "imu/inv_imu_defs.h" /* For error codes */

/* Board drivers */
#include "common.h"
#include "delay.h"
#include "flash_manager.h"
#include "i2c_master.h"
#include "rtc_timer.h"
#include "spi_master.h"
#include "sys_timer.h"
#include "timer.h"
#include "uart_mngr.h"

/* Utils */
#include "Invn/EmbUtils/Message.h"

/* Supported board revisions */
#define SM_REVB_DB 1
#define SM_REVG 2
#define SM_REVI 3
#define SM_REVDPLUS SM_REVB_DB

/* SPI/I2C configuration for IMU I/O */
#if (SM_BOARD_REV == SM_REVB_OB)
#define INV_SPI_AP INV_SPI_ONBOARD_REVB
#define ICM_I2C_ADDR 0x69
#else /* SM_REVB_DB, SM_REVG and SM_REVI have same SPI/I2C configuration */
#define INV_SPI_AP INV_SPI_REVI
#define ICM_I2C_ADDR 0x68
#endif

/* SPI/I2C configuration for AKM I/O */
#define AK_I2C_ADDR 0x0E

/* Timers */
#define TIMEBASE_TIMER INV_TIMER1 /* Used for si_get_time_us() */
#define DELAY_TIMER INV_TIMER2    /* Used for si_sleep_us() */
#define MAG_SAMPLING_TIMER                                                     \
  INV_TIMER3 /* Used for si_io_akm_init_timer_getdata() */
#define MAG_DATA_TIMER INV_TIMER4

/* IMU serial interface type */
static inv_imu_serif_type_t imu_serif_type;

/* ID of the UART used for messages */
static inv_uart_num_t uart_id_message;

/*
 * Board
 */
int si_board_init(void) {
  inv_board_hal_init();

#if (SM_BOARD_REV == SM_REVB_OB)
  /* Set board revision revB if define is set */
  inv_gpio_set_board_rev(INV_GPIO_BOARD_REVB);
#elif (SM_BOARD_REV == SM_REVB_DB)
  /* Set board revision revB DB if define is set */
  inv_gpio_set_board_rev(INV_GPIO_BOARD_REVB_DB);
#elif (SM_BOARD_REV == SM_REVG)
  /* Set board revision revG if define is set */
  inv_gpio_set_board_rev(INV_GPIO_BOARD_REVG);
#elif (SM_BOARD_REV == SM_REVI)
  /* Set board revision revG if define is set */
  inv_gpio_set_board_rev(INV_GPIO_BOARD_REVI);
#else
#error Please select a board revision
#endif

  return 0;
}

/*
 * UART
 */
static void msg_printer(int level, const char *str, va_list ap) {
#ifdef INV_MSG_ENABLE
  static char out_str[256]; /* static to limit stack usage */
  unsigned idx = 0;
  const char *s[INV_MSG_LEVEL_MAX] = {
      "",     // INV_MSG_LEVEL_OFF
      "[E] ", // INV_MSG_LEVEL_ERROR
      "[W] ", // INV_MSG_LEVEL_WARNING
      "[I] ", // INV_MSG_LEVEL_INFO
      "[V] ", // INV_MSG_LEVEL_VERBOSE
      "[D] ", // INV_MSG_LEVEL_DEBUG
  };

  idx += snprintf(&out_str[idx], sizeof(out_str) - idx, "%s", s[level]);
  if (idx >= (sizeof(out_str)))
    return;
  idx += vsnprintf(&out_str[idx], sizeof(out_str) - idx, str, ap);
  if (idx >= (sizeof(out_str)))
    return;
  idx += snprintf(&out_str[idx], sizeof(out_str) - idx, "\r\n");
  if (idx >= (sizeof(out_str)))
    return;

  inv_uart_mngr_puts(uart_id_message, out_str, idx);

#else
  (void)level, (void)str, (void)ap;
#endif
}

int si_config_uart_for_print(inv_uart_num_t id, int level) {
  int rc = 0;
  inv_uart_mngr_init_struct_t uart_mngr_config;

  uart_mngr_config.uart_num = id;
  uart_mngr_config.baudrate = 921600;
  uart_mngr_config.flow_ctrl = INV_UART_FLOW_CONTROL_NONE;
  /*rc |= */ inv_uart_mngr_init(&uart_mngr_config);

  uart_id_message = id;

  /* Setup message facility */
  INV_MSG_SETUP(level, msg_printer);

  return rc;
}

int si_config_uart_for_bin(inv_uart_num_t id) {
  int rc = 0;
  inv_uart_mngr_init_struct_t uart_mngr_config;

  uart_mngr_config.uart_num = id;
  uart_mngr_config.baudrate = 2000000;
  uart_mngr_config.flow_ctrl = INV_UART_FLOW_CONTROL_RTS_CTS;

  /*rc |= */ inv_uart_mngr_init(&uart_mngr_config);

  return rc;
}

int si_get_uart_command(inv_uart_num_t id, char *cmd) {
  int rc = 0;

  *cmd = 0;

  if (inv_uart_mngr_available(id)) {
    char c = inv_uart_mngr_getc(id);
    if (c != '\n')
      *cmd = c;
  }

  return rc;
}

/*
 * I/O for IMU device
 */
int si_io_imu_init(inv_imu_serif_type_t serif_type) {
  imu_serif_type = serif_type;

  switch (imu_serif_type) {
  case UI_SPI4: {
#if (SM_BOARD_REV == SM_REVB_DB)
    uint8_t dummy = 0;
    /* To avoid SPI disturbance on IMU DB, on-chip IMU is forced to SPI by doing
     * a dummy-write*/
    inv_spi_master_init(INV_SPI_ONBOARD_REVB, 12 * 1000 * 1000);
    /* Write to register MPUREG_WHO_AM_I */
    inv_spi_master_write_register(INV_SPI_ONBOARD_REVB, 0x75, 1, &dummy);
#endif
    inv_spi_master_init(INV_SPI_AP, 12 * 1000 * 1000);
    break;
  }

  case UI_I2C:
#if ((SM_BOARD_REV == SM_REVG) || (SM_BOARD_REV == SM_REVI))
    /* Force AD0 to be driven as output level low */
    inv_gpio_init_pin_out(INV_GPIO_AD0);
    inv_gpio_set_pin_low(INV_GPIO_AD0);
#endif
    /* Set I2C clock is 400kHz by default */
    inv_i2c_master_init();
    break;

  default:
    return -1;
  }

  return 0;
}

int si_io_imu_read_reg(uint8_t reg, uint8_t *buf, uint32_t len) {
  switch (imu_serif_type) {
  case UI_SPI4:
    return inv_spi_master_read_register(INV_SPI_AP, reg, len, buf);

  case UI_I2C:
    return inv_i2c_master_read_register(ICM_I2C_ADDR, reg, len, buf);

  default:
    return -1;
  }
}

int si_io_imu_write_reg(uint8_t reg, const uint8_t *buf, uint32_t len) {
  switch (imu_serif_type) {
  case UI_SPI4:
    return inv_spi_master_write_register(INV_SPI_AP, reg, len, buf);

  case UI_I2C:
    return inv_i2c_master_write_register(ICM_I2C_ADDR, reg, len, buf);

  default:
    return -1;
  }
}

/*
 * I/O for Ak09915 device
 */
int si_io_akm_init(void *serif) {
  (void)serif;
  inv_i2c_master_init();
  return 0;
}

int si_io_akm_read_reg(void *serif, uint8_t reg, uint8_t *buf, uint32_t len) {
  (void)serif;
  return inv_i2c_master_read_register(AK_I2C_ADDR, reg, len, buf);
}

int si_io_akm_write_reg(void *serif, uint8_t reg, const uint8_t *buf,
                        uint32_t len) {
  (void)serif;
  return inv_i2c_master_write_register(AK_I2C_ADDR, reg, len, buf);
}

int si_io_akm_init_timer() {
  inv_timer_enable(MAG_SAMPLING_TIMER);

  return 0;
}

int si_io_akm_start_sampling_timer(const uint32_t period_us,
                                   void interrupt_timer_mag_cb(void *context),
                                   int *ch) {
  uint32_t frequency = (1000000 / period_us);
  int channel;

  /* Round up frequency */
  if (period_us != 1000000 / frequency)
    frequency++;

  /* Configure the timer used to trigger new magnetometer data capture */
  channel = inv_timer_configure_callback(MAG_SAMPLING_TIMER, frequency, 0,
                                         interrupt_timer_mag_cb);

  if (ch)
    *ch = channel;

  return 0;
}

int si_io_akm_stop_sampling_timer(int ch) {
  inv_timer_channel_suspend(MAG_SAMPLING_TIMER, ch);

  return 0;
}

int si_io_akm_start_data_timer(const uint32_t period_us,
                               void interrupt_timer_mag_cb(void *context),
                               int *ch) {
  uint32_t frequency = (1000000 / period_us);
  int channel;

  /* Round up frequency */
  if (period_us != 1000000 / frequency)
    frequency++;

  /* Configure the timer used to trigger new magnetometer data capture */
  channel = inv_timer_configure_callback(MAG_DATA_TIMER, frequency, 0,
                                         interrupt_timer_mag_cb);

  if (ch)
    *ch = channel;

  return 0;
}

int si_io_akm_stop_data_timer(int ch) {
  inv_timer_channel_stop(MAG_DATA_TIMER, ch);

  return 0;
}

/*
 * Timers
 */
int si_init_timers() {
  int rc = 0;

  rc |= inv_delay_init(DELAY_TIMER);
  rc |= inv_timer_configure_timebase(1000000);
  inv_timer_enable(TIMEBASE_TIMER);

  return rc;
}

void si_sleep_us(uint32_t us) { inv_delay_us(us); }

uint64_t si_get_time_us() { return inv_timer_get_counter(TIMEBASE_TIMER); }

/*
 * RTC/CLKIN
 */
int si_init_clkin() {
  rtc_timer_init(NULL);
  return inv_gpio_output_clk_on_pin(INV_GPIO_CLKIN);
}

int si_uninit_clkin() { return inv_gpio_disable_clk_on_pin(INV_GPIO_CLKIN); }

/*
 * GPIO
 */
#define FSYNC_TIMER INV_TIMER3
static int fsync_channel = INV_TIMER_MAX;

int si_init_gpio_int(unsigned int_num,
                     void (*int_cb)(void *context, unsigned int_num)) {
  inv_gpio_sensor_irq_init(int_num, int_cb, 0);
  return 0;
}

int si_start_gpio_fsync(uint32_t freq, void (*fsync_timer_cb)(void *context)) {
  int rc = 0;

  /*
   * Configure output mode GPIO connected to FSYNC_PIN.
   * This pin is connected to IMU FSYNC input and will send the FSYNC signal
   * to emulate a camera module.
   */
  inv_gpio_init_pin_out(INV_GPIO_INT2);
  inv_gpio_set_pin_high(INV_GPIO_INT2);

  if (freq) {
    /*
     * Emulate the FSYNC Camera module
     * The FSYNC signal is based on the timer interrupt
     * A callback function is also passed that will be executed each time on
     * timer interrupts.
     */
    fsync_channel =
        inv_timer_configure_callback(FSYNC_TIMER, freq, 0, fsync_timer_cb);
    if (fsync_channel < 0)
      rc |= fsync_channel;
  }

  return rc;
}

int si_stop_gpio_fsync() {
  return inv_timer_channel_stop(FSYNC_TIMER, fsync_channel);
}

void si_toggle_gpio_fsync(void) { inv_gpio_toggle_pin(INV_GPIO_INT2); }

/*
 * FLASH STORAGE
 */

int si_flash_storage_init(void) { return inv_flash_manager_init(); }

int si_flash_storage_read(uint8_t *pData) {
  return inv_flash_manager_readData(pData);
}

int si_flash_storage_write(const uint8_t *pData) {
  return inv_flash_manager_writeData(pData);
}

/*
 * Common
 */

void si_disable_irq() { inv_disable_irq(); }

void si_enable_irq() { inv_enable_irq(); }

/*
 * Error codes
 */
int si_print_error_if_any(int rc) {
  if (rc != 0) {
    switch (rc) {
    case INV_IMU_ERROR:
      INV_MSG(INV_MSG_LEVEL_ERROR, "Unspecified error (%d)", rc);
      break;
    case INV_IMU_ERROR_TRANSPORT:
      INV_MSG(INV_MSG_LEVEL_ERROR, "Error occurred at transport level (%d)",
              rc);
      break;
    case INV_IMU_ERROR_TIMEOUT:
      INV_MSG(INV_MSG_LEVEL_ERROR,
              "Action did not complete in the expected time window (%d)", rc);
      break;
    case INV_IMU_ERROR_BAD_ARG:
      INV_MSG(INV_MSG_LEVEL_ERROR, "Invalid argument provided (%d)", rc);
      break;
    case INV_IMU_ERROR_EDMP_BUF_EMPTY:
      INV_MSG(INV_MSG_LEVEL_ERROR, "EDMP buffer is empty (%d)", rc);
      break;
    default:
      INV_MSG(INV_MSG_LEVEL_ERROR, "Unknown error (%d)", rc);
      break;
    }
  }

  return rc;
}
