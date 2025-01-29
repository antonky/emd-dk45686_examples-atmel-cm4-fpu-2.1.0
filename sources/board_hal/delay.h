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

/** @defgroup delay delay
 *  @brief    API implementing some active wait functionalities.
 *
 *	@ingroup  Low_Level_Driver
 *  @{
 */

#ifndef _INV_DELAY_H_
#define _INV_DELAY_H_

#include <stdint.h>

/**
 * @brief  Initialize the timer delay
 * @param timer_num Timer peripheral number
 * @return 0 if success, -1 on error
 */
int inv_delay_init(unsigned timer_num);

/**
 * @brief  Busy wait based on a 100MHz clock timer
 * The timer is start and stop for each call to this function to avoid power
 * consumption
 * @warning Maximum timing value supported is 40s
 * @param  Timing in us
 */
void inv_delay_us(uint32_t us);

/**
 * @brief  Busy wait based on a 100MHz clock timer
 * The timer is start and stop for each call to this function to avoid power
 * consumption
 * @warning Maximum timing value supported is 40s
 * @param  Timing in ms
 */
void inv_delay_ms(uint32_t ms);

#endif

/** @} */
