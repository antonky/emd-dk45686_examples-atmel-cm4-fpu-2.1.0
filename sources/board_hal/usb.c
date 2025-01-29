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

#include <string.h>

#include "common.h"
#include "conf_usb.h"
#include "udc.h"
#include "usb.h"

/********************************* Globals ************************************/
/** External callback called when the host suspend the USB line */
void user_callback_suspend_action(void);
/** External callback called when the host or device resume the USB line */
void user_callback_resume_action(void);

static inv_usb_init_struct_t usb_mapping = {
    .usb_num = INV_USB_TARGET,

    .suspend_action_cb = NULL,
    .resume_action_cb = NULL,
};

/****************************** Public Functions ******************************/

void inv_usb_init(inv_usb_init_struct_t *usb_init) {
  usb_mapping.suspend_action_cb = usb_init->suspend_action_cb;
  usb_mapping.resume_action_cb = usb_init->resume_action_cb;

  /* Start USB stack to authorize VBus monitoring */
  udc_start();
}

int inv_usb_hid_mouse_move(int8_t moveX, int8_t moveY) {
  if (udi_hid_mouse_moveXY(moveX, moveY))
    return 0;
  else
    return -1;
}

int inv_usb_hid_mouse_button_click(bool click_left, bool click_right) {
  if (udi_hid_mouse_btnleft(click_left) && udi_hid_mouse_btnright(click_right))
    return 0;
  else
    return -1;
}

/****************************** Callback Functions
 * ******************************/

void user_callback_suspend_action(void) {
  if (usb_mapping.suspend_action_cb != NULL)
    usb_mapping.suspend_action_cb();
}

void user_callback_resume_action(void) {
  if (usb_mapping.resume_action_cb != NULL)
    usb_mapping.resume_action_cb();
}
