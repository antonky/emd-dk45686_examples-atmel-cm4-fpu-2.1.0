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
#include "wdt.h"
#include "ioport.h"

#include "common.h"

/* This variable contains the number of nested calls to disable_irq */
static uint32_t sDisableIntCount = 0;

void inv_board_hal_init(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	
	ioport_init();
	
	/* Initialize LED0, turned off */
	ioport_set_pin_dir(PIO_PA6_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PA6_IDX, IOPORT_PIN_LEVEL_HIGH);

	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
}

void inv_disable_irq(void)
{
	if(sDisableIntCount == 0) {
		__disable_irq();
	}
	sDisableIntCount ++;
}

void inv_enable_irq(void)
{
	sDisableIntCount --;
	if(sDisableIntCount == 0) {
		__enable_irq();
	}
}
