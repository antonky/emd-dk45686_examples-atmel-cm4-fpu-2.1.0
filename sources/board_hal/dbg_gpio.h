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

/** @defgroup dbg_gpio dbg_gpio
 *  @brief    This API allows to control the level of several GPIO for
 * debug purpose.
 *
 *	@ingroup  Low_Level_Driver
 *  @{
*/

#ifndef _INV_DBG_GPIO_H_
#define _INV_DBG_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @brief simple enum to abstract physical mapping of the GPIOs
  *
  * To find the actual physical mapping of the GPIO controlled by the API
  * check in source code board_hal/dbg_gpio.c
  */
enum dbg_gpio_num {
	INV_DBG_GPIO_0,
	INV_DBG_GPIO_1,
	INV_DBG_GPIO_2,
	INV_DBG_GPIO_MAX
};

/** @brief Initialize the GPIO controller driving the GPIO 
 * passed in parameter
 * @param gpio_num GPIO number defined in enum dbg_gpio_num
 */
void inv_dbg_gpio_init_out(int gpio_num);

/** @brief Set level of the GPIO passed in parameter
 * @param gpio_num GPIO number defined in enum dbg_gpio_num
 */
void inv_dbg_gpio_set(int gpio_num);

/** @brief Reset level of the GPIO passed in parameter
 * @param gpio_num GPIO number defined in enum dbg_gpio_num
 */
void inv_dbg_gpio_clear(int gpio_num);

static inline void inv_dbg_gpio_ctrl(int gpio_num, int en)
{
	if(en) {
		inv_dbg_gpio_set(gpio_num);
	}
	else {
		inv_dbg_gpio_clear(gpio_num);
	}
}

/** @brief Toggle level of the GPIO passed in parameter
 * @param gpio_num GPIO number defined in enum dbg_gpio_num
 */
void inv_dbg_gpio_toggle(int gpio_num);

#ifdef __cplusplus
}
#endif

#endif /* _INV_DBG_GPIO_H_*/

/** @} */
