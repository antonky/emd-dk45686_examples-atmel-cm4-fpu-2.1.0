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

#ifndef _SAMG55_ADC_INSTANCE_
#define _SAMG55_ADC_INSTANCE_

/* ========== Register definition for ADC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ADC_CR (0x40038000U) /**< \brief (ADC) Control Register */
#define REG_ADC_MR (0x40038004U) /**< \brief (ADC) Mode Register */
#define REG_ADC_SEQR1                                                          \
  (0x40038008U) /**< \brief (ADC) Channel Sequence Register 1 */
#define REG_ADC_CHER (0x40038010U) /**< \brief (ADC) Channel Enable Register   \
                                    */
#define REG_ADC_CHDR (0x40038014U) /**< \brief (ADC) Channel Disable Register  \
                                    */
#define REG_ADC_CHSR (0x40038018U) /**< \brief (ADC) Channel Status Register   \
                                    */
#define REG_ADC_LCDR                                                           \
  (0x40038020U) /**< \brief (ADC) Last Converted Data Register */
#define REG_ADC_IER (0x40038024U) /**< \brief (ADC) Interrupt Enable Register  \
                                   */
#define REG_ADC_IDR                                                            \
  (0x40038028U) /**< \brief (ADC) Interrupt Disable Register */
#define REG_ADC_IMR (0x4003802CU) /**< \brief (ADC) Interrupt Mask Register */
#define REG_ADC_ISR (0x40038030U) /**< \brief (ADC) Interrupt Status Register  \
                                   */
#define REG_ADC_LCTMR                                                          \
  (0x40038034U) /**< \brief (ADC) Last Channel Trigger Mode Register */
#define REG_ADC_LCCWR                                                          \
  (0x40038038U) /**< \brief (ADC) Last Channel Compare Window Register */
#define REG_ADC_OVER (0x4003803CU) /**< \brief (ADC) Overrun Status Register   \
                                    */
#define REG_ADC_EMR (0x40038040U)  /**< \brief (ADC) Extended Mode Register */
#define REG_ADC_CWR (0x40038044U)  /**< \brief (ADC) Compare Window Register */
#define REG_ADC_COR (0x4003804CU)  /**< \brief (ADC) Channel Offset Register */
#define REG_ADC_CDR (0x40038050U)  /**< \brief (ADC) Channel Data Register */
#define REG_ADC_WPMR                                                           \
  (0x400380E4U) /**< \brief (ADC) Write Protection Mode Register */
#define REG_ADC_WPSR                                                           \
  (0x400380E8U) /**< \brief (ADC) Write Protection Status Register */
#define REG_ADC_RPR (0x40038100U) /**< \brief (ADC) Receive Pointer Register   \
                                   */
#define REG_ADC_RCR (0x40038104U) /**< \brief (ADC) Receive Counter Register   \
                                   */
#define REG_ADC_RNPR                                                           \
  (0x40038110U) /**< \brief (ADC) Receive Next Pointer Register */
#define REG_ADC_RNCR                                                           \
  (0x40038114U) /**< \brief (ADC) Receive Next Counter Register */
#define REG_ADC_PTCR                                                           \
  (0x40038120U) /**< \brief (ADC) Transfer Control Register */
#define REG_ADC_PTSR (0x40038124U) /**< \brief (ADC) Transfer Status Register  \
                                    */
#else
#define REG_ADC_CR                                                             \
  (*(__O uint32_t *)0x40038000U) /**< \brief (ADC) Control Register */
#define REG_ADC_MR                                                             \
  (*(__IO uint32_t *)0x40038004U) /**< \brief (ADC) Mode Register */
#define REG_ADC_SEQR1                                                          \
  (*(__IO uint32_t                                                             \
         *)0x40038008U) /**< \brief (ADC) Channel Sequence Register 1 */
#define REG_ADC_CHER                                                           \
  (*(__O uint32_t *)0x40038010U) /**< \brief (ADC) Channel Enable Register */
#define REG_ADC_CHDR                                                           \
  (*(__O uint32_t *)0x40038014U) /**< \brief (ADC) Channel Disable Register */
#define REG_ADC_CHSR                                                           \
  (*(__I uint32_t *)0x40038018U) /**< \brief (ADC) Channel Status Register */
#define REG_ADC_LCDR                                                           \
  (*(__I uint32_t                                                              \
         *)0x40038020U) /**< \brief (ADC) Last Converted Data Register */
#define REG_ADC_IER                                                            \
  (*(__O uint32_t *)0x40038024U) /**< \brief (ADC) Interrupt Enable Register   \
                                  */
#define REG_ADC_IDR                                                            \
  (*(__O uint32_t *)0x40038028U) /**< \brief (ADC) Interrupt Disable Register  \
                                  */
#define REG_ADC_IMR                                                            \
  (*(__I uint32_t *)0x4003802CU) /**< \brief (ADC) Interrupt Mask Register */
#define REG_ADC_ISR                                                            \
  (*(__I uint32_t *)0x40038030U) /**< \brief (ADC) Interrupt Status Register   \
                                  */
#define REG_ADC_LCTMR                                                          \
  (*(__IO uint32_t *)0x40038034U) /**< \brief (ADC) Last Channel Trigger Mode  \
                                     Register */
#define REG_ADC_LCCWR                                                          \
  (*(__IO uint32_t *)0x40038038U) /**< \brief (ADC) Last Channel Compare       \
                                     Window Register */
#define REG_ADC_OVER                                                           \
  (*(__I uint32_t *)0x4003803CU) /**< \brief (ADC) Overrun Status Register */
#define REG_ADC_EMR                                                            \
  (*(__IO uint32_t *)0x40038040U) /**< \brief (ADC) Extended Mode Register */
#define REG_ADC_CWR                                                            \
  (*(__IO uint32_t *)0x40038044U) /**< \brief (ADC) Compare Window Register */
#define REG_ADC_COR                                                            \
  (*(__IO uint32_t *)0x4003804CU) /**< \brief (ADC) Channel Offset Register */
#define REG_ADC_CDR                                                            \
  (*(__I uint32_t *)0x40038050U) /**< \brief (ADC) Channel Data Register */
#define REG_ADC_WPMR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x400380E4U) /**< \brief (ADC) Write Protection Mode Register */
#define REG_ADC_WPSR                                                           \
  (*(__I uint32_t                                                              \
         *)0x400380E8U) /**< \brief (ADC) Write Protection Status Register */
#define REG_ADC_RPR                                                            \
  (*(__IO uint32_t *)0x40038100U) /**< \brief (ADC) Receive Pointer Register   \
                                   */
#define REG_ADC_RCR                                                            \
  (*(__IO uint32_t *)0x40038104U) /**< \brief (ADC) Receive Counter Register   \
                                   */
#define REG_ADC_RNPR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x40038110U) /**< \brief (ADC) Receive Next Pointer Register */
#define REG_ADC_RNCR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x40038114U) /**< \brief (ADC) Receive Next Counter Register */
#define REG_ADC_PTCR                                                           \
  (*(__O uint32_t *)0x40038120U) /**< \brief (ADC) Transfer Control Register   \
                                  */
#define REG_ADC_PTSR                                                           \
  (*(__I uint32_t *)0x40038124U) /**< \brief (ADC) Transfer Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMG55_ADC_INSTANCE_ */
