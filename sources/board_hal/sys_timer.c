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

#include "sysclk.h"

#include "sys_timer.h"

/*
 * Callback for Systick handler
 */
static void (*sSystick_irq_handler_cb)(void);

void inv_sys_timer_init(void (*systick_handler)(void), uint32_t wake_period_ms)
{
	sSystick_irq_handler_cb = systick_handler;

	// Configure the Systick
	// To adjust the SysTick time base, use the following formula:
	// Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)

	// - Reload Value is the parameter to be passed for SysTick_Config() function
	// - Reload Value should not exceed 0xFFFFFF
	
	if(wake_period_ms < 1000)
		SysTick_Config(sysclk_get_cpu_hz() / (1000 / wake_period_ms));
	else 
		SysTick_Config(sysclk_get_cpu_hz() * (wake_period_ms / 1000));

}

/* Interrupt management ------------------------------------------------------*/
  
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(sSystick_irq_handler_cb != 0)
		sSystick_irq_handler_cb();
}
