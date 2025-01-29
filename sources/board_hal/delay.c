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

#include "delay.h"
#include "timer.h"
#include <compiler.h>
#include "component/tc.h"
#include "tc.h"

#include <stdint.h>

/** @brief Control structure for delay timer */
static struct tim_delay_s {
	Tc *timer_instance;
	uint32_t timer_channel;
	unsigned timer_num;
} delay_timer_instance;

static void internal_delay(uint16_t us)
{
	volatile uint32_t now;
	uint32_t end;
	uint32_t prev;
	now = tc_read_cv(delay_timer_instance.timer_instance, delay_timer_instance.timer_channel);
	end = now + us;
	prev = now;

	while(now < end) {
		now = tc_read_cv(delay_timer_instance.timer_instance, delay_timer_instance.timer_channel);
		/* handle rollover */
		if(now < prev) {
			now += UINT16_MAX;
		}
		prev = now;
	}
}

int inv_delay_init(unsigned tim_num)
{
	int rc;

	if(INV_TIMER1 == tim_num) {
		/* as we implement our delay with dedicated start/stop
		 * of a timer, do not allow the timebase timer to be
		 * used. That will also help us optimize further access
		 * to the delay timer's counter later on.
		 */
		rc = -1;
	} else {
		/* Although not adequate, this global simplifies user API */
		delay_timer_instance.timer_num = tim_num;
		rc = inv_timer_get_hw_infos(tim_num, &delay_timer_instance.timer_instance, &delay_timer_instance.timer_channel);
		/* Timer configuration at 1MHz frequency */
		rc += inv_timer_configure_timebase(1000000);
		if(0 == rc) {
			inv_timer_enable(delay_timer_instance.timer_num);
		}
	}

	return rc;
}

void inv_delay_us(uint32_t us)
{
	if((tc_get_status(delay_timer_instance.timer_instance, delay_timer_instance.timer_channel) & TC_SR_CLKSTA) == 0) {
		tc_start(delay_timer_instance.timer_instance, delay_timer_instance.timer_channel);
		while((tc_get_status(delay_timer_instance.timer_instance, delay_timer_instance.timer_channel) & TC_SR_CLKSTA) == 0) {}
	}

	/* in case the delay is up to UINT16_MAX */
	if(us >= UINT16_MAX) {
		/* go to the loop as the internal_delay function only support uint16_t argument type */
		for(uint32_t i = 0; i < (uint32_t)(us / UINT16_MAX); i++) {
			internal_delay(UINT16_MAX);
		}
		internal_delay(us % UINT16_MAX);
	}
	else
		internal_delay(us);

}

void inv_delay_ms(uint32_t ms)
{
	inv_delay_us(ms * 1000);
}

