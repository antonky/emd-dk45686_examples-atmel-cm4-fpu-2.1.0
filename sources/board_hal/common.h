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

/** @defgroup common common
 *  @brief    Implementation of API shared by several modules
 *
 *	@ingroup  Low_Level_Driver
 *  @{
*/

#ifndef __INV_COMMON_H__
#define __INV_COMMON_H__

void inv_board_hal_init(void);

/**
  * @brief  Disable core interrupts while supporting nested interrupts.
  * To fully support nesting, interrupts must be enabled with enable_irq() function.
  */
void inv_disable_irq(void);

/**
  * @brief  Enable core interrupts while supporting nested interrupts.
  * To fully support nesting, interrupts must be enabled with disable_irq() function.
  */
void inv_enable_irq(void);

#endif //__INV_COMMON_H__

/** @} */