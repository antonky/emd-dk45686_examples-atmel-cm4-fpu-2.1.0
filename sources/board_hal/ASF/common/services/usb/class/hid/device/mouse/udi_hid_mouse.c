/**
 * \file
 *
 * \brief USB Device Human Interface Device (HID) mouse interface.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip
 * Support</a>
 */

#include "udi_hid_mouse.h"
#include "conf_usb.h"
#include "udc.h"
#include "udd.h"
#include "udi_hid.h"
#include "usb_protocol.h"
#include <string.h>

/**
 * \ingroup udi_hid_mouse_group
 * \defgroup udi_hid_mouse_group_udc Interface with USB Device Core (UDC)
 *
 * Structures and functions required by UDC.
 *
 * @{
 */
bool udi_hid_mouse_enable(void);
void udi_hid_mouse_disable(void);
bool udi_hid_mouse_setup(void);
uint8_t udi_hid_mouse_getsetting(void);

//! Global structure which contains standard UDI interface for UDC
UDC_DESC_STORAGE udi_api_t udi_api_hid_mouse = {
    .enable = (bool (*)(void))udi_hid_mouse_enable,
    .disable = (void (*)(void))udi_hid_mouse_disable,
    .setup = (bool (*)(void))udi_hid_mouse_setup,
    .getsetting = (uint8_t (*)(void))udi_hid_mouse_getsetting,
    .sof_notify = NULL,
};
//@}

/**
 * \ingroup udi_hid_mouse_group
 * \defgroup udi_hid_mouse_group_internal Implementation of UDI HID Mouse
 *
 * Class internal implementation
 * @{
 */

/**
 * \name Internal defines and variables to manage HID mouse
 */
//@{

//! Size of report for standard HID mouse
#define UDI_HID_MOUSE_REPORT_SIZE 4
//! To store current rate of HID mouse
COMPILER_WORD_ALIGNED
static uint8_t udi_hid_mouse_rate;
//! To store current protocol of HID mouse
COMPILER_WORD_ALIGNED
static uint8_t udi_hid_mouse_protocol;
//! To signal if a valid report is ready to send
static bool udi_hid_mouse_b_report_valid;
//! Report ready to send
static uint8_t udi_hid_mouse_report[UDI_HID_MOUSE_REPORT_SIZE];
//! Signal if a report transfer is on going
static bool udi_hid_mouse_report_trans_ongoing;
//! Buffer used to send report
COMPILER_WORD_ALIGNED
static uint8_t udi_hid_mouse_report_trans[UDI_HID_MOUSE_REPORT_SIZE];

/**
 * \brief Callback for set report setup request
 *
 * \return \c 1 always, because it is not used on mouse interface
 */
static bool udi_hid_mouse_setreport(void);

//@}

//! HID report descriptor for standard HID mouse
UDC_DESC_STORAGE udi_hid_mouse_report_desc_t udi_hid_mouse_report_desc = {{
    0x05, 0x01, /* Usage Page (Generic Desktop),       */
    0x09, 0x02, /* Usage (Mouse),                      */
    0xA1, 0x01, /*  Collection (Application),          */
    0x09, 0x01, /*   Usage (Pointer),                  */
    0xA1, 0x00, /*  Collection (Physical),             */
    0x05, 0x09, /*     Usage Page (Buttons),           */
    0x19, 0x01, /*     Usage Minimum (01),             */
    0x29, 0x03, /*     Usage Maximum (03),             */
    0x15, 0x00, /*     Logical Minimum (0),            */
    0x25, 0x01, /*     Logical Maximum (1),            */
    0x75, 0x01, /*     Report Size (1),                */
    0x95, 0x03, /*     Report Count (3),               */
    0x81, 0x02, /*     Input (Data, Variable, Absolute) */
    0x75, 0x05, /*     Report Size (5),                */
    0x95, 0x01, /*     Report Count (1),               */
    0x81, 0x01, /*     Input (Constant),               */
    0x05, 0x01, /*     Usage Page (Generic Desktop),   */
    0x09, 0x30, /*     Usage (X),                      */
    0x09, 0x31, /*     Usage (Y),                      */
    0x09, 0x38, /*     Usage (Scroll),                 */
    0x15, 0x81, /*     Logical Minimum (-127),         */
    0x25, 0x7F, /*     Logical Maximum (127),          */
    0x75, 0x08, /*     Report Size (8),                */
    0x95, 0x03, /*     Report Count (3),               */
    0x81, 0x06, /*     Input (Data, Variable, Relative) */
    0xC0,       /*  End Collection,                    */
    0xC0,       /* End Collection                      */
}};

/**
 * \name Internal routines
 */
//@{

/**
 * \brief Moves an axe
 *
 * \param pos           Signed value to move
 * \param index_report  Index of report to move
 *								(3=scroll wheel,
 *2=axe Y, 1=axe X))
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
static bool udi_hid_mouse_move(int8_t pos, uint8_t index_report);

/**
 * \brief Changes a button state
 *
 * \param b_state    New button state
 * \param btn        Index of button to change (4=middle, 2=right, 1=left)
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
static bool udi_hid_mouse_btn(bool b_state, uint8_t btn);

/**
 * \brief Send the report
 *
 * \return \c 1 if send on going, \c 0 if delay.
 */
static bool udi_hid_mouse_send_report(void);

/**
 * \brief Callback called when the report is sent
 *
 * \param status     UDD_EP_TRANSFER_OK, if transfer finish
 * \param status     UDD_EP_TRANSFER_ABORT, if transfer aborted
 * \param nb_sent    number of data transfered
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
static void udi_hid_mouse_report_sent(udd_ep_status_t status,
                                      iram_size_t nb_sent, udd_ep_id_t ep);

//@}

//--------------------------------------------
//------ Interface for UDI HID level

bool udi_hid_mouse_enable(void) {
  // Initialize internal value
  udi_hid_mouse_rate = 0;
  udi_hid_mouse_protocol = 0;
  udi_hid_mouse_report_trans_ongoing = false;
  memset(udi_hid_mouse_report, 0, UDI_HID_MOUSE_REPORT_SIZE);
  udi_hid_mouse_b_report_valid = false;
  return UDI_HID_MOUSE_ENABLE_EXT();
}

void udi_hid_mouse_disable(void) { UDI_HID_MOUSE_DISABLE_EXT(); }

bool udi_hid_mouse_setup(void) {
  return udi_hid_setup(&udi_hid_mouse_rate, &udi_hid_mouse_protocol,
                       (uint8_t *)&udi_hid_mouse_report_desc,
                       udi_hid_mouse_setreport);
}

uint8_t udi_hid_mouse_getsetting(void) { return 0; }

static bool udi_hid_mouse_setreport(void) { return false; }

//--------------------------------------------
//------ Interface for application

bool udi_hid_mouse_moveScroll(int8_t pos) { return udi_hid_mouse_move(pos, 3); }

bool udi_hid_mouse_moveY(int8_t pos_y) { return udi_hid_mouse_move(pos_y, 2); }

bool udi_hid_mouse_moveX(int8_t pos_x) { return udi_hid_mouse_move(pos_x, 1); }

bool udi_hid_mouse_moveXY(int8_t pos_x, int8_t pos_y) {
  int16_t s16_newpos_x, s16_newpos_y;

  irqflags_t flags = cpu_irq_save();

  // Add position in HID mouse report
  s16_newpos_x = (int8_t)udi_hid_mouse_report[1];
  s16_newpos_x += pos_x;
  s16_newpos_y = (int8_t)udi_hid_mouse_report[2];
  s16_newpos_y += pos_y;
  if ((-127 > s16_newpos_x) || (127 < s16_newpos_x) || (-127 > s16_newpos_y) ||
      (127 < s16_newpos_y)) {
    cpu_irq_restore(flags);
    return false; // Overflow of report
  }
  udi_hid_mouse_report[1] = (uint8_t)s16_newpos_x;
  udi_hid_mouse_report[2] = (uint8_t)s16_newpos_y;

  // Valid and send report
  udi_hid_mouse_b_report_valid = true;
  udi_hid_mouse_send_report();

  cpu_irq_restore(flags);
  return true;
}

bool udi_hid_mouse_btnmiddle(bool b_state) {
  return udi_hid_mouse_btn(b_state, 0x04);
}

bool udi_hid_mouse_btnright(bool b_state) {
  return udi_hid_mouse_btn(b_state, 0x02);
}

bool udi_hid_mouse_btnleft(bool b_state) {
  return udi_hid_mouse_btn(b_state, 0x01);
}

//--------------------------------------------
//------ Internal routines

static bool udi_hid_mouse_move(int8_t pos, uint8_t index_report) {
  int16_t s16_newpos;

  irqflags_t flags = cpu_irq_save();

  // Add position in HID mouse report
  s16_newpos = (int8_t)udi_hid_mouse_report[index_report];
  s16_newpos += pos;
  if ((-127 > s16_newpos) || (127 < s16_newpos)) {
    cpu_irq_restore(flags);
    return false; // Overflow of report
  }
  udi_hid_mouse_report[index_report] = (uint8_t)s16_newpos;

  // Valid and send report
  udi_hid_mouse_b_report_valid = true;
  udi_hid_mouse_send_report();

  cpu_irq_restore(flags);
  return true;
}

static bool udi_hid_mouse_btn(bool b_state, uint8_t btn) {
  // Modify buttons report
  if (HID_MOUSE_BTN_DOWN == b_state)
    udi_hid_mouse_report[0] |= btn;
  else
    udi_hid_mouse_report[0] &= ~(unsigned)btn;
  // Use mouse move routine
  return udi_hid_mouse_move(0, 1);
}

static bool udi_hid_mouse_send_report(void) {
  if (udi_hid_mouse_report_trans_ongoing)
    return false; // Transfer on going then send this one after transfer
                  // complete

  // Copy report on other array used only for transfer
  memcpy(udi_hid_mouse_report_trans, udi_hid_mouse_report,
         UDI_HID_MOUSE_REPORT_SIZE);
  memset(&udi_hid_mouse_report[1], 0, 3); // Keep status of btn for next report
  udi_hid_mouse_b_report_valid = false;

  // Send report
  udi_hid_mouse_report_trans_ongoing =
      udd_ep_run(UDI_HID_MOUSE_EP_IN, false, udi_hid_mouse_report_trans,
                 UDI_HID_MOUSE_REPORT_SIZE, udi_hid_mouse_report_sent);
  return udi_hid_mouse_report_trans_ongoing;
}

static void udi_hid_mouse_report_sent(udd_ep_status_t status,
                                      iram_size_t nb_sent, udd_ep_id_t ep) {
  UNUSED(ep);
  UNUSED(status);
  UNUSED(nb_sent);
  // Valid report sending
  udi_hid_mouse_report_trans_ongoing = false;
  if (udi_hid_mouse_b_report_valid) {
    // Send new valid report
    udi_hid_mouse_send_report();
  }
}

//@}
