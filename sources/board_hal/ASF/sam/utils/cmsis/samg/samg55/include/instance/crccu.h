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

#ifndef _SAMG55_CRCCU_INSTANCE_
#define _SAMG55_CRCCU_INSTANCE_

/* ========== Register definition for CRCCU peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CRCCU_DSCR                                                         \
  (0x40048000U) /**< \brief (CRCCU) CRCCU Descriptor Base Register */
#define REG_CRCCU_DMA_EN                                                       \
  (0x40048008U) /**< \brief (CRCCU) CRCCU DMA Enable Register */
#define REG_CRCCU_DMA_DIS                                                      \
  (0x4004800CU) /**< \brief (CRCCU) CRCCU DMA Disable Register */
#define REG_CRCCU_DMA_SR                                                       \
  (0x40048010U) /**< \brief (CRCCU) CRCCU DMA Status Register */
#define REG_CRCCU_DMA_IER                                                      \
  (0x40048014U) /**< \brief (CRCCU) CRCCU DMA Interrupt Enable Register */
#define REG_CRCCU_DMA_IDR                                                      \
  (0x40048018U) /**< \brief (CRCCU) CRCCU DMA Interrupt Disable Register */
#define REG_CRCCU_DMA_IMR                                                      \
  (0x4004801CU) /**< \brief (CRCCU) CRCCU DMA Interrupt Mask Register */
#define REG_CRCCU_DMA_ISR                                                      \
  (0x40048020U) /**< \brief (CRCCU) CRCCU DMA Interrupt Status Register */
#define REG_CRCCU_CR (0x40048034U) /**< \brief (CRCCU) CRCCU Control Register  \
                                    */
#define REG_CRCCU_MR (0x40048038U) /**< \brief (CRCCU) CRCCU Mode Register */
#define REG_CRCCU_SR (0x4004803CU) /**< \brief (CRCCU) CRCCU Status Register   \
                                    */
#define REG_CRCCU_IER                                                          \
  (0x40048040U) /**< \brief (CRCCU) CRCCU Interrupt Enable Register */
#define REG_CRCCU_IDR                                                          \
  (0x40048044U) /**< \brief (CRCCU) CRCCU Interrupt Disable Register */
#define REG_CRCCU_IMR                                                          \
  (0x40048048U) /**< \brief (CRCCU) CRCCU Interrupt Mask Register */
#define REG_CRCCU_ISR                                                          \
  (0x4004804CU) /**< \brief (CRCCU) CRCCU Interrupt Status Register */
#else
#define REG_CRCCU_DSCR                                                         \
  (*(__IO uint32_t                                                             \
         *)0x40048000U) /**< \brief (CRCCU) CRCCU Descriptor Base Register */
#define REG_CRCCU_DMA_EN                                                       \
  (*(__O uint32_t                                                              \
         *)0x40048008U) /**< \brief (CRCCU) CRCCU DMA Enable Register */
#define REG_CRCCU_DMA_DIS                                                      \
  (*(__O uint32_t                                                              \
         *)0x4004800CU) /**< \brief (CRCCU) CRCCU DMA Disable Register */
#define REG_CRCCU_DMA_SR                                                       \
  (*(__I uint32_t                                                              \
         *)0x40048010U) /**< \brief (CRCCU) CRCCU DMA Status Register */
#define REG_CRCCU_DMA_IER                                                      \
  (*(__O uint32_t *)0x40048014U) /**< \brief (CRCCU) CRCCU DMA Interrupt       \
                                    Enable Register */
#define REG_CRCCU_DMA_IDR                                                      \
  (*(__O uint32_t *)0x40048018U) /**< \brief (CRCCU) CRCCU DMA Interrupt       \
                                    Disable Register */
#define REG_CRCCU_DMA_IMR                                                      \
  (*(__I uint32_t *)0x4004801CU) /**< \brief (CRCCU) CRCCU DMA Interrupt Mask  \
                                    Register */
#define REG_CRCCU_DMA_ISR                                                      \
  (*(__I uint32_t *)0x40048020U) /**< \brief (CRCCU) CRCCU DMA Interrupt       \
                                    Status Register */
#define REG_CRCCU_CR                                                           \
  (*(__O uint32_t *)0x40048034U) /**< \brief (CRCCU) CRCCU Control Register */
#define REG_CRCCU_MR                                                           \
  (*(__IO uint32_t *)0x40048038U) /**< \brief (CRCCU) CRCCU Mode Register */
#define REG_CRCCU_SR                                                           \
  (*(__I uint32_t *)0x4004803CU) /**< \brief (CRCCU) CRCCU Status Register */
#define REG_CRCCU_IER                                                          \
  (*(__O uint32_t                                                              \
         *)0x40048040U) /**< \brief (CRCCU) CRCCU Interrupt Enable Register */
#define REG_CRCCU_IDR                                                          \
  (*(__O uint32_t *)0x40048044U) /**< \brief (CRCCU) CRCCU Interrupt Disable   \
                                    Register */
#define REG_CRCCU_IMR                                                          \
  (*(__I uint32_t                                                              \
         *)0x40048048U) /**< \brief (CRCCU) CRCCU Interrupt Mask Register */
#define REG_CRCCU_ISR                                                          \
  (*(__I uint32_t                                                              \
         *)0x4004804CU) /**< \brief (CRCCU) CRCCU Interrupt Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMG55_CRCCU_INSTANCE_ */
