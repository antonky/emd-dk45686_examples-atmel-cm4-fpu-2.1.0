/**
 * \file
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel
 * Support</a>
 */

#ifndef _SAMG55_RTC_INSTANCE_
#define _SAMG55_RTC_INSTANCE_

/* ========== Register definition for RTC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_RTC_CR (0x400E1460U)     /**< \brief (RTC) Control Register */
#define REG_RTC_MR (0x400E1464U)     /**< \brief (RTC) Mode Register */
#define REG_RTC_TIMR (0x400E1468U)   /**< \brief (RTC) Time Register */
#define REG_RTC_CALR (0x400E146CU)   /**< \brief (RTC) Calendar Register */
#define REG_RTC_TIMALR (0x400E1470U) /**< \brief (RTC) Time Alarm Register */
#define REG_RTC_CALALR                                                         \
  (0x400E1474U)                  /**< \brief (RTC) Calendar Alarm Register */
#define REG_RTC_SR (0x400E1478U) /**< \brief (RTC) Status Register */
#define REG_RTC_SCCR                                                           \
  (0x400E147CU) /**< \brief (RTC) Status Clear Command Register */
#define REG_RTC_IER (0x400E1480U) /**< \brief (RTC) Interrupt Enable Register  \
                                   */
#define REG_RTC_IDR                                                            \
  (0x400E1484U) /**< \brief (RTC) Interrupt Disable Register */
#define REG_RTC_IMR (0x400E1488U) /**< \brief (RTC) Interrupt Mask Register */
#define REG_RTC_VER (0x400E148CU) /**< \brief (RTC) Valid Entry Register */
#define REG_RTC_MSR (0x400E1530U) /**< \brief (RTC) Milliseconds Register */
#define REG_RTC_WPMR                                                           \
  (0x400E1544U) /**< \brief (RTC) Write Protection Mode Register */
#else
#define REG_RTC_CR                                                             \
  (*(__IO uint32_t *)0x400E1460U) /**< \brief (RTC) Control Register */
#define REG_RTC_MR                                                             \
  (*(__IO uint32_t *)0x400E1464U) /**< \brief (RTC) Mode Register */
#define REG_RTC_TIMR                                                           \
  (*(__IO uint32_t *)0x400E1468U) /**< \brief (RTC) Time Register */
#define REG_RTC_CALR                                                           \
  (*(__IO uint32_t *)0x400E146CU) /**< \brief (RTC) Calendar Register */
#define REG_RTC_TIMALR                                                         \
  (*(__IO uint32_t *)0x400E1470U) /**< \brief (RTC) Time Alarm Register */
#define REG_RTC_CALALR                                                         \
  (*(__IO uint32_t *)0x400E1474U) /**< \brief (RTC) Calendar Alarm Register */
#define REG_RTC_SR                                                             \
  (*(__I uint32_t *)0x400E1478U) /**< \brief (RTC) Status Register */
#define REG_RTC_SCCR                                                           \
  (*(__O uint32_t                                                              \
         *)0x400E147CU) /**< \brief (RTC) Status Clear Command Register */
#define REG_RTC_IER                                                            \
  (*(__O uint32_t *)0x400E1480U) /**< \brief (RTC) Interrupt Enable Register   \
                                  */
#define REG_RTC_IDR                                                            \
  (*(__O uint32_t *)0x400E1484U) /**< \brief (RTC) Interrupt Disable Register  \
                                  */
#define REG_RTC_IMR                                                            \
  (*(__I uint32_t *)0x400E1488U) /**< \brief (RTC) Interrupt Mask Register */
#define REG_RTC_VER                                                            \
  (*(__I uint32_t *)0x400E148CU) /**< \brief (RTC) Valid Entry Register */
#define REG_RTC_MSR                                                            \
  (*(__I uint32_t *)0x400E1530U) /**< \brief (RTC) Milliseconds Register */
#define REG_RTC_WPMR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x400E1544U) /**< \brief (RTC) Write Protection Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMG55_RTC_INSTANCE_ */
