/*
 *
 * Copyright (c) [2020] by InvenSense, Inc.
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

#ifndef __FRONTEND_H__
#define __FRONTEND_H__

/* InvenSense algorithm */
#include "invn_algo_agm.h"

/*
 * Define msg level
 */
#define MSG_LEVEL INV_MSG_LEVEL_INFO

/*
 * Enum for possible commands from user
 */
typedef enum {
  RESET_AGM,
  IS_MAG_INIT_SUCCESSFUL,
  ENABLE_CALIBRATION_SAVING,
  DISABLE_CALIBRATION_SAVING,
} inv_commands;

/**
 * \brief This function will notify input and output to the user.
 * \param[in] time Current timestamp (not necessarily accurate, just for
 * reference).
 * \param[in] input Pointer to algorithm input structure.
 * \param[in] output Pointer to algorithm output structure.
 */
void notify_data(const uint64_t time, const InvnAlgoAGMInput *input,
                 const InvnAlgoAGMOutput *output);

/**
 * \brief This function initializes the callback that will be called when a
 * command is received.
 * \param[in] fun The function to be called when a command is received.
 */
void init_frontend(int (*cmd_cb)(inv_commands cmd));

/**
 * \brief This function verifies if a command is pending and processes it if it
 * is.
 */
int check_received_command();

#endif /* !__FRONTEND_H__ */
