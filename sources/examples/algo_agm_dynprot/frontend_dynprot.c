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

/* InvenSense utils */
#include "Invn/DynamicProtocol/DynProtocol.h"
#include "Invn/DynamicProtocol/DynProtocolTransportUart.h"
#include "Invn/EmbUtils/Message.h"
#include "Invn/InvError.h"

/* Board drivers */
#include "uart_mngr.h"

/* Math */
#include <math.h>
#include <stdio.h>
#include <string.h>

/*
 * Frontend configuration
 */

/*
 * Callback to be called when command is received
 */
int (*command_cb)(inv_commands cmd);

/*
 * Static variables
 * Dynamic protocol and transport handles
 */
static DynProtocol_t protocol;
static DynProTransportUart_t transport;

static struct {
  uint8_t acc_en;
  uint8_t mag_en;
  uint8_t gyr_en;
  uint8_t temp_en;
  uint8_t rv_en;
  uint8_t umag_en;
  uint8_t grv_en;
  uint8_t ugyr_en;
  uint8_t racc_en;
  uint8_t rgyr_en;
  uint8_t rmag_en;
  uint8_t rtemp_en;
  uint8_t linacc_en;
  uint8_t gra_en;
} self;

/*
 * Used to artificially increase resolution of gyro and mag bias through UCAL
 * sensors. Default to 1, can be changed with sensorcli (`setconfig gyr
 * 32=mult`). See `handle_command` function for details.
 */
static int32_t biases_multiplier;

/*
 * Static functions definition
 */
static void transport_event_cb(enum DynProTransportEvent e,
                               union DynProTransportEventData data,
                               void *cookie);
static void protocol_event_cb(enum DynProtocolEtype etype,
                              enum DynProtocolEid eid,
                              const DynProtocolEdata_t *edata, void *cookie);
static int handle_command(enum DynProtocolEid eid,
                          const DynProtocolEdata_t *edata,
                          DynProtocolEdata_t *respdata);
static int send_dp_data(DynProtocolEdata_t *dp_data);

void init_frontend(int (*cmd_cb)(inv_commands cmd)) {
  memset(&self, 0, sizeof(self));

  /* Init biases multiplier to 1 */
  biases_multiplier = 1;

  /* Init UART (EDBG, 921600 baud, 8bits, no parity) */
  si_config_uart_for_print(SI_UART_ID_EDBG, MSG_LEVEL);

  /* Init UART (FTDI, 2000000 baud, 8bits, no parity, RTS/CTS) */
  si_config_uart_for_bin(SI_UART_ID_FTDI);

  /* Assign command callback */
  command_cb = cmd_cb;

  /* Initialize Dynamic protocol */
  DynProTransportUart_init(&transport, transport_event_cb, 0);
  DynProtocol_init(&protocol, protocol_event_cb, 0);
}

void notify_data(const uint64_t time, const InvnAlgoAGMInput *input,
                 const InvnAlgoAGMOutput *output) {
  DynProtocolEdata_t dp_data;
  dp_data.d.async.sensorEvent.status = DYN_PRO_SENSOR_STATUS_DATA_UPDATED;
  dp_data.d.async.sensorEvent.vdata.base.timestamp = time;

  if (self.racc_en && (input->mask & INVN_ALGO_AGM_INPUT_MASK_ACC)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_RAW_ACCELEROMETER;
    dp_data.d.async.sensorEvent.vdata.data.u32[0] =
        (uint32_t)input->sRacc_data[0];
    dp_data.d.async.sensorEvent.vdata.data.u32[1] =
        (uint32_t)input->sRacc_data[1];
    dp_data.d.async.sensorEvent.vdata.data.u32[2] =
        (uint32_t)input->sRacc_data[2];
    send_dp_data(&dp_data);
  }

  if (self.rgyr_en && (input->mask & INVN_ALGO_AGM_INPUT_MASK_GYR)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_RAW_GYROSCOPE;
    dp_data.d.async.sensorEvent.vdata.data.u32[0] =
        (uint32_t)input->sRgyr_data[0];
    dp_data.d.async.sensorEvent.vdata.data.u32[1] =
        (uint32_t)input->sRgyr_data[1];
    dp_data.d.async.sensorEvent.vdata.data.u32[2] =
        (uint32_t)input->sRgyr_data[2];
    send_dp_data(&dp_data);
  }

  if (self.rtemp_en && (input->mask & INVN_ALGO_AGM_INPUT_MASK_ACC)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_RAW_TEMPERATURE;
    dp_data.d.async.sensorEvent.vdata.data.u32[0] =
        (uint32_t)input->sRtemp_data;
    send_dp_data(&dp_data);
  }

  if (self.rmag_en && (input->mask & INVN_ALGO_AGM_INPUT_MASK_MAG)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_RAW_MAGNETOMETER;
    dp_data.d.async.sensorEvent.vdata.data.u32[0] =
        (uint32_t)input->sRmag_data[0];
    dp_data.d.async.sensorEvent.vdata.data.u32[1] =
        (uint32_t)input->sRmag_data[1];
    dp_data.d.async.sensorEvent.vdata.data.u32[2] =
        (uint32_t)input->sRmag_data[2];
    send_dp_data(&dp_data);
  }

  if (self.acc_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_ACCEL_CAL)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_ACCELEROMETER;
    dp_data.d.async.sensorEvent.vdata.base.meta_data =
        (uint32_t)output->acc_accuracy_flag; // Accuracy flag
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, output->acc_cal_q16,
           sizeof(output->acc_cal_q16));
    send_dp_data(&dp_data);
  }

  if (self.gyr_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_GYRO_CAL)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_GYROSCOPE;
    dp_data.d.async.sensorEvent.vdata.base.meta_data =
        (uint32_t)output->gyr_accuracy_flag; // Accuracy flag
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, output->gyr_cal_q16,
           sizeof(output->gyr_cal_q16));
    send_dp_data(&dp_data);
  }

  if (self.temp_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_ACCEL_CAL)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_TEMPERATURE;
    dp_data.d.async.sensorEvent.vdata.base.meta_data =
        0; // Accuracy flag not available
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, &output->temp_degC_q16,
           sizeof(output->temp_degC_q16));
    send_dp_data(&dp_data);
  }

  if (self.ugyr_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_GYRO_CAL)) {
    int32_t ugyr_q16[6];
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_UNCAL_GYROSCOPE;
    dp_data.d.async.sensorEvent.vdata.base.meta_data =
        (uint32_t)output->gyr_accuracy_flag; // Accuracy flag
    ugyr_q16[0] = output->gyr_cal_q16[0] + output->gyr_bias_q16[0];
    ugyr_q16[1] = output->gyr_cal_q16[1] + output->gyr_bias_q16[1];
    ugyr_q16[2] = output->gyr_cal_q16[2] + output->gyr_bias_q16[2];
    ugyr_q16[3] = biases_multiplier * output->gyr_bias_q16[0];
    ugyr_q16[4] = biases_multiplier * output->gyr_bias_q16[1];
    ugyr_q16[5] = biases_multiplier * output->gyr_bias_q16[2];
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, ugyr_q16, sizeof(ugyr_q16));
    send_dp_data(&dp_data);
  }

  if (self.mag_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_MAG_CAL)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_MAGNETOMETER;
    dp_data.d.async.sensorEvent.vdata.base.meta_data =
        (uint32_t)output->mag_accuracy_flag; // Accuracy flag
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, output->mag_cal_q16,
           sizeof(output->mag_cal_q16));
    send_dp_data(&dp_data);
  }

  if (self.umag_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_MAG_CAL)) {
    int32_t umag_q16[6];
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_UNCAL_MAGNETOMETER;
    dp_data.d.async.sensorEvent.vdata.base.meta_data =
        (uint32_t)output->mag_accuracy_flag; // Accuracy flag
    umag_q16[0] = output->mag_cal_q16[0] + output->mag_bias_q16[0];
    umag_q16[1] = output->mag_cal_q16[1] + output->mag_bias_q16[1];
    umag_q16[2] = output->mag_cal_q16[2] + output->mag_bias_q16[2];
    umag_q16[3] = biases_multiplier * output->mag_bias_q16[0];
    umag_q16[4] = biases_multiplier * output->mag_bias_q16[1];
    umag_q16[5] = biases_multiplier * output->mag_bias_q16[2];
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, umag_q16, sizeof(umag_q16));
    send_dp_data(&dp_data);
  }

  if (self.grv_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_QUAT_AG)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_GAME_ROTATION_VECTOR;
    dp_data.d.async.sensorEvent.vdata.base.meta_data = 0;
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, output->grv_quat_q30,
           sizeof(output->grv_quat_q30));
    send_dp_data(&dp_data);
  }

  if (self.rv_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_QUAT_AGM)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_ROTATION_VECTOR;
    dp_data.d.async.sensorEvent.vdata.data.u32[4] =
        output->rv_accuracy_q27 >> 11; /* Q16 */
    dp_data.d.async.sensorEvent.vdata.base.meta_data = 0;
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, output->rv_quat_q30,
           sizeof(output->rv_quat_q30));
    send_dp_data(&dp_data);
  }

  if (self.linacc_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_LINEARACC)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_LINEAR_ACCELERATION;
    dp_data.d.async.sensorEvent.vdata.base.meta_data = 0;
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, output->linear_acc_q16,
           sizeof(output->linear_acc_q16));
    send_dp_data(&dp_data);
  }

  if (self.gra_en && (output->mask & INVN_ALGO_AGM_OUTPUT_MASK_GRAVITY)) {
    dp_data.sensor_id = DYN_PRO_SENSOR_TYPE_GRAVITY;
    dp_data.d.async.sensorEvent.vdata.base.meta_data = 0;
    memcpy(&dp_data.d.async.sensorEvent.vdata.data, output->gravity_q16,
           sizeof(output->gravity_q16));
    send_dp_data(&dp_data);
  }
}

int check_received_command() {
  int rc = 0;
  /*
   * Look for RX bytes and feed Dynamic protocol transport (will ultimately call
   * Dynamic protocol event handler)
   */
  while (inv_uart_mngr_available(SI_UART_ID_FTDI)) {
    int c = inv_uart_mngr_getc(SI_UART_ID_FTDI);
    DynProTransportUart_rxProcessByte(&transport, (uint8_t)c);
  }

  return rc;
}

static void transport_event_cb(enum DynProTransportEvent e,
                               union DynProTransportEventData data,
                               void *cookie) {
  (void)cookie;

  int rc;

  switch (e) {
  case DYN_PRO_TRANSPORT_EVENT_ERROR:
    INV_MSG(
        INV_MSG_LEVEL_ERROR,
        "ERROR event with value %d received from Dynamic Protocol transport",
        data.error);
    break;

  case DYN_PRO_TRANSPORT_EVENT_PKT_BYTE:
    /* Feed Dynamic protocol with bytes */
    rc = DynProtocol_processPktByte(&protocol, data.pkt_byte);
    if (rc < 0)
      INV_MSG(INV_MSG_LEVEL_DEBUG,
              "DynProtocol_processPktByte(%02x) returned %d", data.pkt_byte,
              rc);
    break;

  // case DYN_PRO_TRANSPORT_EVENT_PKT_SIZE:
  // case DYN_PRO_TRANSPORT_EVENT_PKT_END:
  // case DYN_PRO_TRANSPORT_EVENT_TX_START:
  // case DYN_PRO_TRANSPORT_EVENT_TX_BYTE:
  // case DYN_PRO_TRANSPORT_EVENT_TX_END:
  default:
    break;
  }
}

static void protocol_event_cb(enum DynProtocolEtype etype,
                              enum DynProtocolEid eid,
                              const DynProtocolEdata_t *edata, void *cookie) {
  (void)cookie;

  int rc;
  static DynProtocolEdata_t resp_edata; /* static to take on .bss */
  static uint8_t uart_buffer[128];
  DynProTransportUartFrame_t uart_frame;

  switch (etype) {
  case DYN_PROTOCOL_ETYPE_CMD:
    resp_edata.d.response.rc = handle_command(eid, edata, &resp_edata);

    /* get memory location for the dynamic protocol payload */
    if (DynProTransportUart_txAssignBuffer(&transport, &uart_frame, uart_buffer,
                                           sizeof(uart_buffer)) != 0)
      goto error_dma_buffer;

    if (DynProtocol_encodeResponse(
            &protocol, eid, &resp_edata, uart_frame.payload_data,
            uart_frame.max_payload_len, &uart_frame.payload_len) != 0)
      goto error_dma_buffer;

    if (DynProTransportUart_txEncodeFrame(&transport, &uart_frame) != 0)
      goto error_dma_buffer;

    /* respond to the command */
    if ((rc = inv_uart_mngr_puts(SI_UART_ID_FTDI,
                                 (const char *)uart_frame.header,
                                 (unsigned short)uart_frame.len)) != 0)
      INV_MSG(INV_MSG_LEVEL_DEBUG,
              "emdwrapper_protocol_event_cb: 'uart_mngr_puts()' returned %d",
              rc);

    break;

  error_dma_buffer:
    INV_MSG(INV_MSG_LEVEL_WARNING,
            "emdwrapper_protocol_event_cb: encode error, response dropped");
    break;

  default:
    INV_MSG(INV_MSG_LEVEL_WARNING,
            "FEUartDynProt: unexpected packet received. Ignored.");
    break; /* not suppose to happen */
  }
}

/*
 * Assign value (`val`) to a variable (`var`) if mag init was successful
 */
static int assign_if_mag_ok(uint8_t *var, uint8_t val) {
  if (command_cb(IS_MAG_INIT_SUCCESSFUL)) {
    *var = val;
    return INV_ERROR_SUCCESS;
  } else {
    return INV_ERROR_BAD_ARG;
  }
}

static int handle_command(enum DynProtocolEid eid,
                          const DynProtocolEdata_t *edata,
                          DynProtocolEdata_t *respdata) {
  const int sensor = edata->sensor_id;

  switch (eid) {
  case DYN_PROTOCOL_EID_GET_SW_REG:
    INV_MSG(INV_MSG_LEVEL_DEBUG, "FEDP: received command 'get_sw_reg'");
    if (edata->d.command.regAddr == DYN_PROTOCOL_EREG_HANDSHAKE_SUPPORT)
      return (inv_uart_get_flow_control_configuration(SI_UART_ID_FTDI) == 0)
                 ? 0
                 : 1;
    else
      return 0;

  case DYN_PROTOCOL_EID_RESET:
  case DYN_PROTOCOL_EID_CLEANUP:
    INV_MSG(INV_MSG_LEVEL_DEBUG, "FEDP: received command %s",
            (eid == DYN_PROTOCOL_EID_RESET ? "reset" : "cleanup"));
    INV_MSG(INV_MSG_LEVEL_INFO, "Received command: Resetting algorithm");
    self.acc_en = 0;
    self.mag_en = 0;
    self.gyr_en = 0;
    self.temp_en = 0;
    self.rv_en = 0;
    self.umag_en = 0;
    self.grv_en = 0;
    self.ugyr_en = 0;
    self.racc_en = 0;
    self.rgyr_en = 0;
    self.rmag_en = 0;
    self.rtemp_en = 0;
    self.linacc_en = 0;
    self.gra_en = 0;
    return command_cb(RESET_AGM);

  case DYN_PROTOCOL_EID_SETUP:
    INV_MSG(INV_MSG_LEVEL_DEBUG, "FEDP: received command setup");
    return 0;

  case DYN_PROTOCOL_EID_PING_SENSOR:
    INV_MSG(INV_MSG_LEVEL_DEBUG, "FEDP: received command ping for sensor %s",
            DynProtocol_sensorTypeToStr(sensor));
    switch (sensor) {
    case DYN_PRO_SENSOR_TYPE_ACCELEROMETER:
    case DYN_PRO_SENSOR_TYPE_GYROSCOPE:
    case DYN_PRO_SENSOR_TYPE_TEMPERATURE:
    case DYN_PRO_SENSOR_TYPE_GAME_ROTATION_VECTOR:
    case DYN_PRO_SENSOR_TYPE_UNCAL_GYROSCOPE:
    case DYN_PRO_SENSOR_TYPE_RAW_ACCELEROMETER:
    case DYN_PRO_SENSOR_TYPE_RAW_GYROSCOPE:
    case DYN_PRO_SENSOR_TYPE_RAW_TEMPERATURE:
    case DYN_PRO_SENSOR_TYPE_LINEAR_ACCELERATION:
    case DYN_PRO_SENSOR_TYPE_GRAVITY:
      return 0;
    case DYN_PRO_SENSOR_TYPE_MAGNETOMETER:
    case DYN_PRO_SENSOR_TYPE_ROTATION_VECTOR:
    case DYN_PRO_SENSOR_TYPE_UNCAL_MAGNETOMETER:
    case DYN_PRO_SENSOR_TYPE_RAW_MAGNETOMETER:
      return command_cb(IS_MAG_INIT_SUCCESSFUL) ? INV_ERROR_SUCCESS
                                                : INV_ERROR_BAD_ARG;
    default:
      return INV_ERROR_BAD_ARG;
    }

  case DYN_PROTOCOL_EID_START_SENSOR:
    INV_MSG(INV_MSG_LEVEL_DEBUG, "FEDP: received command start for sensor %s",
            DynProtocol_sensorTypeToStr(sensor));
    switch (sensor) {
    case DYN_PRO_SENSOR_TYPE_RAW_ACCELEROMETER:
      self.racc_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_RAW_GYROSCOPE:
      self.rgyr_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_RAW_TEMPERATURE:
      self.rtemp_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_ACCELEROMETER:
      self.acc_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_GYROSCOPE:
      self.gyr_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_UNCAL_GYROSCOPE:
      self.ugyr_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_TEMPERATURE:
      self.temp_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_GAME_ROTATION_VECTOR:
      self.grv_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_LINEAR_ACCELERATION:
      self.linacc_en = 1;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_GRAVITY:
      self.gra_en = 1;
      return INV_ERROR_SUCCESS;
    /* Following sensors depend on mag */
    case DYN_PRO_SENSOR_TYPE_RAW_MAGNETOMETER:
      return assign_if_mag_ok(&(self.rmag_en), 1);
    case DYN_PRO_SENSOR_TYPE_MAGNETOMETER:
      return assign_if_mag_ok(&(self.mag_en), 1);
    case DYN_PRO_SENSOR_TYPE_UNCAL_MAGNETOMETER:
      return assign_if_mag_ok(&(self.umag_en), 1);
    case DYN_PRO_SENSOR_TYPE_ROTATION_VECTOR:
      return assign_if_mag_ok(&(self.rv_en), 1);
    default:
      return INV_ERROR_BAD_ARG;
    }

  case DYN_PROTOCOL_EID_STOP_SENSOR:
    INV_MSG(INV_MSG_LEVEL_DEBUG, "FEDP: received command stop for sensor %s",
            DynProtocol_sensorTypeToStr(sensor));
    switch (sensor) {
    case DYN_PRO_SENSOR_TYPE_RAW_ACCELEROMETER:
      self.racc_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_RAW_GYROSCOPE:
      self.rgyr_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_RAW_TEMPERATURE:
      self.rtemp_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_ACCELEROMETER:
      self.acc_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_GYROSCOPE:
      self.gyr_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_UNCAL_GYROSCOPE:
      self.ugyr_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_TEMPERATURE:
      self.temp_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_GAME_ROTATION_VECTOR:
      self.grv_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_LINEAR_ACCELERATION:
      self.linacc_en = 0;
      return INV_ERROR_SUCCESS;
    case DYN_PRO_SENSOR_TYPE_GRAVITY:
      self.gra_en = 0;
      return INV_ERROR_SUCCESS;
    /* Following sensors depend on mag */
    case DYN_PRO_SENSOR_TYPE_RAW_MAGNETOMETER:
      return assign_if_mag_ok(&(self.rmag_en), 0);
    case DYN_PRO_SENSOR_TYPE_MAGNETOMETER:
      return assign_if_mag_ok(&(self.mag_en), 0);
    case DYN_PRO_SENSOR_TYPE_UNCAL_MAGNETOMETER:
      return assign_if_mag_ok(&(self.umag_en), 0);
    case DYN_PRO_SENSOR_TYPE_ROTATION_VECTOR:
      return assign_if_mag_ok(&(self.rv_en), 0);
    default:
      return INV_ERROR_BAD_ARG;
    }

  /* Need to return success to prevent error with sensor-cli*/
  case DYN_PROTOCOL_EID_SET_SENSOR_PERIOD:
    return 0;

  case DYN_PROTOCOL_EID_SET_SENSOR_CFG:
    INV_MSG(
        INV_MSG_LEVEL_DEBUG,
        "FEDP: received command set_config for sensor %s (type: %u, size: %u)",
        DynProtocol_sensorTypeToStr(sensor), edata->d.command.cfg.base.type,
        edata->d.command.cfg.base.size);
    switch (edata->d.command.cfg.base.type) {
    /*
     * Apply multiplier to gyro and mag biases to increase resolution.
     * From sensorcli: `setconfig gyr 32=mult` with `mult` being the multiplier.
     * Recommended value for `mult` is 256.
     */
    case DYN_PROTOCOL_CONFIG_TYPE_CUSTOM + 0: {
      /* Check command contains an integer only */
      if (edata->d.command.cfg.base.size != sizeof(int))
        return INV_ERROR_SIZE;

      /* Set value to `biases_multiplier` */
      memcpy(&biases_multiplier, edata->d.command.cfg.buffer, sizeof(int));
      INV_MSG(INV_MSG_LEVEL_INFO,
              "Setting multiplier factor for ugyr and umag to %u (max biases "
              "is %u dps/uT)",
              biases_multiplier,
              2048 /* max value that can be coded in dynprot */ /
                  biases_multiplier);
      return INV_ERROR_SUCCESS;
    }

    /*
     * Enable or disable calibration saving in flash.
     * From sensorcli:
     *   * `setconfig gyr 33=0` to disable calibration saving.
     *   * `setconfig gyr 33=1` to enable calibration saving.
     * It is required to disable calibration saving to prevent data gap.
     */
    case DYN_PROTOCOL_CONFIG_TYPE_CUSTOM + 1: {
      int arg;

      /* Check command contains an integer only */
      if (edata->d.command.cfg.base.size != sizeof(int))
        return INV_ERROR_SIZE;

      /* Get argument from command */
      memcpy(&arg, edata->d.command.cfg.buffer, sizeof(int));

      if (arg == 0)
        return command_cb(DISABLE_CALIBRATION_SAVING);
      else if (arg == 1)
        return command_cb(ENABLE_CALIBRATION_SAVING);
      else
        return INV_ERROR_BAD_ARG;
    }

    default:
      return INV_ERROR_BAD_ARG;
    }

  default:
    return INV_ERROR_NIMPL;
  }
}

static int send_dp_data(DynProtocolEdata_t *dp_data) {
  int rc;
  static uint8_t uart_buffer[128];
  DynProTransportUartFrame_t uart_frame;

  /* get memory location for the dynamic protocol payload */
  rc = DynProTransportUart_txAssignBuffer(&transport, &uart_frame, uart_buffer,
                                          sizeof(uart_buffer));
  if (rc != 0)
    goto error_dma_buf;

  rc = DynProtocol_encodeAsync(&protocol, DYN_PROTOCOL_EID_NEW_SENSOR_DATA,
                               dp_data, uart_frame.payload_data,
                               uart_frame.max_payload_len,
                               &uart_frame.payload_len);

  if (rc != 0)
    goto error_dma_buf;

  rc = DynProTransportUart_txEncodeFrame(&transport, &uart_frame);
  if (rc != 0)
    goto error_dma_buf;

  /* send async event */
  if ((rc = inv_uart_mngr_puts(SI_UART_ID_FTDI, (const char *)uart_frame.header,
                               (unsigned short)uart_frame.len)) != 0)
    INV_MSG(INV_MSG_LEVEL_DEBUG,
            "sensor_event_cb: 'uart_mngr_puts()' returned %d", rc);

  return rc;

error_dma_buf:
  INV_MSG(INV_MSG_LEVEL_WARNING, "notify_event: encode error, frame dropped");
  return rc;
}
