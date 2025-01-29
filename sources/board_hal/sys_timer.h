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

/** @defgroup System_Timer System_Timer
	@ingroup  Low_Level_Driver
	@{
*/
#ifndef _INV_SYS_TIMER_H_
#define _INV_SYS_TIMER_H_

#include <stdint.h>

/**
  * @brief  Init system timer based on systick clock
  * @param systick_handler  systick IRQ handler 
  * @param  wake_period_ms scheduler period in ms (Systick period), minimum period = 1ms
  */
void inv_sys_timer_init(void (*systick_handler)(void), uint32_t wake_period_ms);

#endif /* _INV_SYS_TIMER_H_ */

/** @} */