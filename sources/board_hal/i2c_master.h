/*
 *
 * Copyright (c) [2016] by InvenSense, Inc.
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

/** @defgroup I2C_Master I2C_Master
        @ingroup Low_Level_Driver
        @{
*/
#ifndef __INV_I2C_MASTER_H__
#define __INV_I2C_MASTER_H__

#include <stdint.h>

/** @brief Configures I2C master peripheral
 */
void inv_i2c_master_init(void);

/** @brief Deactivates the I2C master peripheral
 */
void inv_i2c_master_deinit(void);

/** @brief Read a register through the control interface I2C
 * @param[in] address, I2c 7bit-address
 * @param[in] register_addr, register address (location) to access
 * @param[in] register_len, length value to read
 * @param[in] register_value, pointer on byte value to read
 * @retval 0 if correct communication, else wrong communication
 */
unsigned long inv_i2c_master_read_register(unsigned char address,
                                           unsigned char register_addr,
                                           unsigned short register_len,
                                           unsigned char *register_value);

/** @brief Write a register through the control interface I2C
 * @param[in] address, I2c 7bit-address
 * @param[in] register_addr, register address (location) to access
 * @param[in] register_len, length value to write
 * @param[in] register_value, pointer on byte value to write
 * @retval 0 if correct communication, else wrong communication
 */
unsigned long inv_i2c_master_write_register(
    unsigned char address, unsigned char register_addr,
    unsigned short register_len, const unsigned char *register_value);

/** @brief Read a byte buffer through the control interface I2C
 * @param[in] address, I2c 7bit-address
 * @param[in] len, length value to read
 * @param[in] value, pointer on byte value to read
 * @retval 0 if correct communication, else wrong communication
 */
unsigned long inv_i2c_master_read_raw(unsigned char address, unsigned short len,
                                      unsigned char *value);

/** @brief Write a byte buffer through the control interface I2C
 * @param[in] address, I2c 7bit-address
 * @param[in] len, length value to write
 * @param[in] value, pointer on byte value to write
 * @retval 0 if correct communication, else wrong communication
 */
unsigned long inv_i2c_master_write_raw(unsigned char address,
                                       unsigned short len,
                                       const unsigned char *value);

#endif /* __INV_I2C_MASTER_H__ */

/** @} */
