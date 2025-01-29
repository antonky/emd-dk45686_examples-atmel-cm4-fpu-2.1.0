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

#ifndef _SYSTEM_INTERFACE_H_
#define _SYSTEM_INTERFACE_H_

#include "imu/inv_imu_transport.h" /* For inv_imu_serif_type_t */

/* Boards drivers */
#include "gpio.h"
#include "uart.h"

/* Utils */
#include "Invn/EmbUtils/Message.h"

/*
 * Board
 */

/** @brief Initialize board.
 *  @return  0 on success, negative value on error.
 */
int si_board_init(void);

/*
 * UART
 */

#define SI_UART_ID_FTDI INV_UART_SENSOR_CTRL
#define SI_UART_ID_EDBG INV_UART_LOG

/** @brief Configure UART to transmit characters.
 *         Baudrate: 921600
 *         Flow control: None
 *  @param[in] id     UART to configure.
 *  @param[in] level  Trace level (enum inv_msg_level).
 *  @return        0 on success, negative value on error.
 */
int si_config_uart_for_print(inv_uart_num_t id, int level);

/** @brief Configure UART to transmit binary data.
 *         Baudrate: 2000000
 *         Flow control: RTS/CTS
 *  @param[in] id  UART to configure.
 *  @return        0 on success, negative value on error.
 */
int si_config_uart_for_bin(inv_uart_num_t id);

/** @brief Get user command from UART.
 *  @param[in] id    UART to read from.
 *  @param[out] cmd  User command if one has been sent, 0 otherwise.
 *  @return          0 on success, negative value on error.
 */
int si_get_uart_command(inv_uart_num_t id, char *cmd);

/*
 * I/O for IMU device
 */

/** @brief Configure I/O for IMU device.
 *  @param[in] serif_type  Serial interface type to be used.
 *  @return                0 on success, negative value on error.
 */
int si_io_imu_init(inv_imu_serif_type_t serif_type);

/** @brief Read register(s) implementation for IMU device.
 *  @param[in] reg   Register address to be read.
 *  @param[out] buf  Output data from the register.
 *  @param[in] len   Number of byte to be read.
 *  @return          0 on success, negative value on error.
 */
int si_io_imu_read_reg(uint8_t reg, uint8_t *buf, uint32_t len);

/** @brief Write register(s) implementation for IMU device.
 *  @param[in] reg  Register address to be written.
 *  @param[in] buf  Input data to write.
 *  @param[in] len  Number of byte to be written.
 *  @return         0 on success, negative value on error.
 */
int si_io_imu_write_reg(uint8_t reg, const uint8_t *buf, uint32_t len);

/*
 * I/O for AKM device
 */

/** @brief Configure I/O for AKM device.
 *  @param[in] serif  Pointer to serial interface structure.
 *  @return           0 on success, negative value on error.
 */
int si_io_akm_init(void *serif);

/** @brief Read register(s) implementation for AKM device.
 *  @param[in] serif  Pointer to serial interface structure.
 *  @param[in] reg    Register address to be read.
 *  @param[out] buf   Output data from the register.
 *  @param[in] len    Number of byte to be read.
 *  @return           0 on success, negative value on error.
 */
int si_io_akm_read_reg(void *serif, uint8_t reg, uint8_t *buf, uint32_t len);

/** @brief Write register(s) implementation for AKM device.
 *  @param[in] serif  Pointer to serial interface structure.
 *  @param[in] reg    Register address to be written.
 *  @param[in] buf    Input data to write.
 *  @param[in] len    Number of byte to be written.
 *  @return           0 on success, negative value on error.
 */
int si_io_akm_write_reg(void *serif, uint8_t reg, const uint8_t *buf,
                        uint32_t len);

int si_io_akm_init_timer();
int si_io_akm_start_sampling_timer(const uint32_t period_us,
                                   void interrupt_timer_mag_cb(void *context),
                                   int *ch);
int si_io_akm_stop_sampling_timer(int ch);
int si_io_akm_start_data_timer(const uint32_t period_us,
                               void interrupt_timer_mag_cb(void *context),
                               int *ch);
int si_io_akm_stop_data_timer(int ch);

/*
 * Timers
 */

/** @brief Initialize timers IP.
 *         INV_TIMER1 for timebase.
 *         INV_TIMER2 for delay.
 *  @return  0 on success, negative value on error.
 */
int si_init_timers();

/** @brief Sleep function implementation.
 *  @param[in] us  Time to sleep in microseconds.
 */
void si_sleep_us(uint32_t us);

/** @brief Get current time function implementation.
 *  @return  The current time in us or 0 if get_time_us pointer is null.
 */
uint64_t si_get_time_us();

/*
 * RTC/CLKIN
 */

/** @brief Initialize RTC IP and output 32768Hz RTC on clock pin.
 *  @return  0 on success, negative value on error.
 */
int si_init_clkin();

/** @brief Stop output 32768Hz RTC on clock pin.
 *  @return  0 on success, negative value on error.
 */
int si_uninit_clkin();

/*
 * GPIO
 */

#define SI_GPIO_INT1 INV_GPIO_INT1
#define SI_GPIO_INT2 INV_GPIO_INT2
#define SI_GPIO_INT_MAG INV_GPIO_3RD_PARTY_INT1

/** @brief Initializes GPIO module to trigger callback when interrupt from IMU
 * fires.
 *  @param[in] int_num  Interrupt pin (`SI_GPIO_INT1` or `SI_GPIO_INT2`).
 *  @param[in] int_cb   Callback to be called when interrupt fires.
 *  @return             0 on success, negative value on error.
 */
int si_init_gpio_int(unsigned int_num,
                     void (*int_cb)(void *context, unsigned int_num));

/** @brief Initializes GPIO module to initializes FSYNC output pin and trigger
 * callback at a given frequency to allow user to toggle FSYNC pin at regular
 * interval to emulate camera module.
 *  @param[in] freq             Frequency at which fsync_timer_cb should be
 * called (0 if no timer is to be enabled)
 *  @param[in] fsync_timer_cb   Callback to be called when FSYNC timer expires.
 *  @return                     0 on success, negative value on error.
 */
int si_start_gpio_fsync(uint32_t freq, void (*fsync_timer_cb)(void *context));

/** @brief Stop FSYNC module.
 *  @return  0 on success, negative value on error.
 */
int si_stop_gpio_fsync();

/** @brief Toggles GPIO FSYNC output pin.
 */
void si_toggle_gpio_fsync(void);

/*
 * FLASH STORAGE
 */

/**
 * @brief  Initialize the FLASH
 * @return 0 if init succeeds, flash_status otherwise
 */
int si_flash_storage_init(void);

/**
 * @brief  Read data from the FLASH sector
 * @param  pData, pointer on 84 bytes buffer of data
 * @return 0 if read succeeds, flash_status otherwise
 */
int si_flash_storage_read(uint8_t *pData);

/**
 * @brief  Write data to the FLASH sector
 * @param  pData, pointer on 84 bytes buffer of data
 * @return 0 if write succeeds, flash_status otherwise
 */
int si_flash_storage_write(const uint8_t *pData);

/*
 * Common
 */

/** @brief Disable core interrupts.
 */
void si_disable_irq();

/** @brief Enable core interrupts.
 */
void si_enable_irq();

/*
 * Error codes
 */

/** @brief In case of error, print message, file and line and return with error
 * code.
 *  @param[in] rc  Error code (rc).
 */
#define SI_CHECK_RC(rc)                                                        \
  do {                                                                         \
    if (si_print_error_if_any(rc)) {                                           \
      INV_MSG(INV_MSG_LEVEL_ERROR, "At %s (line %d)", __FILE__, __LINE__);     \
      si_sleep_us(100000);                                                     \
      return rc;                                                               \
    }                                                                          \
  } while (0)

/** @brief Check return code from driver and print message if it is an error.
 *  @param[in] rc  Return code from the driver.
 *  @return        Error code (rc).
 */
int si_print_error_if_any(int rc);

#endif /* !_SYSTEM_INTERFACE_H_ */
