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

#ifndef _SAMG55_UDP_INSTANCE_
#define _SAMG55_UDP_INSTANCE_

/* ========== Register definition for UDP peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_UDP_FRM_NUM (0x40044000U) /**< \brief (UDP) Frame Number Register  \
                                       */
#define REG_UDP_GLB_STAT                                                       \
  (0x40044004U) /**< \brief (UDP) Global State Register */
#define REG_UDP_FADDR                                                          \
  (0x40044008U)                   /**< \brief (UDP) Function Address Register */
#define REG_UDP_IER (0x40044010U) /**< \brief (UDP) Interrupt Enable Register  \
                                   */
#define REG_UDP_IDR                                                            \
  (0x40044014U) /**< \brief (UDP) Interrupt Disable Register */
#define REG_UDP_IMR (0x40044018U) /**< \brief (UDP) Interrupt Mask Register */
#define REG_UDP_ISR (0x4004401CU) /**< \brief (UDP) Interrupt Status Register  \
                                   */
#define REG_UDP_ICR (0x40044020U) /**< \brief (UDP) Interrupt Clear Register   \
                                   */
#define REG_UDP_RST_EP                                                         \
  (0x40044028U) /**< \brief (UDP) Reset Endpoint Register */
#define REG_UDP_CSR                                                            \
  (0x40044030U) /**< \brief (UDP) Endpoint Control and Status Register */
#define REG_UDP_FDR                                                            \
  (0x40044050U) /**< \brief (UDP) Endpoint FIFO Data Register */
#define REG_UDP_TXVC                                                           \
  (0x40044074U) /**< \brief (UDP) Transceiver Control Register */
#else
#define REG_UDP_FRM_NUM                                                        \
  (*(__I uint32_t *)0x40044000U) /**< \brief (UDP) Frame Number Register */
#define REG_UDP_GLB_STAT                                                       \
  (*(__IO uint32_t *)0x40044004U) /**< \brief (UDP) Global State Register */
#define REG_UDP_FADDR                                                          \
  (*(__IO uint32_t *)0x40044008U) /**< \brief (UDP) Function Address Register  \
                                   */
#define REG_UDP_IER                                                            \
  (*(__O uint32_t *)0x40044010U) /**< \brief (UDP) Interrupt Enable Register   \
                                  */
#define REG_UDP_IDR                                                            \
  (*(__O uint32_t *)0x40044014U) /**< \brief (UDP) Interrupt Disable Register  \
                                  */
#define REG_UDP_IMR                                                            \
  (*(__I uint32_t *)0x40044018U) /**< \brief (UDP) Interrupt Mask Register */
#define REG_UDP_ISR                                                            \
  (*(__I uint32_t *)0x4004401CU) /**< \brief (UDP) Interrupt Status Register   \
                                  */
#define REG_UDP_ICR                                                            \
  (*(__O uint32_t *)0x40044020U) /**< \brief (UDP) Interrupt Clear Register */
#define REG_UDP_RST_EP                                                         \
  (*(__IO uint32_t *)0x40044028U) /**< \brief (UDP) Reset Endpoint Register */
#define REG_UDP_CSR                                                            \
  (*(__IO uint32_t *)0x40044030U) /**< \brief (UDP) Endpoint Control and       \
                                     Status Register */
#define REG_UDP_FDR                                                            \
  (*(__IO uint32_t                                                             \
         *)0x40044050U) /**< \brief (UDP) Endpoint FIFO Data Register */
#define REG_UDP_TXVC                                                           \
  (*(__IO uint32_t                                                             \
         *)0x40044074U) /**< \brief (UDP) Transceiver Control Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMG55_UDP_INSTANCE_ */
