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

/** @defgroup Uart Uart
        @ingroup  Low_Level_Driver
        @{
*/
#ifndef __INV_UART_MNGR_H__
#define __INV_UART_MNGR_H__

#include "uart.h"

/** @brief UART manager initialization structure.
 *
 * Such a structure should be filled-in and passed to the uart_mngr_init
 * function in order to initialize the uart peripheral. All fields need to be
 * initialized in order to avoid unpredictable behavior.
 */
typedef struct {
  inv_uart_num_t uart_num; /** < UART peripheral that we wish to initialize */
  int baudrate;            /** < UART baudrate speed */
  inv_uart_flow_control_t
      flow_ctrl; /** < Flow control as defined by uart_flow_control_t enum
                   Note: LOG_UART only support INV_UART_FLOW_CONTROL_NONE */
} inv_uart_mngr_init_struct_t;

/** @brief      Initialize the UART peripheral according to
 *              the parameters specified in the inv_uart_mngr_init_struct_t
 *  @param[in]  uart_mngr_init_struct Pointer to the inv_uart_mngr_init_struct_t
 * that contains the configuration information
 *  @return     0 on success
 *              UART_ERROR_BAD_ARG if the inv_uart_mngr_init_struct_t was
 * incorrectly filled-in
 */
int inv_uart_mngr_init(inv_uart_mngr_init_struct_t *uart_mngr_init_struct);

/** @brief      Transmits an array of characters on the UART.
 *              As the length is sent as parameter, the array can contain zeros
 * and does no have to be NULL-terminated
 *  @param[in]  uart UART peripheral
 *  @param[in]  s Pointer to the array to be transmitted
 *  @param[in]  l Length of the array to be transmitted
 *  @return     0 on success
 *              UART_ERROR_MEMORY if the internal buffers are full
 *              UART_ERROR_BUSY if another transaction is already ongoing
 *              UART_ERROR if for an unknown reason the requested transaction
 * did not start UART_ERROR_BAD_ARG if one of the arguments is unsupported
 *  @note       The data that is to be transfered will be copied to the internal
 * buffers.
 */
int inv_uart_mngr_puts(inv_uart_num_t uart, const char *s, unsigned short l);

/** @brief      Reads a character received by the UART peripheral
 *  @param[in]  uart     UART peripheral
 *  @return     First available character in the RX buffer
 *              EOF if no character available in the RX buffer
 */
int inv_uart_mngr_getc(inv_uart_num_t uart);

/** @brief      Returns the number of available bytes in the RX buffer
 *  @param[in]  uart UART peripheral
 *  @return     Number of available bytes in the RX buffer
 */
int inv_uart_mngr_available(inv_uart_num_t uart);

#endif // __INV_UART_MNGR_H__

/** @} */
