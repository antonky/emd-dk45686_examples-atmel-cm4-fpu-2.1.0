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

/* Algorithm */
#include "invn_algo_agm.h"

/* Board drivers */
#include "system_interface.h"

/* std */
#include <stdio.h>
#include <string.h>

/*
 * This example aims at verifying that the AGM library is properly working by
 * replaying a test vector and verifying the algo generates an identical output.
 * Two test vectors are provided but due to memory limitation, only one can be
 * activated (testing the second one will require a rebuild).
 */

/* Definition of the test vector */
#define TIME_IDX 0
#define RACC_X_IDX 1
#define RACC_Y_IDX 2
#define RACC_Z_IDX 3
#define RGYR_X_IDX 4
#define RGYR_Y_IDX 5
#define RGYR_Z_IDX 6
#define RTEMP_IDX 7
#define RMAG_X_IDX 8
#define RMAG_Y_IDX 9
#define RMAG_Z_IDX 10
#define RV_W_IDX 11
#define RV_X_IDX 12
#define RV_Y_IDX 13
#define RV_Z_IDX 14
#define ACC_BIAS_X_IDX 15
#define ACC_BIAS_Y_IDX 16
#define ACC_BIAS_Z_IDX 17
#define GYR_BIAS_X_IDX 18
#define GYR_BIAS_Y_IDX 19
#define GYR_BIAS_Z_IDX 20
#define MAG_BIAS_X_IDX 21
#define MAG_BIAS_Y_IDX 22
#define MAG_BIAS_Z_IDX 23
#define NUM_COLUMN 24

/*
 * Sanity test vector
 */
#define TEST_NAME "out_invn_agm_1"
#define ACC_FSR 32
#define GYR_FSR 4000
static const int32_t test_vector[][NUM_COLUMN] = {
#include "test_vector/out_invn_agm_1.h"
};

/* Static functions definition */
static int setup_mcu();
static int check_output(int32_t expected_output, int32_t output,
                        const char *str, int line);

/* Main function implementation */
int main(void) {
  int rc = 0;
  InvnAlgoAGMStruct agm;
  InvnAlgoAGMInput input;
  InvnAlgoAGMOutput output;
  InvnAlgoAGMConfig config;

  rc |= setup_mcu();
  SI_CHECK_RC(rc);

  INV_MSG(INV_MSG_LEVEL_INFO, "###");
  INV_MSG(INV_MSG_LEVEL_INFO, "### Example Sanity AGM");
  INV_MSG(INV_MSG_LEVEL_INFO, "###");

  /* Init AGM algo */
  memset(&input, 0, sizeof(input));
  memset(&output, 0, sizeof(output));
  memset(&config, 0, sizeof(config));

  rc |= invn_algo_agm_generate_config(&config, INVN_ALGO_AGM_MOBILE);
  config.acc_fsr = ACC_FSR;
  config.gyr_fsr = GYR_FSR;
  config.acc_odr_us = 10000;
  config.gyr_odr_us = 10000;
  config.mag_odr_us = 10000;
  config.mag_sc_q16 = 9830; // 0.15 uT/LSB
  config.temp_offset = 25 << 16;
  config.temp_sensitivity = (int32_t)((int64_t)((int64_t)100 << 30) / 13248);
  rc |= invn_algo_agm_init(&agm, &config);
  SI_CHECK_RC(rc);

  INV_MSG(INV_MSG_LEVEL_INFO, "Running '%s' test", TEST_NAME);

  for (uint32_t i = 0;
       i < (sizeof(test_vector) / (NUM_COLUMN * sizeof(int32_t))); i++) {
    InvnAlgoAGMOutput expected_output;

    /* Fill input structure */
    input.mask = 7;
    input.sRimu_time_us = test_vector[i][TIME_IDX];
    input.sRacc_data[0] = test_vector[i][RACC_X_IDX];
    input.sRacc_data[1] = test_vector[i][RACC_Y_IDX];
    input.sRacc_data[2] = test_vector[i][RACC_Z_IDX];
    input.sRgyr_data[0] = test_vector[i][RGYR_X_IDX];
    input.sRgyr_data[1] = test_vector[i][RGYR_Y_IDX];
    input.sRgyr_data[2] = test_vector[i][RGYR_Z_IDX];
    input.sRtemp_data = test_vector[i][RTEMP_IDX];
    input.sRmag_data[0] = test_vector[i][RMAG_X_IDX];
    input.sRmag_data[1] = test_vector[i][RMAG_Y_IDX];
    input.sRmag_data[2] = test_vector[i][RMAG_Z_IDX];

    /* Fill expected output structure */
    expected_output.rv_quat_q30[0] = test_vector[i][RV_W_IDX];
    expected_output.rv_quat_q30[1] = test_vector[i][RV_X_IDX];
    expected_output.rv_quat_q30[2] = test_vector[i][RV_Y_IDX];
    expected_output.rv_quat_q30[3] = test_vector[i][RV_Z_IDX];
    expected_output.acc_bias_q16[0] = test_vector[i][ACC_BIAS_X_IDX];
    expected_output.acc_bias_q16[1] = test_vector[i][ACC_BIAS_Y_IDX];
    expected_output.acc_bias_q16[2] = test_vector[i][ACC_BIAS_Z_IDX];
    expected_output.gyr_bias_q16[0] = test_vector[i][GYR_BIAS_X_IDX];
    expected_output.gyr_bias_q16[1] = test_vector[i][GYR_BIAS_Y_IDX];
    expected_output.gyr_bias_q16[2] = test_vector[i][GYR_BIAS_Z_IDX];
    expected_output.mag_bias_q16[0] = test_vector[i][MAG_BIAS_X_IDX];
    expected_output.mag_bias_q16[1] = test_vector[i][MAG_BIAS_Y_IDX];
    expected_output.mag_bias_q16[2] = test_vector[i][MAG_BIAS_Z_IDX];

    /* run algo */
    invn_algo_agm_process(&agm, &input, &output);

    /* Check output */
    rc |= check_output(expected_output.rv_quat_q30[0], output.rv_quat_q30[0],
                       "rv_quat_q30[0]", i);
    rc |= check_output(expected_output.rv_quat_q30[1], output.rv_quat_q30[1],
                       "rv_quat_q30[1]", i);
    rc |= check_output(expected_output.rv_quat_q30[2], output.rv_quat_q30[2],
                       "rv_quat_q30[2]", i);
    rc |= check_output(expected_output.rv_quat_q30[3], output.rv_quat_q30[3],
                       "rv_quat_q30[3]", i);
    rc |= check_output(expected_output.acc_bias_q16[0], output.acc_bias_q16[0],
                       "acc_bias_q16[0]", i);
    rc |= check_output(expected_output.acc_bias_q16[1], output.acc_bias_q16[1],
                       "acc_bias_q16[1]", i);
    rc |= check_output(expected_output.acc_bias_q16[2], output.acc_bias_q16[2],
                       "acc_bias_q16[2]", i);
    rc |= check_output(expected_output.gyr_bias_q16[0], output.gyr_bias_q16[0],
                       "gyr_bias_q16[0]", i);
    rc |= check_output(expected_output.gyr_bias_q16[1], output.gyr_bias_q16[1],
                       "gyr_bias_q16[1]", i);
    rc |= check_output(expected_output.gyr_bias_q16[2], output.gyr_bias_q16[2],
                       "gyr_bias_q16[2]", i);
    rc |= check_output(expected_output.mag_bias_q16[0], output.mag_bias_q16[0],
                       "mag_bias_q16[0]", i);
    rc |= check_output(expected_output.mag_bias_q16[1], output.mag_bias_q16[1],
                       "mag_bias_q16[1]", i);
    rc |= check_output(expected_output.mag_bias_q16[2], output.mag_bias_q16[2],
                       "mag_bias_q16[2]", i);

    /* Break loop if an error is detected */
    if (rc != 0)
      break;
  }
  INV_MSG(INV_MSG_LEVEL_INFO, "   > %s", rc == 0 ? "SUCCESS" : "FAILURE");

  return rc;
}

/* Initializes MCU peripherals. */
static int setup_mcu() {
  int rc = 0;

  rc |= si_board_init();

  /* Configure UART for log */
  si_config_uart_for_print(SI_UART_ID_FTDI, INV_MSG_LEVEL_DEBUG);

  /* Init timer peripheral for sleep and get_time */
  rc |= si_init_timers();

  return rc;
}

static int check_output(int32_t expected_output, int32_t output,
                        const char *str, int line) {
  if (expected_output != output) {
    INV_MSG(INV_MSG_LEVEL_ERROR,
            "   > /!\\ Error on `%s` at line %d: got %d instead of %d", str,
            line, output, expected_output);

    // Sleep 100 ms to ensure trace is properly printed
    si_sleep_us(100000);

    return -1;
  }

  return 0;
}
