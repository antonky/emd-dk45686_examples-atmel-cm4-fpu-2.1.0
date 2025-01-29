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

#include "frontend.h"
#include "system_interface.h"

/* Math */
#include <math.h>
#include <stdio.h>

#define RAD_TO_DEG(rad) ((float)rad * 57.2957795131)

/* Printing period (to prevent terminal overload) */
#define PRINT_PERIOD_US_SLOW 1000000 /* 1 s */
#define PRINT_PERIOD_US_FAST 20000   /* 20 ms */

/* Mask to print data through UART */
#define MASK_PRINT_INPUT_DATA 0x01     /** algorithm inputs */
#define MASK_PRINT_ACC_DATA 0x02       /** accel data */
#define MASK_PRINT_GYR_DATA 0x04       /** gyro data */
#define MASK_PRINT_MAG_DATA 0x08       /** magnetometer data */
#define MASK_PRINT_6AXIS_DATA 0x10     /** 6-axis data */
#define MASK_PRINT_9AXIS_DATA 0x20     /** 9-axis data */
#define MASK_PRINT_GRAVITY_DATA 0x40   /** Gravity vector */
#define MASK_PRINT_LINEARACC_DATA 0x80 /** Linear acceleration vector */

/* Output data to print */
static uint32_t data_to_print;

/* Callback to be called when command is received */
int (*command_cb)(inv_commands cmd);

/* Keep track of when we printed the last event to prevent overloading UART
 * output */
static uint64_t time_of_last_print_us;
static uint64_t print_period_us;

/* Static functions definition */
static void fixedpoint_to_float(const int32_t *in, float *out,
                                const uint8_t fxp_shift, const uint8_t dim);
static void quaternions_to_angles(const float quat[4], float angles[3]);
static void print_help(void);

void init_frontend(int (*cmd_cb)(inv_commands cmd)) {
  /* Configure UART for log */
  si_config_uart_for_print(SI_UART_ID_FTDI, MSG_LEVEL);

  command_cb = cmd_cb;

  /* Print accel, gyro, mag, 6-axis and 9-axis by default */
  data_to_print = MASK_PRINT_ACC_DATA | MASK_PRINT_GYR_DATA |
                  MASK_PRINT_MAG_DATA | MASK_PRINT_6AXIS_DATA |
                  MASK_PRINT_9AXIS_DATA;

  time_of_last_print_us = 0;
  print_period_us = PRINT_PERIOD_US_SLOW;
}

void notify_data(const uint64_t time, const InvnAlgoAGMInput *input,
                 const InvnAlgoAGMOutput *output) {
  (void)time;
  uint64_t current_time_us = si_get_time_us();
  uint64_t delay_since_last_print_us = current_time_us - time_of_last_print_us;

  /*
   * Handle case where last print is in the future (can happen to freeze UART
   * output for some time, for instance when printing help.
   */
  if (current_time_us < time_of_last_print_us)
    delay_since_last_print_us = 0;

  if (delay_since_last_print_us >= print_period_us) {
    /* Print carriage return to ease reading, only if some data are printed */
    if (data_to_print)
      INV_MSG(INV_MSG_LEVEL_INFO, "");

    /* Print input */
    if (data_to_print & MASK_PRINT_INPUT_DATA) {
      /* IMU data */
      INV_MSG(INV_MSG_LEVEL_INFO,
              "%lld: INPUT  RAcc=[%d, %d, %d] RGyr=[%d, %d, %d] Rtemp=[%d]",
              input->sRimu_time_us, input->sRacc_data[0], input->sRacc_data[1],
              input->sRacc_data[2], input->sRgyr_data[0], input->sRgyr_data[1],
              input->sRgyr_data[2], (int32_t)input->sRtemp_data);

      /* Mag data */
      if (command_cb(IS_MAG_INIT_SUCCESSFUL)) {
        INV_MSG(INV_MSG_LEVEL_INFO, "%lld: INPUT  RMag=[%d, %d, %d]",
                input->sRmag_time_us, input->sRmag_data[0],
                input->sRmag_data[1], input->sRmag_data[2]);
      }
    }

    /* Print output */

    /* Accel */
    if (data_to_print & MASK_PRINT_ACC_DATA) {
      float acc_g[3];
      float acc_bias[3];

      fixedpoint_to_float(output->acc_cal_q16, acc_g, 16, 3);
      fixedpoint_to_float(output->acc_bias_q16, acc_bias, 16, 3);

      INV_MSG(INV_MSG_LEVEL_INFO,
              "%lld: OUTPUT Acc=[%.3f, %.3f, %.3f]g AccBias=[%.3f, %.3f, "
              "%.3f]mg Accuracy=%d",
              input->sRimu_time_us, acc_g[0], acc_g[1], acc_g[2],
              acc_bias[0] * 1000, acc_bias[1] * 1000, acc_bias[2] * 1000,
              (int32_t)output->acc_accuracy_flag);
    }

    /* Gyro */
    if (data_to_print & MASK_PRINT_GYR_DATA) {
      float gyr_dps[3];
      float gyr_bias[3];
      float temp;

      fixedpoint_to_float(output->gyr_cal_q16, gyr_dps, 16, 3);
      fixedpoint_to_float(output->gyr_bias_q16, gyr_bias, 16, 3);
      fixedpoint_to_float(&output->temp_degC_q16, &temp, 16, 1);

      INV_MSG(INV_MSG_LEVEL_INFO,
              "%lld: OUTPUT Gyr=[%.3f, %.3f, %.3f]dps GyrBias=[%.3f, %.3f, "
              "%.3f]dps Temp=[%.2f]C Accuracy=%d",
              input->sRimu_time_us, gyr_dps[0], gyr_dps[1], gyr_dps[2],
              gyr_bias[0], gyr_bias[1], gyr_bias[2], temp,
              (int32_t)output->gyr_accuracy_flag);
    }

    /* Mag */
    if (command_cb(IS_MAG_INIT_SUCCESSFUL) &&
        (data_to_print & MASK_PRINT_MAG_DATA)) {
      float mag_cal[3];
      float mag_bias[3];

      fixedpoint_to_float(output->mag_cal_q16, mag_cal, 16, 3);
      fixedpoint_to_float(output->mag_bias_q16, mag_bias, 16, 3);

      INV_MSG(INV_MSG_LEVEL_INFO,
              "%lld: OUTPUT Mag=[%.3f, %.3f, %.3f]uT MagBias=[%.3f, %.3f, "
              "%.3f]uT Accuracy=%d",
              input->sRmag_time_us, mag_cal[0], mag_cal[1], mag_cal[2],
              mag_bias[0], mag_bias[1], mag_bias[2], output->mag_accuracy_flag);
    }

    /* 6-axis Sensor Fusion */
    if (data_to_print & MASK_PRINT_6AXIS_DATA) {
      float grv_quat[4];
      float angles_deg_grv[3];

      fixedpoint_to_float(output->grv_quat_q30, grv_quat, 30, 4);
      quaternions_to_angles(grv_quat, angles_deg_grv);

      INV_MSG(INV_MSG_LEVEL_INFO, "%lld: OUTPUT 6Axis=[%f, %f, %f, %f]",
              input->sRimu_time_us, grv_quat[0], grv_quat[1], grv_quat[2],
              grv_quat[3]);
      INV_MSG(INV_MSG_LEVEL_INFO,
              "%lld: OUTPUT Euler6Axis=[%.2f, %.2f, %.2f]deg",
              input->sRimu_time_us, angles_deg_grv[0], angles_deg_grv[1],
              angles_deg_grv[2]);
    }

    if (command_cb(IS_MAG_INIT_SUCCESSFUL)) {
      float rv_heading_accuracy =
          RAD_TO_DEG((float)output->rv_accuracy_q27 / (1 << 27));

      /* 9-axis Sensor Fusion */
      if (data_to_print & MASK_PRINT_9AXIS_DATA) {
        float rv_quat[4];
        float angles_deg_rv[3];

        fixedpoint_to_float(output->rv_quat_q30, rv_quat, 30, 4);
        quaternions_to_angles(rv_quat, angles_deg_rv);

        INV_MSG(INV_MSG_LEVEL_INFO,
                "%lld: OUTPUT 9Axis=[%f, %f, %f, %f] 9AxisAccuracy=[%f]deg",
                input->sRimu_time_us, rv_quat[0], rv_quat[1], rv_quat[2],
                rv_quat[3], rv_heading_accuracy);

        INV_MSG(INV_MSG_LEVEL_INFO,
                "%lld: OUTPUT Euler9Axis=[%.2f, %.2f, %.2f]deg "
                "9AxisAccuracy=[%f]deg",
                input->sRimu_time_us, angles_deg_rv[0], angles_deg_rv[1],
                angles_deg_rv[2], rv_heading_accuracy);
      }
    }

    /* Gravity */
    if (data_to_print & MASK_PRINT_GRAVITY_DATA) {
      float gravity[3];

      fixedpoint_to_float(output->gravity_q16, gravity, 16, 3);

      INV_MSG(INV_MSG_LEVEL_INFO,
              "%lld: OUTPUT Gravity=[%f, %f, %f] Accuracy=%d",
              input->sRimu_time_us, gravity[0], gravity[1], gravity[2],
              output->acc_accuracy_flag);
    }

    if (data_to_print & MASK_PRINT_LINEARACC_DATA) {
      float linear_acc[3];

      fixedpoint_to_float(output->linear_acc_q16, linear_acc, 16, 3);

      INV_MSG(INV_MSG_LEVEL_INFO,
              "%lld: OUTPUT LinearAcc=[%f, %f, %f] Accuracy=%d",
              input->sRimu_time_us, linear_acc[0], linear_acc[1], linear_acc[2],
              output->acc_accuracy_flag);
    }

    time_of_last_print_us = current_time_us;
  }
}

int check_received_command(void) {
  int rc = 0;
  char cmd = 0;

  rc |= si_get_uart_command(SI_UART_ID_FTDI, &cmd);
  SI_CHECK_RC(rc);

  /* Verify if a callback is registered */
  if (command_cb == 0) {
    INV_MSG(INV_MSG_LEVEL_ERROR,
            "/!\\No callback registered, can't process commands");
    return -1;
  }

  switch (cmd) {
  case 'i': /* Print input data */
    data_to_print ^= MASK_PRINT_INPUT_DATA;
    break;
  case 'a': /* Print accel data */
    data_to_print ^= MASK_PRINT_ACC_DATA;
    break;
  case 'g': /* Print gyro data */
    data_to_print ^= MASK_PRINT_GYR_DATA;
    break;
  case 'm': /* Print mag data */
    if (command_cb(IS_MAG_INIT_SUCCESSFUL))
      data_to_print ^= MASK_PRINT_MAG_DATA;
    else {
      INV_MSG(INV_MSG_LEVEL_INFO, "Unknown command : %c", cmd);
      print_help();
    }
    break;
  case '9': /* Print 9 axis data */
    if (command_cb(IS_MAG_INIT_SUCCESSFUL))
      data_to_print ^= MASK_PRINT_9AXIS_DATA;
    else {
      INV_MSG(INV_MSG_LEVEL_INFO, "Unknown command : %c", cmd);
      print_help();
    }
    break;
  case '6': /* Print 6 axis data */
    data_to_print ^= MASK_PRINT_6AXIS_DATA;
    break;
  case 'G': /* Print gravity data */
    data_to_print ^= MASK_PRINT_GRAVITY_DATA;
    break;
  case 'l': /* Print linear acceleration data */
    data_to_print ^= MASK_PRINT_LINEARACC_DATA;
    break;
  case 's': /* Configure printing period to 'slow' (1 s) */
    print_period_us = PRINT_PERIOD_US_SLOW;
    break;
  case 'f': /* Configure printing period to 'fast' (20 ms) */
    print_period_us = PRINT_PERIOD_US_FAST;
    break;
  case 'R': /* Reset algo */
    rc |= command_cb(RESET_AGM);
    SI_CHECK_RC(rc);
    break;
  case 'h':
  case 'H':
    print_help();
    break;
  case 0: /* No command received */
    break;
  default:
    INV_MSG(INV_MSG_LEVEL_INFO, "Unknown command : %c", cmd);
    print_help();
    break;
  }

  return rc;
}

static void print_help(void) {
  INV_MSG(INV_MSG_LEVEL_INFO, "#");
  INV_MSG(INV_MSG_LEVEL_INFO, "# Help");
  INV_MSG(INV_MSG_LEVEL_INFO, "#");
  INV_MSG(INV_MSG_LEVEL_INFO,
          "# 'i' : print input data (raw accel, raw gyro and raw mag)");
  INV_MSG(INV_MSG_LEVEL_INFO, "# 'a' : print calibrated accel data");
  INV_MSG(INV_MSG_LEVEL_INFO, "# 'g' : print calibrated gyro data");
  if (command_cb(IS_MAG_INIT_SUCCESSFUL)) {
    INV_MSG(INV_MSG_LEVEL_INFO, "# 'm' : print calibrated mag data");
    INV_MSG(INV_MSG_LEVEL_INFO,
            "# '9' : print 9-axis quaternion and eulers angles (RV)");
  }
  INV_MSG(INV_MSG_LEVEL_INFO,
          "# '6' : print 6-axis quaternion and eulers angles (GRV)");
  INV_MSG(INV_MSG_LEVEL_INFO,
          "# 'G' : print gravity estimation in sensor frame");
  INV_MSG(INV_MSG_LEVEL_INFO,
          "# 'l' : print linear acceleration estimation in sensor frame");
  INV_MSG(INV_MSG_LEVEL_INFO,
          "# 'f' : configure printing period to 'fast' (20 ms)");
  INV_MSG(INV_MSG_LEVEL_INFO,
          "# 's' : configure printing period to 'slow' (1 s)");
  INV_MSG(INV_MSG_LEVEL_INFO, "# 'R' : reset biases and accuracies");
  INV_MSG(INV_MSG_LEVEL_INFO, "# 'h' : print this helper");

  /* Give user some time to read */
  INV_MSG(INV_MSG_LEVEL_INFO, "Pausing UART output for 5 s");
  time_of_last_print_us = si_get_time_us() + 5000000;
}

static void fixedpoint_to_float(const int32_t *in, float *out,
                                const uint8_t fxp_shift, const uint8_t dim) {
  int i;
  float scale = 1.f / (1 << fxp_shift);

  for (i = 0; i < dim; i++)
    out[i] = scale * in[i];
}

static void quaternions_to_angles(const float quat[4], float angles[3]) {
  const float RAD_2_DEG = (180.f / 3.14159265358979f);
  float rot_matrix[9];

  // quaternion to rotation matrix
  const float dTx = 2.0f * quat[1];
  const float dTy = 2.0f * quat[2];
  const float dTz = 2.0f * quat[3];
  const float dTwx = dTx * quat[0];
  const float dTwy = dTy * quat[0];
  const float dTwz = dTz * quat[0];
  const float dTxx = dTx * quat[1];
  const float dTxy = dTy * quat[1];
  const float dTxz = dTz * quat[1];
  const float dTyy = dTy * quat[2];
  const float dTyz = dTz * quat[2];
  const float dTzz = dTz * quat[3];

  rot_matrix[0] = 1.0f - (dTyy + dTzz);
  rot_matrix[1] = dTxy - dTwz;
  rot_matrix[2] = dTxz + dTwy;
  rot_matrix[3] = dTxy + dTwz;
  rot_matrix[4] = 1.0f - (dTxx + dTzz);
  rot_matrix[5] = dTyz - dTwx;
  rot_matrix[6] = dTxz - dTwy;
  rot_matrix[7] = dTyz + dTwx;
  rot_matrix[8] = 1.0f - (dTxx + dTyy);

  angles[0] = atan2f(-rot_matrix[3], rot_matrix[0]) * RAD_2_DEG;
  angles[1] = atan2f(-rot_matrix[7], rot_matrix[8]) * RAD_2_DEG;
  angles[2] = asinf(-rot_matrix[6]) * RAD_2_DEG;
}
