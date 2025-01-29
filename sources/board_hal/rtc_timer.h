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

/** @defgroup RTC_Timer RTC_Timer
	@ingroup Low_Level_Driver
	@{
*/

#ifndef _RTC_TIMER_H_
#define _RTC_TIMER_H_

#include <stdint.h>
#include "rtc.h"
#include "pmc.h"

/**
  * @brief  Init system timer based on RTC clock (24-hour mode)  
  * @Note   Initialize SLCK to external crystal.
  * @param  rtc_irq_handler RTC clock IRQ handler, set to NULL in case no wake up is required from RTC
  */
void rtc_timer_init(void (*rtc_irq_handler)(void));

/**
  * @brief  Reconfigure RTC clock IRQ handler
  * @param  rtc_irq_handler RTC clock IRQ handler
  */
void rtc_timer_update_irq_callback(void (*rtc_irq_handler)(void));

/**
  * @brief  Get timestamps from RTC calendar counters in microsecond and prevent rollover
  * @retval timestamps in microsecond
  */
uint64_t rtc_timer_get_time_us(void);

#endif /* _RTC_TIMER_H_ */

/** @} */