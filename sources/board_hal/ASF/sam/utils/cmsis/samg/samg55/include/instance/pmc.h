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

#ifndef _SAMG55_PMC_INSTANCE_
#define _SAMG55_PMC_INSTANCE_

/* ========== Register definition for PMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PMC_SCER                                                           \
  (0x400E0400U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR                                                           \
  (0x400E0404U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR                                                           \
  (0x400E0408U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_PCER0                                                          \
  (0x400E0410U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
#define REG_PMC_PCDR0                                                          \
  (0x400E0414U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
#define REG_PMC_PCSR0                                                          \
  (0x400E0418U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
#define REG_CKGR_MOR (0x400E0420U) /**< \brief (PMC) Main Oscillator Register  \
                                    */
#define REG_CKGR_MCFR                                                          \
  (0x400E0424U) /**< \brief (PMC) Main Clock Frequency Register */
#define REG_CKGR_PLLAR (0x400E0428U) /**< \brief (PMC) PLLA Register */
#define REG_CKGR_PLLBR (0x400E042CU) /**< \brief (PMC) PLLB Register */
#define REG_PMC_MCKR (0x400E0430U)   /**< \brief (PMC) Master Clock Register */
#define REG_PMC_USB (0x400E0438U)    /**< \brief (PMC) USB Clock Register */
#define REG_PMC_PCK                                                            \
  (0x400E0440U) /**< \brief (PMC) Programmable Clock 0 Register */
#define REG_PMC_IER (0x400E0460U) /**< \brief (PMC) Interrupt Enable Register  \
                                   */
#define REG_PMC_IDR                                                            \
  (0x400E0464U)                  /**< \brief (PMC) Interrupt Disable Register */
#define REG_PMC_SR (0x400E0468U) /**< \brief (PMC) Status Register */
#define REG_PMC_IMR (0x400E046CU) /**< \brief (PMC) Interrupt Mask Register */
#define REG_PMC_FSMR                                                           \
  (0x400E0470U) /**< \brief (PMC) Fast Startup Mode Register */
#define REG_PMC_FSPR                                                           \
  (0x400E0474U) /**< \brief (PMC) Fast Startup Polarity Register */
#define REG_PMC_FOCR                                                           \
  (0x400E0478U) /**< \brief (PMC) Fault Output Clear Register */
#define REG_PMC_WPMR                                                           \
  (0x400E04E4U) /**< \brief (PMC) Write Protection Mode Register */
#define REG_PMC_WPSR                                                           \
  (0x400E04E8U) /**< \brief (PMC) Write Protection Status Register */
#define REG_PMC_PCR                                                            \
  (0x400E050CU) /**< \brief (PMC) Peripheral Control Register */
#define REG_PMC_OCR                                                            \
  (0x400E0510U) /**< \brief (PMC) Oscillator Calibration Register */
#define REG_PMC_SLPWK_ER0                                                      \
  (0x400E0514U) /**< \brief (PMC) SleepWalking Enable Register 0 */
#define REG_PMC_SLPWK_DR0                                                      \
  (0x400E0518U) /**< \brief (PMC) SleepWalking Disable Register 0 */
#define REG_PMC_SLPWK_SR0                                                      \
  (0x400E051CU) /**< \brief (PMC) SleepWalking Status Register 0 */
#define REG_PMC_SLPWK_ASR0                                                     \
  (0x400E0520U) /**< \brief (PMC) SleepWalking Activity Status Register 0 */
#define REG_PMC_PMMR                                                           \
  (0x400E0530U) /**< \brief (PMC) PLL Maximum Multiplier Value Register */
#else
#define REG_PMC_SCER                                                           \
  (*(__O uint32_t                                                              \
         *)0x400E0400U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR                                                           \
  (*(__O uint32_t                                                              \
         *)0x400E0404U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR                                                           \
  (*(__I uint32_t                                                              \
         *)0x400E0408U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_PCER0                                                          \
  (*(__O uint32_t *)0x400E0410U) /**< \brief (PMC) Peripheral Clock Enable     \
                                    Register 0 */
#define REG_PMC_PCDR0                                                          \
  (*(__O uint32_t *)0x400E0414U) /**< \brief (PMC) Peripheral Clock Disable    \
                                    Register 0 */
#define REG_PMC_PCSR0                                                          \
  (*(__I uint32_t *)0x400E0418U) /**< \brief (PMC) Peripheral Clock Status     \
                                    Register 0 */
#define REG_CKGR_MOR                                                           \
  (*(__IO uint32_t *)0x400E0420U) /**< \brief (PMC) Main Oscillator Register   \
                                   */
#define REG_CKGR_MCFR                                                          \
  (*(__IO uint32_t                                                             \
         *)0x400E0424U) /**< \brief (PMC) Main Clock Frequency Register */
#define REG_CKGR_PLLAR                                                         \
  (*(__IO uint32_t *)0x400E0428U) /**< \brief (PMC) PLLA Register */
#define REG_CKGR_PLLBR                                                         \
  (*(__IO uint32_t *)0x400E042CU) /**< \brief (PMC) PLLB Register */
#define REG_PMC_MCKR                                                           \
  (*(__IO uint32_t *)0x400E0430U) /**< \brief (PMC) Master Clock Register */
#define REG_PMC_USB                                                            \
  (*(__IO uint32_t *)0x400E0438U) /**< \brief (PMC) USB Clock Register */
#define REG_PMC_PCK                                                            \
  (*(__IO uint32_t                                                             \
         *)0x400E0440U) /**< \brief (PMC) Programmable Clock 0 Register */
#define REG_PMC_IER                                                            \
  (*(__O uint32_t *)0x400E0460U) /**< \brief (PMC) Interrupt Enable Register   \
                                  */
#define REG_PMC_IDR                                                            \
  (*(__O uint32_t *)0x400E0464U) /**< \brief (PMC) Interrupt Disable Register  \
                                  */
#define REG_PMC_SR                                                             \
  (*(__I uint32_t *)0x400E0468U) /**< \brief (PMC) Status Register */
#define REG_PMC_IMR                                                            \
  (*(__I uint32_t *)0x400E046CU) /**< \brief (PMC) Interrupt Mask Register */
#define REG_PMC_FSMR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x400E0470U) /**< \brief (PMC) Fast Startup Mode Register */
#define REG_PMC_FSPR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x400E0474U) /**< \brief (PMC) Fast Startup Polarity Register */
#define REG_PMC_FOCR                                                           \
  (*(__O uint32_t                                                              \
         *)0x400E0478U) /**< \brief (PMC) Fault Output Clear Register */
#define REG_PMC_WPMR                                                           \
  (*(__IO uint32_t                                                             \
         *)0x400E04E4U) /**< \brief (PMC) Write Protection Mode Register */
#define REG_PMC_WPSR                                                           \
  (*(__I uint32_t                                                              \
         *)0x400E04E8U) /**< \brief (PMC) Write Protection Status Register */
#define REG_PMC_PCR                                                            \
  (*(__IO uint32_t                                                             \
         *)0x400E050CU) /**< \brief (PMC) Peripheral Control Register */
#define REG_PMC_OCR                                                            \
  (*(__IO uint32_t                                                             \
         *)0x400E0510U) /**< \brief (PMC) Oscillator Calibration Register */
#define REG_PMC_SLPWK_ER0                                                      \
  (*(__O uint32_t                                                              \
         *)0x400E0514U) /**< \brief (PMC) SleepWalking Enable Register 0 */
#define REG_PMC_SLPWK_DR0                                                      \
  (*(__O uint32_t                                                              \
         *)0x400E0518U) /**< \brief (PMC) SleepWalking Disable Register 0 */
#define REG_PMC_SLPWK_SR0                                                      \
  (*(__I uint32_t                                                              \
         *)0x400E051CU) /**< \brief (PMC) SleepWalking Status Register 0 */
#define REG_PMC_SLPWK_ASR0                                                     \
  (*(__I uint32_t *)0x400E0520U) /**< \brief (PMC) SleepWalking Activity       \
                                    Status Register 0 */
#define REG_PMC_PMMR                                                           \
  (*(__IO uint32_t *)0x400E0530U) /**< \brief (PMC) PLL Maximum Multiplier     \
                                     Value Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMG55_PMC_INSTANCE_ */
