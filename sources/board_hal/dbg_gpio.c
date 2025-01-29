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

#include "ioport.h"

#include "dbg_gpio.h"

static const uint16_t mapping[INV_DBG_GPIO_MAX] = { PIO_PA0_IDX, PIO_PA17_IDX, PIO_PA18_IDX };

void inv_dbg_gpio_init_out(int gpio_num)
{
	if(gpio_num < INV_DBG_GPIO_MAX) {
		ioport_init();
		ioport_set_pin_dir(mapping[gpio_num], IOPORT_DIR_OUTPUT);
		ioport_set_pin_mode(mapping[gpio_num], IOPORT_MODE_PULLDOWN);
	}
}

void inv_dbg_gpio_set(int gpio_num)
{
	if(gpio_num < INV_DBG_GPIO_MAX) {
		ioport_set_pin_level(mapping[gpio_num], true);
	}
}

void inv_dbg_gpio_clear(int gpio_num)
{
	if(gpio_num < INV_DBG_GPIO_MAX) {
		ioport_set_pin_level(mapping[gpio_num], false);
	}
}

void inv_dbg_gpio_toggle(int gpio_num)
{
	if(gpio_num < INV_DBG_GPIO_MAX) {
		ioport_toggle_pin_level(mapping[gpio_num]);
	}
}