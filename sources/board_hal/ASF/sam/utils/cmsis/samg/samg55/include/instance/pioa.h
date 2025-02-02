/**
 * \file
 *
 * Copyright (c) 2014-2016 Atmel Corporation. All rights reserved.
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

#ifndef _SAMG55_PIOA_INSTANCE_
#define _SAMG55_PIOA_INSTANCE_

/* ========== Register definition for PIOA peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PIOA_PER (0x400E0E00U) /**< \brief (PIOA) PIO Enable Register */
#define REG_PIOA_PDR (0x400E0E04U) /**< \brief (PIOA) PIO Disable Register */
#define REG_PIOA_PSR (0x400E0E08U) /**< \brief (PIOA) PIO Status Register */
#define REG_PIOA_OER (0x400E0E10U) /**< \brief (PIOA) Output Enable Register   \
                                    */
#define REG_PIOA_ODR (0x400E0E14U) /**< \brief (PIOA) Output Disable Register  \
                                    */
#define REG_PIOA_OSR (0x400E0E18U) /**< \brief (PIOA) Output Status Register   \
                                    */
#define REG_PIOA_IFER                                                          \
  (0x400E0E20U) /**< \brief (PIOA) Glitch Input Filter Enable Register */
#define REG_PIOA_IFDR                                                          \
  (0x400E0E24U) /**< \brief (PIOA) Glitch Input Filter Disable Register */
#define REG_PIOA_IFSR                                                          \
  (0x400E0E28U) /**< \brief (PIOA) Glitch Input Filter Status Register */
#define REG_PIOA_SODR                                                          \
  (0x400E0E30U) /**< \brief (PIOA) Set Output Data Register */
#define REG_PIOA_CODR                                                          \
  (0x400E0E34U) /**< \brief (PIOA) Clear Output Data Register */
#define REG_PIOA_ODSR                                                          \
  (0x400E0E38U) /**< \brief (PIOA) Output Data Status Register */
#define REG_PIOA_PDSR                                                          \
  (0x400E0E3CU) /**< \brief (PIOA) Pin Data Status Register */
#define REG_PIOA_IER                                                           \
  (0x400E0E40U) /**< \brief (PIOA) Interrupt Enable Register */
#define REG_PIOA_IDR                                                           \
  (0x400E0E44U) /**< \brief (PIOA) Interrupt Disable Register */
#define REG_PIOA_IMR (0x400E0E48U) /**< \brief (PIOA) Interrupt Mask Register  \
                                    */
#define REG_PIOA_ISR                                                           \
  (0x400E0E4CU) /**< \brief (PIOA) Interrupt Status Register */
#define REG_PIOA_MDER                                                          \
  (0x400E0E50U) /**< \brief (PIOA) Multi-driver Enable Register */
#define REG_PIOA_MDDR                                                          \
  (0x400E0E54U) /**< \brief (PIOA) Multi-driver Disable Register */
#define REG_PIOA_MDSR                                                          \
  (0x400E0E58U) /**< \brief (PIOA) Multi-driver Status Register */
#define REG_PIOA_PUDR                                                          \
  (0x400E0E60U) /**< \brief (PIOA) Pull-up Disable Register */
#define REG_PIOA_PUER                                                          \
  (0x400E0E64U) /**< \brief (PIOA) Pull-up Enable Register */
#define REG_PIOA_PUSR                                                          \
  (0x400E0E68U) /**< \brief (PIOA) Pad Pull-up Status Register */
#define REG_PIOA_ABCDSR                                                        \
  (0x400E0E70U) /**< \brief (PIOA) Peripheral Select Register */
#define REG_PIOA_IFSCDR                                                        \
  (0x400E0E80U) /**< \brief (PIOA) Input Filter Slow Clock Disable Register */
#define REG_PIOA_IFSCER                                                        \
  (0x400E0E84U) /**< \brief (PIOA) Input Filter Slow Clock Enable Register */
#define REG_PIOA_IFSCSR                                                        \
  (0x400E0E88U) /**< \brief (PIOA) Input Filter Slow Clock Status Register */
#define REG_PIOA_SCDR                                                          \
  (0x400E0E8CU) /**< \brief (PIOA) Slow Clock Divider Debouncing Register */
#define REG_PIOA_PPDDR                                                         \
  (0x400E0E90U) /**< \brief (PIOA) Pad Pull-down Disable Register */
#define REG_PIOA_PPDER                                                         \
  (0x400E0E94U) /**< \brief (PIOA) Pad Pull-down Enable Register */
#define REG_PIOA_PPDSR                                                         \
  (0x400E0E98U) /**< \brief (PIOA) Pad Pull-down Status Register */
#define REG_PIOA_OWER (0x400E0EA0U) /**< \brief (PIOA) Output Write Enable */
#define REG_PIOA_OWDR (0x400E0EA4U) /**< \brief (PIOA) Output Write Disable */
#define REG_PIOA_OWSR                                                          \
  (0x400E0EA8U) /**< \brief (PIOA) Output Write Status Register */
#define REG_PIOA_AIMER                                                         \
  (0x400E0EB0U) /**< \brief (PIOA) Additional Interrupt Modes Enable Register  \
                 */
#define REG_PIOA_AIMDR                                                         \
  (0x400E0EB4U) /**< \brief (PIOA) Additional Interrupt Modes Disable Register \
                 */
#define REG_PIOA_AIMMR                                                         \
  (0x400E0EB8U) /**< \brief (PIOA) Additional Interrupt Modes Mask Register */
#define REG_PIOA_ESR (0x400E0EC0U) /**< \brief (PIOA) Edge Select Register */
#define REG_PIOA_LSR (0x400E0EC4U) /**< \brief (PIOA) Level Select Register */
#define REG_PIOA_ELSR                                                          \
  (0x400E0EC8U) /**< \brief (PIOA) Edge/Level Status Register */
#define REG_PIOA_FELLSR                                                        \
  (0x400E0ED0U) /**< \brief (PIOA) Falling Edge/Low-Level Select Register */
#define REG_PIOA_REHLSR                                                        \
  (0x400E0ED4U) /**< \brief (PIOA) Rising Edge/High-Level Select Register */
#define REG_PIOA_FRLHSR                                                        \
  (0x400E0ED8U) /**< \brief (PIOA) Fall/Rise - Low/High Status Register */
#define REG_PIOA_WPMR                                                          \
  (0x400E0EE4U) /**< \brief (PIOA) Write Protection Mode Register */
#define REG_PIOA_WPSR                                                          \
  (0x400E0EE8U) /**< \brief (PIOA) Write Protection Status Register */
#define REG_PIOA_SCHMITT                                                       \
  (0x400E0F00U) /**< \brief (PIOA) Schmitt Trigger Register */
#define REG_PIOA_DRIVER                                                        \
  (0x400E0F10U) /**< \brief (PIOA) PIO I/O Drive Register */
#else
#define REG_PIOA_PER                                                           \
  (*(__O uint32_t *)0x400E0E00U) /**< \brief (PIOA) PIO Enable Register */
#define REG_PIOA_PDR                                                           \
  (*(__O uint32_t *)0x400E0E04U) /**< \brief (PIOA) PIO Disable Register */
#define REG_PIOA_PSR                                                           \
  (*(__I uint32_t *)0x400E0E08U) /**< \brief (PIOA) PIO Status Register */
#define REG_PIOA_OER                                                           \
  (*(__O uint32_t *)0x400E0E10U) /**< \brief (PIOA) Output Enable Register */
#define REG_PIOA_ODR                                                           \
  (*(__O uint32_t *)0x400E0E14U) /**< \brief (PIOA) Output Disable Register */
#define REG_PIOA_OSR                                                           \
  (*(__I uint32_t *)0x400E0E18U) /**< \brief (PIOA) Output Status Register */
#define REG_PIOA_IFER                                                          \
  (*(__O uint32_t *)0x400E0E20U) /**< \brief (PIOA) Glitch Input Filter Enable \
                                    Register */
#define REG_PIOA_IFDR                                                          \
  (*(__O uint32_t *)0x400E0E24U) /**< \brief (PIOA) Glitch Input Filter        \
                                    Disable Register */
#define REG_PIOA_IFSR                                                          \
  (*(__I uint32_t *)0x400E0E28U) /**< \brief (PIOA) Glitch Input Filter Status \
                                    Register */
#define REG_PIOA_SODR                                                          \
  (*(__O uint32_t *)0x400E0E30U) /**< \brief (PIOA) Set Output Data Register   \
                                  */
#define REG_PIOA_CODR                                                          \
  (*(__O uint32_t                                                              \
         *)0x400E0E34U) /**< \brief (PIOA) Clear Output Data Register */
#define REG_PIOA_ODSR                                                          \
  (*(__IO uint32_t                                                             \
         *)0x400E0E38U) /**< \brief (PIOA) Output Data Status Register */
#define REG_PIOA_PDSR                                                          \
  (*(__I uint32_t *)0x400E0E3CU) /**< \brief (PIOA) Pin Data Status Register   \
                                  */
#define REG_PIOA_IER                                                           \
  (*(__O uint32_t *)0x400E0E40U) /**< \brief (PIOA) Interrupt Enable Register  \
                                  */
#define REG_PIOA_IDR                                                           \
  (*(__O uint32_t                                                              \
         *)0x400E0E44U) /**< \brief (PIOA) Interrupt Disable Register */
#define REG_PIOA_IMR                                                           \
  (*(__I uint32_t *)0x400E0E48U) /**< \brief (PIOA) Interrupt Mask Register */
#define REG_PIOA_ISR                                                           \
  (*(__I uint32_t *)0x400E0E4CU) /**< \brief (PIOA) Interrupt Status Register  \
                                  */
#define REG_PIOA_MDER                                                          \
  (*(__O uint32_t                                                              \
         *)0x400E0E50U) /**< \brief (PIOA) Multi-driver Enable Register */
#define REG_PIOA_MDDR                                                          \
  (*(__O uint32_t                                                              \
         *)0x400E0E54U) /**< \brief (PIOA) Multi-driver Disable Register */
#define REG_PIOA_MDSR                                                          \
  (*(__I uint32_t                                                              \
         *)0x400E0E58U) /**< \brief (PIOA) Multi-driver Status Register */
#define REG_PIOA_PUDR                                                          \
  (*(__O uint32_t *)0x400E0E60U) /**< \brief (PIOA) Pull-up Disable Register   \
                                  */
#define REG_PIOA_PUER                                                          \
  (*(__O uint32_t *)0x400E0E64U) /**< \brief (PIOA) Pull-up Enable Register */
#define REG_PIOA_PUSR                                                          \
  (*(__I uint32_t                                                              \
         *)0x400E0E68U) /**< \brief (PIOA) Pad Pull-up Status Register */
#define REG_PIOA_ABCDSR                                                        \
  (*(__IO uint32_t                                                             \
         *)0x400E0E70U) /**< \brief (PIOA) Peripheral Select Register */
#define REG_PIOA_IFSCDR                                                        \
  (*(__O uint32_t *)0x400E0E80U) /**< \brief (PIOA) Input Filter Slow Clock    \
                                    Disable Register */
#define REG_PIOA_IFSCER                                                        \
  (*(__O uint32_t *)0x400E0E84U) /**< \brief (PIOA) Input Filter Slow Clock    \
                                    Enable Register */
#define REG_PIOA_IFSCSR                                                        \
  (*(__I uint32_t *)0x400E0E88U) /**< \brief (PIOA) Input Filter Slow Clock    \
                                    Status Register */
#define REG_PIOA_SCDR                                                          \
  (*(__IO uint32_t *)0x400E0E8CU) /**< \brief (PIOA) Slow Clock Divider        \
                                     Debouncing Register */
#define REG_PIOA_PPDDR                                                         \
  (*(__O uint32_t                                                              \
         *)0x400E0E90U) /**< \brief (PIOA) Pad Pull-down Disable Register */
#define REG_PIOA_PPDER                                                         \
  (*(__O uint32_t                                                              \
         *)0x400E0E94U) /**< \brief (PIOA) Pad Pull-down Enable Register */
#define REG_PIOA_PPDSR                                                         \
  (*(__I uint32_t                                                              \
         *)0x400E0E98U) /**< \brief (PIOA) Pad Pull-down Status Register */
#define REG_PIOA_OWER                                                          \
  (*(__O uint32_t *)0x400E0EA0U) /**< \brief (PIOA) Output Write Enable */
#define REG_PIOA_OWDR                                                          \
  (*(__O uint32_t *)0x400E0EA4U) /**< \brief (PIOA) Output Write Disable */
#define REG_PIOA_OWSR                                                          \
  (*(__I uint32_t                                                              \
         *)0x400E0EA8U) /**< \brief (PIOA) Output Write Status Register */
#define REG_PIOA_AIMER                                                         \
  (*(__O uint32_t *)0x400E0EB0U) /**< \brief (PIOA) Additional Interrupt Modes \
                                    Enable Register */
#define REG_PIOA_AIMDR                                                         \
  (*(__O uint32_t *)0x400E0EB4U) /**< \brief (PIOA) Additional Interrupt Modes \
                                    Disable Register */
#define REG_PIOA_AIMMR                                                         \
  (*(__I uint32_t *)0x400E0EB8U) /**< \brief (PIOA) Additional Interrupt Modes \
                                    Mask Register */
#define REG_PIOA_ESR                                                           \
  (*(__O uint32_t *)0x400E0EC0U) /**< \brief (PIOA) Edge Select Register */
#define REG_PIOA_LSR                                                           \
  (*(__O uint32_t *)0x400E0EC4U) /**< \brief (PIOA) Level Select Register */
#define REG_PIOA_ELSR                                                          \
  (*(__I uint32_t                                                              \
         *)0x400E0EC8U) /**< \brief (PIOA) Edge/Level Status Register */
#define REG_PIOA_FELLSR                                                        \
  (*(__O uint32_t *)0x400E0ED0U) /**< \brief (PIOA) Falling Edge/Low-Level     \
                                    Select Register */
#define REG_PIOA_REHLSR                                                        \
  (*(__O uint32_t *)0x400E0ED4U) /**< \brief (PIOA) Rising Edge/High-Level     \
                                    Select Register */
#define REG_PIOA_FRLHSR                                                        \
  (*(__I uint32_t *)0x400E0ED8U) /**< \brief (PIOA) Fall/Rise - Low/High       \
                                    Status Register */
#define REG_PIOA_WPMR                                                          \
  (*(__IO uint32_t                                                             \
         *)0x400E0EE4U) /**< \brief (PIOA) Write Protection Mode Register */
#define REG_PIOA_WPSR                                                          \
  (*(__I uint32_t                                                              \
         *)0x400E0EE8U) /**< \brief (PIOA) Write Protection Status Register */
#define REG_PIOA_SCHMITT                                                       \
  (*(__IO uint32_t *)0x400E0F00U) /**< \brief (PIOA) Schmitt Trigger Register  \
                                   */
#define REG_PIOA_DRIVER                                                        \
  (*(__IO uint32_t *)0x400E0F10U) /**< \brief (PIOA) PIO I/O Drive Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMG55_PIOA_INSTANCE_ */
