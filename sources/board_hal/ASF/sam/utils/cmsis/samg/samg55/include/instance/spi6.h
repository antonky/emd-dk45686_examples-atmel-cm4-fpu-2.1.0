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

#ifndef _SAMG55_SPI6_INSTANCE_
#define _SAMG55_SPI6_INSTANCE_

/* ========== Register definition for SPI6 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SPI6_CR (0x40040400U) /**< \brief (SPI6) SPI Control Register */
#define REG_SPI6_MR (0x40040404U) /**< \brief (SPI6) SPI Mode Register */
#define REG_SPI6_RDR                                                           \
  (0x40040408U) /**< \brief (SPI6) SPI Receive Data Register */
#define REG_SPI6_TDR                                                           \
  (0x4004040CU) /**< \brief (SPI6) SPI Transmit Data Register */
#define REG_SPI6_SR (0x40040410U) /**< \brief (SPI6) SPI Status Register */
#define REG_SPI6_IER                                                           \
  (0x40040414U) /**< \brief (SPI6) SPI Interrupt Enable Register */
#define REG_SPI6_IDR                                                           \
  (0x40040418U) /**< \brief (SPI6) SPI Interrupt Disable Register */
#define REG_SPI6_IMR                                                           \
  (0x4004041CU) /**< \brief (SPI6) SPI Interrupt Mask Register */
#define REG_SPI6_CSR                                                           \
  (0x40040430U) /**< \brief (SPI6) SPI Chip Select Register */
#define REG_SPI6_CMPR                                                          \
  (0x40040448U) /**< \brief (SPI6) SPI Comparison Register */
#define REG_SPI6_WPMR                                                          \
  (0x400404E4U) /**< \brief (SPI6) SPI Write Protection Mode Register */
#define REG_SPI6_WPSR                                                          \
  (0x400404E8U) /**< \brief (SPI6) SPI Write Protection Status Register */
#define REG_SPI6_RPR                                                           \
  (0x40040500U) /**< \brief (SPI6) Receive Pointer Register */
#define REG_SPI6_RCR                                                           \
  (0x40040504U) /**< \brief (SPI6) Receive Counter Register */
#define REG_SPI6_TPR                                                           \
  (0x40040508U) /**< \brief (SPI6) Transmit Pointer Register */
#define REG_SPI6_TCR                                                           \
  (0x4004050CU) /**< \brief (SPI6) Transmit Counter Register */
#define REG_SPI6_RNPR                                                          \
  (0x40040510U) /**< \brief (SPI6) Receive Next Pointer Register */
#define REG_SPI6_RNCR                                                          \
  (0x40040514U) /**< \brief (SPI6) Receive Next Counter Register */
#define REG_SPI6_TNPR                                                          \
  (0x40040518U) /**< \brief (SPI6) Transmit Next Pointer Register */
#define REG_SPI6_TNCR                                                          \
  (0x4004051CU) /**< \brief (SPI6) Transmit Next Counter Register */
#define REG_SPI6_PTCR                                                          \
  (0x40040520U) /**< \brief (SPI6) Transfer Control Register */
#define REG_SPI6_PTSR                                                          \
  (0x40040524U) /**< \brief (SPI6) Transfer Status Register */
#else
#define REG_SPI6_CR                                                            \
  (*(__O uint32_t *)0x40040400U) /**< \brief (SPI6) SPI Control Register */
#define REG_SPI6_MR                                                            \
  (*(__IO uint32_t *)0x40040404U) /**< \brief (SPI6) SPI Mode Register */
#define REG_SPI6_RDR                                                           \
  (*(__I uint32_t *)0x40040408U) /**< \brief (SPI6) SPI Receive Data Register  \
                                  */
#define REG_SPI6_TDR                                                           \
  (*(__O uint32_t                                                              \
         *)0x4004040CU) /**< \brief (SPI6) SPI Transmit Data Register */
#define REG_SPI6_SR                                                            \
  (*(__I uint32_t *)0x40040410U) /**< \brief (SPI6) SPI Status Register */
#define REG_SPI6_IER                                                           \
  (*(__O uint32_t                                                              \
         *)0x40040414U) /**< \brief (SPI6) SPI Interrupt Enable Register */
#define REG_SPI6_IDR                                                           \
  (*(__O uint32_t                                                              \
         *)0x40040418U) /**< \brief (SPI6) SPI Interrupt Disable Register */
#define REG_SPI6_IMR                                                           \
  (*(__I uint32_t                                                              \
         *)0x4004041CU) /**< \brief (SPI6) SPI Interrupt Mask Register */
#define REG_SPI6_CSR                                                           \
  (*(__IO uint32_t *)0x40040430U) /**< \brief (SPI6) SPI Chip Select Register  \
                                   */
#define REG_SPI6_CMPR                                                          \
  (*(__IO uint32_t *)0x40040448U) /**< \brief (SPI6) SPI Comparison Register   \
                                   */
#define REG_SPI6_WPMR                                                          \
  (*(__IO uint32_t *)0x400404E4U) /**< \brief (SPI6) SPI Write Protection Mode \
                                     Register */
#define REG_SPI6_WPSR                                                          \
  (*(__I uint32_t *)0x400404E8U) /**< \brief (SPI6) SPI Write Protection       \
                                    Status Register */
#define REG_SPI6_RPR                                                           \
  (*(__IO uint32_t *)0x40040500U) /**< \brief (SPI6) Receive Pointer Register  \
                                   */
#define REG_SPI6_RCR                                                           \
  (*(__IO uint32_t *)0x40040504U) /**< \brief (SPI6) Receive Counter Register  \
                                   */
#define REG_SPI6_TPR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x40040508U) /**< \brief (SPI6) Transmit Pointer Register */
#define REG_SPI6_TCR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x4004050CU) /**< \brief (SPI6) Transmit Counter Register */
#define REG_SPI6_RNPR                                                          \
  (*(__IO uint32_t                                                             \
         *)0x40040510U) /**< \brief (SPI6) Receive Next Pointer Register */
#define REG_SPI6_RNCR                                                          \
  (*(__IO uint32_t                                                             \
         *)0x40040514U) /**< \brief (SPI6) Receive Next Counter Register */
#define REG_SPI6_TNPR                                                          \
  (*(__IO uint32_t                                                             \
         *)0x40040518U) /**< \brief (SPI6) Transmit Next Pointer Register */
#define REG_SPI6_TNCR                                                          \
  (*(__IO uint32_t                                                             \
         *)0x4004051CU) /**< \brief (SPI6) Transmit Next Counter Register */
#define REG_SPI6_PTCR                                                          \
  (*(__O uint32_t *)0x40040520U) /**< \brief (SPI6) Transfer Control Register  \
                                  */
#define REG_SPI6_PTSR                                                          \
  (*(__I uint32_t *)0x40040524U) /**< \brief (SPI6) Transfer Status Register   \
                                  */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMG55_SPI6_INSTANCE_ */
