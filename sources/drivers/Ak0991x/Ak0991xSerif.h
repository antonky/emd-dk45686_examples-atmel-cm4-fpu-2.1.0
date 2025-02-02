/*
 *
 * Copyright (c) [2015] by InvenSense, Inc.
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

/** @defgroup DriverAk0991xSerif Ak0991x driver serif
 *  @brief Interface for low-level serial (I2C/SPI) access
 *  @ingroup  DriverAk0991x
 *  @{
 */

#ifndef _INV_AK0991X_SERIF_H_
#define _INV_AK0991X_SERIF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Invn/InvError.h"

#include <stdint.h>

/** @brief Ak0991x serial interface
 */
struct inv_ak0991x_serif {
  void *context;
  int (*read_reg)(void *serif, uint8_t reg, uint8_t *buf, uint32_t len);
  int (*write_reg)(void *serif, uint8_t reg, const uint8_t *buf, uint32_t len);
  uint32_t max_read;
  uint32_t max_write;
  uint8_t is_spi;
};

static inline uint8_t inv_ak0991x_serif_is_spi(struct inv_ak0991x_serif *s) {
  if (!s)
    return INV_ERROR;

  return s->is_spi;
}

static inline uint32_t inv_ak0991x_serif_max_read(struct inv_ak0991x_serif *s) {
  if (!s)
    return INV_ERROR;

  return s->max_read;
}

static inline uint32_t
inv_ak0991x_serif_max_write(struct inv_ak0991x_serif *s) {
  if (!s)
    return INV_ERROR;

  return s->max_write;
}

static inline int inv_ak0991x_serif_read_reg(struct inv_ak0991x_serif *s,
                                             uint8_t reg, uint8_t *buf,
                                             uint32_t len) {
  if (!s)
    return INV_ERROR;

  if (len > s->max_read)
    return INV_ERROR_SIZE;

  if (s->read_reg(s->context, reg, buf, len) != 0)
    return INV_ERROR_TRANSPORT;

  return 0;
}

static inline int inv_ak0991x_serif_write_reg(struct inv_ak0991x_serif *s,
                                              uint8_t reg, const uint8_t *buf,
                                              uint32_t len) {
  if (!s)
    return INV_ERROR;

  if (len > s->max_write)
    return INV_ERROR_SIZE;

  if (s->write_reg(s->context, reg, buf, len) != 0)
    return INV_ERROR_TRANSPORT;

  return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* _INV_AK0991X_SERIF_H_ */

/** @} */
