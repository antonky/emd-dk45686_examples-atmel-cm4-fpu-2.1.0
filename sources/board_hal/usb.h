/*
 *
 * Copyright (c) [2018] by InvenSense, Inc.
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

/** @defgroup Usb Usb
	@ingroup  Low_Level_Driver
	@{
*/
#ifndef __INV_USB_H__
#define __INV_USB_H__

#include <stdint.h>
#include <stdbool.h>

/**
 * Available USB peripherals
 */
typedef enum usb_num {
	INV_USB_TARGET, /**< Just a fancier and hw independant name for USB connector.
	                   < It is used to display pointing based on HID Mouse.
	                   < On samg55 it is mapped on J301 USB port with PA21_USB_N / PA22_USB_P lines. */
}inv_usb_num_t;

/** @brief USB initialisation structure.
 *
 * Such a structure should be filled-in and passed to the usb_init function in order to 
 * initialize the usb peripheral.
 */
typedef struct inv_usb_init_struct {
	inv_usb_num_t    usb_num;                             /** < USB peripheral to initialize */
	void            (*suspend_action_cb)(void);           /** < Callback executed when USB bus is wakeup */
	void            (*resume_action_cb)(void);            /** < Callback executed for each received SOF */
}inv_usb_init_struct_t;

/** @brief      Initialize the USB peripheral according to 
 *              the parameters specified in the usb_init_struct
 *  @param[in]  usb Pointer to the usb_init_struct that contains
 *              the configuration information
 */
void inv_usb_init(inv_usb_init_struct_t * usb);

/** @brief      Move the mouse pointer on X and Y axes through 
 *              USB HID Mouse interface
 *  @param[in]  moveX Delta on X axis
 *  @param[in]  moveY Delta on Y axis
 *  @return 0 if success, -1 on error
 */
int inv_usb_hid_mouse_move(int8_t moveX, int8_t moveY);

/** @brief      Click the mouse button left or right through 
 *              USB HID Mouse interface
 *  @param[in]  click_left true on left click, false otherwise
 *  @param[in]  click_right true on rigth click, false otherwise
 *  @return 0 if success, -1 on error
 */
int inv_usb_hid_mouse_button_click(bool click_left, bool click_right);

#endif // __INV_USB_H__

/** @} */
