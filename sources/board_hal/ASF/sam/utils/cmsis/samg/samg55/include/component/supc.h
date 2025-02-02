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

#ifndef _SAMG55_SUPC_COMPONENT_
#define _SAMG55_SUPC_COMPONENT_

/* =============================================================================
 */
/**  SOFTWARE API DEFINITION FOR Supply Controller */
/* =============================================================================
 */
/** \addtogroup SAMG55_SUPC Supply Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Supc hardware registers */
typedef struct {
  __O uint32_t SUPC_CR;    /**< \brief (Supc Offset: 0x00) Supply Controller
                              Control Register */
  __IO uint32_t SUPC_SMMR; /**< \brief (Supc Offset: 0x04) Supply Controller
                              Supply Monitor Mode Register */
  __IO uint32_t SUPC_MR; /**< \brief (Supc Offset: 0x08) Supply Controller Mode
                            Register */
  __IO uint32_t SUPC_WUMR; /**< \brief (Supc Offset: 0x0C) Supply Controller
                              Wake-up Mode Register */
  __IO uint32_t SUPC_WUIR; /**< \brief (Supc Offset: 0x10) Supply Controller
                              Wake-up Inputs Register */
  __I uint32_t SUPC_SR; /**< \brief (Supc Offset: 0x14) Supply Controller Status
                           Register */
  __I uint32_t Reserved1[1];
  __IO uint32_t SUPC_PWMR; /**< \brief (Supc Offset: 0x1C) Supply Controller
                              Power Mode Register */
} Supc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SUPC_CR : (SUPC Offset: 0x00) Supply Controller Control Register
 * -------- */
#define SUPC_CR_VROFF (0x1u << 2) /**< \brief (SUPC_CR) Voltage Regulator Off  \
                                   */
#define SUPC_CR_VROFF_NO_EFFECT (0x0u << 2) /**< \brief (SUPC_CR) No effect.   \
                                             */
#define SUPC_CR_VROFF_STOP_VREG                                                \
  (0x1u << 2) /**< \brief (SUPC_CR) If KEY is correct, asserts the system      \
                 reset signal and stops the voltage regulator. */
#define SUPC_CR_XTALSEL                                                        \
  (0x1u << 3) /**< \brief (SUPC_CR) Crystal Oscillator Select */
#define SUPC_CR_XTALSEL_NO_EFFECT                                              \
  (0x0u << 3) /**< \brief (SUPC_CR) No effect. */
#define SUPC_CR_XTALSEL_CRYSTAL_SEL                                            \
  (0x1u << 3) /**< \brief (SUPC_CR) If KEY is correct, switches the slow clock \
                 on the crystal oscillator output. */
#define SUPC_CR_KEY_Pos 24
#define SUPC_CR_KEY_Msk                                                        \
  (0xffu << SUPC_CR_KEY_Pos) /**< \brief (SUPC_CR) Password */
#define SUPC_CR_KEY_PASSWD                                                     \
  (0xA5u << 24) /**< \brief (SUPC_CR) Writing any other value in this field    \
                   aborts the write operation.Always reads as 0. */
/* -------- SUPC_SMMR : (SUPC Offset: 0x04) Supply Controller Supply Monitor
 * Mode Register -------- */
#define SUPC_SMMR_SMTH_Pos 0
#define SUPC_SMMR_SMTH_Msk                                                     \
  (0xfu                                                                        \
   << SUPC_SMMR_SMTH_Pos) /**< \brief (SUPC_SMMR) Supply Monitor Threshold */
#define SUPC_SMMR_SMTH(value)                                                  \
  ((SUPC_SMMR_SMTH_Msk & ((value) << SUPC_SMMR_SMTH_Pos)))
#define SUPC_SMMR_SMSMPL_Pos 8
#define SUPC_SMMR_SMSMPL_Msk                                                   \
  (0x7u << SUPC_SMMR_SMSMPL_Pos) /**< \brief (SUPC_SMMR) Supply Monitor        \
                                    Sampling Period */
#define SUPC_SMMR_SMSMPL_SMD                                                   \
  (0x0u << 8) /**< \brief (SUPC_SMMR) Supply Monitor disabled */
#define SUPC_SMMR_SMSMPL_CSM                                                   \
  (0x1u << 8) /**< \brief (SUPC_SMMR) Continuous Supply Monitor */
#define SUPC_SMMR_SMSMPL_32SLCK                                                \
  (0x2u << 8) /**< \brief (SUPC_SMMR) Supply Monitor enables one SLCK period   \
                 every 32 SLCK periods */
#define SUPC_SMMR_SMSMPL_256SLCK                                               \
  (0x3u << 8) /**< \brief (SUPC_SMMR) Supply Monitor enables one SLCK period   \
                 every 256 SLCK periods */
#define SUPC_SMMR_SMSMPL_2048SLCK                                              \
  (0x4u << 8) /**< \brief (SUPC_SMMR) Supply Monitor enables one SLCK period   \
                 every 2,048 SLCK periods */
#define SUPC_SMMR_SMRSTEN                                                      \
  (0x1u << 12) /**< \brief (SUPC_SMMR) Supply Monitor Reset Enable */
#define SUPC_SMMR_SMRSTEN_NOT_ENABLE                                           \
  (0x0u << 12) /**< \brief (SUPC_SMMR) The core reset signal vddcore_nreset is \
                  not affected when a supply monitor detection occurs. */
#define SUPC_SMMR_SMRSTEN_ENABLE                                               \
  (0x1u << 12) /**< \brief (SUPC_SMMR) The core reset signal vddcore_nreset is \
                  asserted when a supply monitor detection occurs. */
#define SUPC_SMMR_SMIEN                                                        \
  (0x1u << 13) /**< \brief (SUPC_SMMR) Supply Monitor Interrupt Enable */
#define SUPC_SMMR_SMIEN_NOT_ENABLE                                             \
  (0x0u << 13) /**< \brief (SUPC_SMMR) The SUPC interrupt signal is not        \
                  affected when a supply monitor detection occurs. */
#define SUPC_SMMR_SMIEN_ENABLE                                                 \
  (0x1u << 13) /**< \brief (SUPC_SMMR) The SUPC interrupt signal is asserted   \
                  when a supply monitor detection occurs. */
/* -------- SUPC_MR : (SUPC Offset: 0x08) Supply Controller Mode Register
 * -------- */
#define SUPC_MR_BODRSTEN                                                       \
  (0x1u << 12) /**< \brief (SUPC_MR) POR Core Reset Enable */
#define SUPC_MR_BODRSTEN_NOT_ENABLE                                            \
  (0x0u << 12) /**< \brief (SUPC_MR) The core reset signal vddcore_nreset is   \
                  not affected when a brownout detection occurs. */
#define SUPC_MR_BODRSTEN_ENABLE                                                \
  (0x1u << 12) /**< \brief (SUPC_MR) The core reset signal vddcore_nreset is   \
                  asserted when a brownout detection occurs. */
#define SUPC_MR_BODDIS (0x1u << 13) /**< \brief (SUPC_MR) POR Core Disable */
#define SUPC_MR_BODDIS_ENABLE                                                  \
  (0x0u << 13) /**< \brief (SUPC_MR) The core brownout detector is enabled. */
#define SUPC_MR_BODDIS_DISABLE                                                 \
  (0x1u << 13) /**< \brief (SUPC_MR) The core brownout detector is disabled.   \
                */
#define SUPC_MR_OSCBYPASS                                                      \
  (0x1u << 20) /**< \brief (SUPC_MR) Oscillator Bypass */
#define SUPC_MR_OSCBYPASS_NO_EFFECT                                            \
  (0x0u << 20) /**< \brief (SUPC_MR) No effect. Clock selection depends on     \
                  XTALSEL value. */
#define SUPC_MR_OSCBYPASS_BYPASS                                               \
  (0x1u << 20) /**< \brief (SUPC_MR) The 32 kHz crystal oscillator is selected \
                  and put in bypass mode. */
#define SUPC_MR_CDPSWITCH                                                      \
  (0x1u << 21) /**< \brief (SUPC_MR) Cache Data SRAM Power Switch */
#define SUPC_MR_CDPSWITCH_OFF                                                  \
  (0x0u << 21) /**< \brief (SUPC_MR) The cache data SRAM is not powered. */
#define SUPC_MR_CDPSWITCH_ON                                                   \
  (0x1u << 21) /**< \brief (SUPC_MR) The cache data SRAM is powered. */
#define SUPC_MR_CTPSWITCH                                                      \
  (0x1u << 22) /**< \brief (SUPC_MR) Cache Tag SRAM Power Switch */
#define SUPC_MR_CTPSWITCH_OFF                                                  \
  (0x0u << 22) /**< \brief (SUPC_MR) The cache tag SRAM is not powered. */
#define SUPC_MR_CTPSWITCH_ON                                                   \
  (0x1u << 22) /**< \brief (SUPC_MR) The cache tag SRAM is powered. */
#define SUPC_MR_ONE                                                            \
  (0x1u << 23) /**< \brief (SUPC_MR) This bit must always be set to 1. */
#define SUPC_MR_KEY_Pos 24
#define SUPC_MR_KEY_Msk                                                        \
  (0xffu << SUPC_MR_KEY_Pos) /**< \brief (SUPC_MR) Password Key */
#define SUPC_MR_KEY_PASSWD                                                     \
  (0xA5u << 24) /**< \brief (SUPC_MR) Writing any other value in this field    \
                   aborts the write operation.Always reads as 0. */
/* -------- SUPC_WUMR : (SUPC Offset: 0x0C) Supply Controller Wake-up Mode
 * Register -------- */
#define SUPC_WUMR_SMEN                                                         \
  (0x1u << 1) /**< \brief (SUPC_WUMR) Supply Monitor Wake-up Enable */
#define SUPC_WUMR_SMEN_NOT_ENABLE                                              \
  (0x0u << 1) /**< \brief (SUPC_WUMR) The supply monitor detection has no      \
                 wake-up effect. */
#define SUPC_WUMR_SMEN_ENABLE                                                  \
  (0x1u << 1) /**< \brief (SUPC_WUMR) The supply monitor detection forces the  \
                 wake-up of the core power supply. */
#define SUPC_WUMR_RTTEN                                                        \
  (0x1u << 2) /**< \brief (SUPC_WUMR) Real-time Timer Wake-up Enable */
#define SUPC_WUMR_RTTEN_ENABLE                                                 \
  (0x1u << 2) /**< \brief (SUPC_WUMR) The RTT alarm signal forces the wake-up  \
                 of the core power supply. */
#define SUPC_WUMR_RTCEN                                                        \
  (0x1u << 3) /**< \brief (SUPC_WUMR) Real-time Clock Wake-up Enable */
#define SUPC_WUMR_RTCEN_ENABLE                                                 \
  (0x1u << 3) /**< \brief (SUPC_WUMR) The RTC alarm signal forces the wake-up  \
                 of the core power supply. */
#define SUPC_WUMR_WKUPDBC_Pos 12
#define SUPC_WUMR_WKUPDBC_Msk                                                  \
  (0x7u << SUPC_WUMR_WKUPDBC_Pos) /**< \brief (SUPC_WUMR) Wake-up Inputs       \
                                     Debouncer Period */
#define SUPC_WUMR_WKUPDBC_IMMEDIATE                                            \
  (0x0u << 12) /**< \brief (SUPC_WUMR) Immediate, no debouncing, detected      \
                  active at least on one Slow Clock edge. */
#define SUPC_WUMR_WKUPDBC_3_SCLK                                               \
  (0x1u << 12) /**< \brief (SUPC_WUMR) WKUPx shall be in its active state for  \
                  at least 3 SLCK periods */
#define SUPC_WUMR_WKUPDBC_32_SCLK                                              \
  (0x2u << 12) /**< \brief (SUPC_WUMR) WKUPx shall be in its active state for  \
                  at least 32 SLCK periods */
#define SUPC_WUMR_WKUPDBC_512_SCLK                                             \
  (0x3u << 12) /**< \brief (SUPC_WUMR) WKUPx shall be in its active state for  \
                  at least 512 SLCK periods */
#define SUPC_WUMR_WKUPDBC_4096_SCLK                                            \
  (0x4u << 12) /**< \brief (SUPC_WUMR) WKUPx shall be in its active state for  \
                  at least 4,096 SLCK periods */
#define SUPC_WUMR_WKUPDBC_32768_SCLK                                           \
  (0x5u << 12) /**< \brief (SUPC_WUMR) WKUPx shall be in its active state for  \
                  at least 32,768 SLCK periods */
/* -------- SUPC_WUIR : (SUPC Offset: 0x10) Supply Controller Wake-up Inputs
 * Register -------- */
#define SUPC_WUIR_WKUPEN0                                                      \
  (0x1u << 0) /**< \brief (SUPC_WUIR) Wake-up Input Enable 0 */
#define SUPC_WUIR_WKUPEN0_DISABLE                                              \
  (0x0u << 0) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN0_ENABLE                                               \
  (0x1u << 0) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN1                                                      \
  (0x1u << 1) /**< \brief (SUPC_WUIR) Wake-up Input Enable 1 */
#define SUPC_WUIR_WKUPEN1_DISABLE                                              \
  (0x0u << 1) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN1_ENABLE                                               \
  (0x1u << 1) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN2                                                      \
  (0x1u << 2) /**< \brief (SUPC_WUIR) Wake-up Input Enable 2 */
#define SUPC_WUIR_WKUPEN2_DISABLE                                              \
  (0x0u << 2) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN2_ENABLE                                               \
  (0x1u << 2) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN3                                                      \
  (0x1u << 3) /**< \brief (SUPC_WUIR) Wake-up Input Enable 3 */
#define SUPC_WUIR_WKUPEN3_DISABLE                                              \
  (0x0u << 3) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN3_ENABLE                                               \
  (0x1u << 3) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN4                                                      \
  (0x1u << 4) /**< \brief (SUPC_WUIR) Wake-up Input Enable 4 */
#define SUPC_WUIR_WKUPEN4_DISABLE                                              \
  (0x0u << 4) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN4_ENABLE                                               \
  (0x1u << 4) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN5                                                      \
  (0x1u << 5) /**< \brief (SUPC_WUIR) Wake-up Input Enable 5 */
#define SUPC_WUIR_WKUPEN5_DISABLE                                              \
  (0x0u << 5) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN5_ENABLE                                               \
  (0x1u << 5) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN6                                                      \
  (0x1u << 6) /**< \brief (SUPC_WUIR) Wake-up Input Enable 6 */
#define SUPC_WUIR_WKUPEN6_DISABLE                                              \
  (0x0u << 6) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN6_ENABLE                                               \
  (0x1u << 6) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN7                                                      \
  (0x1u << 7) /**< \brief (SUPC_WUIR) Wake-up Input Enable 7 */
#define SUPC_WUIR_WKUPEN7_DISABLE                                              \
  (0x0u << 7) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN7_ENABLE                                               \
  (0x1u << 7) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN8                                                      \
  (0x1u << 8) /**< \brief (SUPC_WUIR) Wake-up Input Enable 8 */
#define SUPC_WUIR_WKUPEN8_DISABLE                                              \
  (0x0u << 8) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN8_ENABLE                                               \
  (0x1u << 8) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN9                                                      \
  (0x1u << 9) /**< \brief (SUPC_WUIR) Wake-up Input Enable 9 */
#define SUPC_WUIR_WKUPEN9_DISABLE                                              \
  (0x0u << 9) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no   \
                 wake-up effect. */
#define SUPC_WUIR_WKUPEN9_ENABLE                                               \
  (0x1u << 9) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces   \
                 the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN10                                                     \
  (0x1u << 10) /**< \brief (SUPC_WUIR) Wake-up Input Enable 10 */
#define SUPC_WUIR_WKUPEN10_DISABLE                                             \
  (0x0u << 10) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no  \
                  wake-up effect. */
#define SUPC_WUIR_WKUPEN10_ENABLE                                              \
  (0x1u << 10) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces  \
                  the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN11                                                     \
  (0x1u << 11) /**< \brief (SUPC_WUIR) Wake-up Input Enable 11 */
#define SUPC_WUIR_WKUPEN11_DISABLE                                             \
  (0x0u << 11) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no  \
                  wake-up effect. */
#define SUPC_WUIR_WKUPEN11_ENABLE                                              \
  (0x1u << 11) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces  \
                  the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN12                                                     \
  (0x1u << 12) /**< \brief (SUPC_WUIR) Wake-up Input Enable 12 */
#define SUPC_WUIR_WKUPEN12_DISABLE                                             \
  (0x0u << 12) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no  \
                  wake-up effect. */
#define SUPC_WUIR_WKUPEN12_ENABLE                                              \
  (0x1u << 12) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces  \
                  the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN13                                                     \
  (0x1u << 13) /**< \brief (SUPC_WUIR) Wake-up Input Enable 13 */
#define SUPC_WUIR_WKUPEN13_DISABLE                                             \
  (0x0u << 13) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no  \
                  wake-up effect. */
#define SUPC_WUIR_WKUPEN13_ENABLE                                              \
  (0x1u << 13) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces  \
                  the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN14                                                     \
  (0x1u << 14) /**< \brief (SUPC_WUIR) Wake-up Input Enable 14 */
#define SUPC_WUIR_WKUPEN14_DISABLE                                             \
  (0x0u << 14) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no  \
                  wake-up effect. */
#define SUPC_WUIR_WKUPEN14_ENABLE                                              \
  (0x1u << 14) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces  \
                  the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPEN15                                                     \
  (0x1u << 15) /**< \brief (SUPC_WUIR) Wake-up Input Enable 15 */
#define SUPC_WUIR_WKUPEN15_DISABLE                                             \
  (0x0u << 15) /**< \brief (SUPC_WUIR) The corresponding wake-up input has no  \
                  wake-up effect. */
#define SUPC_WUIR_WKUPEN15_ENABLE                                              \
  (0x1u << 15) /**< \brief (SUPC_WUIR) The corresponding wake-up input forces  \
                  the wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT0                                                       \
  (0x1u << 16) /**< \brief (SUPC_WUIR) Wake-up Input Type 0 */
#define SUPC_WUIR_WKUPT0_LOW                                                   \
  (0x0u << 16) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT0_HIGH                                                  \
  (0x1u << 16) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT1                                                       \
  (0x1u << 17) /**< \brief (SUPC_WUIR) Wake-up Input Type 1 */
#define SUPC_WUIR_WKUPT1_LOW                                                   \
  (0x0u << 17) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT1_HIGH                                                  \
  (0x1u << 17) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT2                                                       \
  (0x1u << 18) /**< \brief (SUPC_WUIR) Wake-up Input Type 2 */
#define SUPC_WUIR_WKUPT2_LOW                                                   \
  (0x0u << 18) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT2_HIGH                                                  \
  (0x1u << 18) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT3                                                       \
  (0x1u << 19) /**< \brief (SUPC_WUIR) Wake-up Input Type 3 */
#define SUPC_WUIR_WKUPT3_LOW                                                   \
  (0x0u << 19) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT3_HIGH                                                  \
  (0x1u << 19) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT4                                                       \
  (0x1u << 20) /**< \brief (SUPC_WUIR) Wake-up Input Type 4 */
#define SUPC_WUIR_WKUPT4_LOW                                                   \
  (0x0u << 20) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT4_HIGH                                                  \
  (0x1u << 20) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT5                                                       \
  (0x1u << 21) /**< \brief (SUPC_WUIR) Wake-up Input Type 5 */
#define SUPC_WUIR_WKUPT5_LOW                                                   \
  (0x0u << 21) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT5_HIGH                                                  \
  (0x1u << 21) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT6                                                       \
  (0x1u << 22) /**< \brief (SUPC_WUIR) Wake-up Input Type 6 */
#define SUPC_WUIR_WKUPT6_LOW                                                   \
  (0x0u << 22) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT6_HIGH                                                  \
  (0x1u << 22) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT7                                                       \
  (0x1u << 23) /**< \brief (SUPC_WUIR) Wake-up Input Type 7 */
#define SUPC_WUIR_WKUPT7_LOW                                                   \
  (0x0u << 23) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT7_HIGH                                                  \
  (0x1u << 23) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT8                                                       \
  (0x1u << 24) /**< \brief (SUPC_WUIR) Wake-up Input Type 8 */
#define SUPC_WUIR_WKUPT8_LOW                                                   \
  (0x0u << 24) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT8_HIGH                                                  \
  (0x1u << 24) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT9                                                       \
  (0x1u << 25) /**< \brief (SUPC_WUIR) Wake-up Input Type 9 */
#define SUPC_WUIR_WKUPT9_LOW                                                   \
  (0x0u << 25) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT9_HIGH                                                  \
  (0x1u << 25) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT10                                                      \
  (0x1u << 26) /**< \brief (SUPC_WUIR) Wake-up Input Type 10 */
#define SUPC_WUIR_WKUPT10_LOW                                                  \
  (0x0u << 26) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT10_HIGH                                                 \
  (0x1u << 26) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT11                                                      \
  (0x1u << 27) /**< \brief (SUPC_WUIR) Wake-up Input Type 11 */
#define SUPC_WUIR_WKUPT11_LOW                                                  \
  (0x0u << 27) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT11_HIGH                                                 \
  (0x1u << 27) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT12                                                      \
  (0x1u << 28) /**< \brief (SUPC_WUIR) Wake-up Input Type 12 */
#define SUPC_WUIR_WKUPT12_LOW                                                  \
  (0x0u << 28) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT12_HIGH                                                 \
  (0x1u << 28) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT13                                                      \
  (0x1u << 29) /**< \brief (SUPC_WUIR) Wake-up Input Type 13 */
#define SUPC_WUIR_WKUPT13_LOW                                                  \
  (0x0u << 29) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT13_HIGH                                                 \
  (0x1u << 29) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT14                                                      \
  (0x1u << 30) /**< \brief (SUPC_WUIR) Wake-up Input Type 14 */
#define SUPC_WUIR_WKUPT14_LOW                                                  \
  (0x0u << 30) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT14_HIGH                                                 \
  (0x1u << 30) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT15                                                      \
  (0x1u << 31) /**< \brief (SUPC_WUIR) Wake-up Input Type 15 */
#define SUPC_WUIR_WKUPT15_LOW                                                  \
  (0x0u << 31) /**< \brief (SUPC_WUIR) A low level for a period defined by     \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
#define SUPC_WUIR_WKUPT15_HIGH                                                 \
  (0x1u << 31) /**< \brief (SUPC_WUIR) A high level for a period defined by    \
                  WKUPDBC on the corresponding wake-up input forces the        \
                  wake-up of the core power supply. */
/* -------- SUPC_SR : (SUPC Offset: 0x14) Supply Controller Status Register
 * -------- */
#define SUPC_SR_WKUPS (0x1u << 1) /**< \brief (SUPC_SR) WKUP Wake-up Status */
#define SUPC_SR_WKUPS_NO                                                       \
  (0x0u << 1) /**< \brief (SUPC_SR) No wake-up due to the assertion of the     \
                 WKUP pins has occurred since the last read of SUPC_SR. */
#define SUPC_SR_WKUPS_PRESENT                                                  \
  (0x1u                                                                        \
   << 1) /**< \brief (SUPC_SR) At least one wake-up due to the assertion of    \
            the WKUP pins has occurred since the last read of SUPC_SR. */
#define SUPC_SR_BODRSTS                                                        \
  (0x1u << 3) /**< \brief (SUPC_SR) Brownout Detector Reset Status */
#define SUPC_SR_BODRSTS_NO                                                     \
  (0x0u << 3) /**< \brief (SUPC_SR) No core brownout rising edge event has     \
                 been detected since the last read of the SUPC_SR. */
#define SUPC_SR_BODRSTS_PRESENT                                                \
  (0x1u                                                                        \
   << 3) /**< \brief (SUPC_SR) At least one brownout output rising edge event  \
            has been detected since the last read of the SUPC_SR. */
#define SUPC_SR_SMRSTS                                                         \
  (0x1u << 4) /**< \brief (SUPC_SR) Supply Monitor Reset Status */
#define SUPC_SR_SMRSTS_NO                                                      \
  (0x0u << 4) /**< \brief (SUPC_SR) No supply monitor detection has generated  \
                 a core reset since the last read of the SUPC_SR. */
#define SUPC_SR_SMRSTS_PRESENT                                                 \
  (0x1u << 4) /**< \brief (SUPC_SR) At least one supply monitor detection has  \
                 generated a core reset since the last read of the SUPC_SR. */
#define SUPC_SR_SMS (0x1u << 5) /**< \brief (SUPC_SR) Supply Monitor Status */
#define SUPC_SR_SMS_NO                                                         \
  (0x0u << 5) /**< \brief (SUPC_SR) No supply monitor detection since the last \
                 read of SUPC_SR. */
#define SUPC_SR_SMS_PRESENT                                                    \
  (0x1u << 5) /**< \brief (SUPC_SR) At least one supply monitor detection      \
                 since the last read of SUPC_SR. */
#define SUPC_SR_SMOS                                                           \
  (0x1u << 6) /**< \brief (SUPC_SR) Supply Monitor Output Status */
#define SUPC_SR_SMOS_HIGH                                                      \
  (0x0u << 6) /**< \brief (SUPC_SR) The supply monitor detected VDDIO higher   \
                 than its threshold at its last measurement. */
#define SUPC_SR_SMOS_LOW                                                       \
  (0x1u << 6) /**< \brief (SUPC_SR) The supply monitor detected VDDIO lower    \
                 than its threshold at its last measurement. */
#define SUPC_SR_OSCSEL                                                         \
  (0x1u << 7) /**< \brief (SUPC_SR) 32-kHz Oscillator Selection Status */
#define SUPC_SR_OSCSEL_RC                                                      \
  (0x0u << 7) /**< \brief (SUPC_SR) The slow clock SLCK is generated by the    \
                 embedded 32 kHz RC oscillator. */
#define SUPC_SR_OSCSEL_CRYST                                                   \
  (0x1u << 7) /**< \brief (SUPC_SR) The slow clock SLCK is generated by the 32 \
                 kHz crystal oscillator. */
#define SUPC_SR_WKUPIS0                                                        \
  (0x1u << 16) /**< \brief (SUPC_SR) WKUP Input Status 0 */
#define SUPC_SR_WKUPIS0_DISABLED                                               \
  (0x0u << 16) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS0_ENABLED                                                \
  (0x1u                                                                        \
   << 16) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS1                                                        \
  (0x1u << 17) /**< \brief (SUPC_SR) WKUP Input Status 1 */
#define SUPC_SR_WKUPIS1_DISABLED                                               \
  (0x0u << 17) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS1_ENABLED                                                \
  (0x1u                                                                        \
   << 17) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS2                                                        \
  (0x1u << 18) /**< \brief (SUPC_SR) WKUP Input Status 2 */
#define SUPC_SR_WKUPIS2_DISABLED                                               \
  (0x0u << 18) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS2_ENABLED                                                \
  (0x1u                                                                        \
   << 18) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS3                                                        \
  (0x1u << 19) /**< \brief (SUPC_SR) WKUP Input Status 3 */
#define SUPC_SR_WKUPIS3_DISABLED                                               \
  (0x0u << 19) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS3_ENABLED                                                \
  (0x1u                                                                        \
   << 19) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS4                                                        \
  (0x1u << 20) /**< \brief (SUPC_SR) WKUP Input Status 4 */
#define SUPC_SR_WKUPIS4_DISABLED                                               \
  (0x0u << 20) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS4_ENABLED                                                \
  (0x1u                                                                        \
   << 20) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS5                                                        \
  (0x1u << 21) /**< \brief (SUPC_SR) WKUP Input Status 5 */
#define SUPC_SR_WKUPIS5_DISABLED                                               \
  (0x0u << 21) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS5_ENABLED                                                \
  (0x1u                                                                        \
   << 21) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS6                                                        \
  (0x1u << 22) /**< \brief (SUPC_SR) WKUP Input Status 6 */
#define SUPC_SR_WKUPIS6_DISABLED                                               \
  (0x0u << 22) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS6_ENABLED                                                \
  (0x1u                                                                        \
   << 22) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS7                                                        \
  (0x1u << 23) /**< \brief (SUPC_SR) WKUP Input Status 7 */
#define SUPC_SR_WKUPIS7_DISABLED                                               \
  (0x0u << 23) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS7_ENABLED                                                \
  (0x1u                                                                        \
   << 23) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS8                                                        \
  (0x1u << 24) /**< \brief (SUPC_SR) WKUP Input Status 8 */
#define SUPC_SR_WKUPIS8_DISABLED                                               \
  (0x0u << 24) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS8_ENABLED                                                \
  (0x1u                                                                        \
   << 24) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS9                                                        \
  (0x1u << 25) /**< \brief (SUPC_SR) WKUP Input Status 9 */
#define SUPC_SR_WKUPIS9_DISABLED                                               \
  (0x0u << 25) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS9_ENABLED                                                \
  (0x1u                                                                        \
   << 25) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS10                                                       \
  (0x1u << 26) /**< \brief (SUPC_SR) WKUP Input Status 10 */
#define SUPC_SR_WKUPIS10_DISABLED                                              \
  (0x0u << 26) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS10_ENABLED                                               \
  (0x1u                                                                        \
   << 26) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS11                                                       \
  (0x1u << 27) /**< \brief (SUPC_SR) WKUP Input Status 11 */
#define SUPC_SR_WKUPIS11_DISABLED                                              \
  (0x0u << 27) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS11_ENABLED                                               \
  (0x1u                                                                        \
   << 27) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS12                                                       \
  (0x1u << 28) /**< \brief (SUPC_SR) WKUP Input Status 12 */
#define SUPC_SR_WKUPIS12_DISABLED                                              \
  (0x0u << 28) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS12_ENABLED                                               \
  (0x1u                                                                        \
   << 28) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS13                                                       \
  (0x1u << 29) /**< \brief (SUPC_SR) WKUP Input Status 13 */
#define SUPC_SR_WKUPIS13_DISABLED                                              \
  (0x0u << 29) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS13_ENABLED                                               \
  (0x1u                                                                        \
   << 29) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS14                                                       \
  (0x1u << 30) /**< \brief (SUPC_SR) WKUP Input Status 14 */
#define SUPC_SR_WKUPIS14_DISABLED                                              \
  (0x0u << 30) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS14_ENABLED                                               \
  (0x1u                                                                        \
   << 30) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
#define SUPC_SR_WKUPIS15                                                       \
  (0x1u << 31) /**< \brief (SUPC_SR) WKUP Input Status 15 */
#define SUPC_SR_WKUPIS15_DISABLED                                              \
  (0x0u << 31) /**< \brief (SUPC_SR) The corresponding wake-up input is        \
                  disabled, or was inactive at the time the debouncer          \
                  triggered a wake-up event. */
#define SUPC_SR_WKUPIS15_ENABLED                                               \
  (0x1u                                                                        \
   << 31) /**< \brief (SUPC_SR) The corresponding wake-up input was active at  \
             the time the debouncer triggered a wake-up event. */
/* -------- SUPC_PWMR : (SUPC Offset: 0x1C) Supply Controller Power Mode
 * Register -------- */
#define SUPC_PWMR_LPOWERS                                                      \
  (0x1u << 0) /**< \brief (SUPC_PWMR) Low Power Value Selection */
#define SUPC_PWMR_LPOWERS_FACTORY                                              \
  (0x0u                                                                        \
   << 0) /**< \brief (SUPC_PWMR) The trimming value applied to the regulator   \
            when the device is in wait mode. This value is factory-defined. */
#define SUPC_PWMR_LPOWERS_USER                                                 \
  (0x1u                                                                        \
   << 0) /**< \brief (SUPC_PWMR) The trimming value applied to the regulator   \
            is defined by the value programmed in the LPOWERx bits. */
#define SUPC_PWMR_LPOWER0 (0x1u << 1) /**< \brief (SUPC_PWMR) Low Power Value  \
                                       */
#define SUPC_PWMR_LPOWER1 (0x1u << 2) /**< \brief (SUPC_PWMR) Low Power Value  \
                                       */
#define SUPC_PWMR_LPOWER2 (0x1u << 3) /**< \brief (SUPC_PWMR) Low Power Value  \
                                       */
#define SUPC_PWMR_LPOWER3 (0x1u << 4) /**< \brief (SUPC_PWMR) Low Power Value  \
                                       */
#define SUPC_PWMR_STUPTIME                                                     \
  (0x1u                                                                        \
   << 7) /**< \brief (SUPC_PWMR) Start-up Time when Resuming from Wait Mode */
#define SUPC_PWMR_STUPTIME_FAST                                                \
  (0x0u << 7) /**< \brief (SUPC_PWMR) Fast start-up. */
#define SUPC_PWMR_STUPTIME_SLOW                                                \
  (0x1u << 7) /**< \brief (SUPC_PWMR) Slow start-up. */
#define SUPC_PWMR_ECPWRS                                                       \
  (0x1u << 8) /**< \brief (SUPC_PWMR) Enhanced Custom Power Value Selection */
#define SUPC_PWMR_ECPWRS_FACTORY                                               \
  (0x0u << 8) /**< \brief (SUPC_PWMR) The trimming value applied to the        \
                 regulator when the device is in active mode. This value is    \
                 factory-defined. */
#define SUPC_PWMR_ECPWRS_USER                                                  \
  (0x1u                                                                        \
   << 8) /**< \brief (SUPC_PWMR) The trimming value applied to the regulator   \
            is defined by the value programmed in ECPWRx bits. */
#define SUPC_PWMR_ECPWR0                                                       \
  (0x1u << 9) /**< \brief (SUPC_PWMR) Enhanced Custom Power Value */
#define SUPC_PWMR_ECPWR1                                                       \
  (0x1u << 10) /**< \brief (SUPC_PWMR) Enhanced Custom Power Value */
#define SUPC_PWMR_ECPWR2                                                       \
  (0x1u << 11) /**< \brief (SUPC_PWMR) Enhanced Custom Power Value */
#define SUPC_PWMR_ECPWR3                                                       \
  (0x1u << 12) /**< \brief (SUPC_PWMR) Enhanced Custom Power Value */
#define SUPC_PWMR_SRAM0ON                                                      \
  (0x1u << 16) /**< \brief (SUPC_PWMR) SRAM Power Control */
#define SUPC_PWMR_SRAM0ON_OFF                                                  \
  (0x0u << 16) /**< \brief (SUPC_PWMR) SRAMx is not powered. */
#define SUPC_PWMR_SRAM0ON_ON                                                   \
  (0x1u << 16) /**< \brief (SUPC_PWMR) SRAMx is powered. */
#define SUPC_PWMR_SRAM1ON                                                      \
  (0x1u << 17) /**< \brief (SUPC_PWMR) SRAM Power Control */
#define SUPC_PWMR_SRAM1ON_OFF                                                  \
  (0x0u << 17) /**< \brief (SUPC_PWMR) SRAMx is not powered. */
#define SUPC_PWMR_SRAM1ON_ON                                                   \
  (0x1u << 17) /**< \brief (SUPC_PWMR) SRAMx is powered. */
#define SUPC_PWMR_SRAM2ON                                                      \
  (0x1u << 18) /**< \brief (SUPC_PWMR) SRAM Power Control */
#define SUPC_PWMR_SRAM2ON_OFF                                                  \
  (0x0u << 18) /**< \brief (SUPC_PWMR) SRAMx is not powered. */
#define SUPC_PWMR_SRAM2ON_ON                                                   \
  (0x1u << 18) /**< \brief (SUPC_PWMR) SRAMx is powered. */
#define SUPC_PWMR_SRAM3ON                                                      \
  (0x1u << 19) /**< \brief (SUPC_PWMR) SRAM Power Control */
#define SUPC_PWMR_SRAM3ON_OFF                                                  \
  (0x0u << 19) /**< \brief (SUPC_PWMR) SRAMx is not powered. */
#define SUPC_PWMR_SRAM3ON_ON                                                   \
  (0x1u << 19) /**< \brief (SUPC_PWMR) SRAMx is powered. */
#define SUPC_PWMR_SRAM4ON                                                      \
  (0x1u << 20) /**< \brief (SUPC_PWMR) SRAM Power Control */
#define SUPC_PWMR_SRAM4ON_OFF                                                  \
  (0x0u << 20) /**< \brief (SUPC_PWMR) SRAMx is not powered. */
#define SUPC_PWMR_SRAM4ON_ON                                                   \
  (0x1u << 20) /**< \brief (SUPC_PWMR) SRAMx is powered. */
#define SUPC_PWMR_SRAM5ON                                                      \
  (0x1u << 21) /**< \brief (SUPC_PWMR) SRAM Power Control */
#define SUPC_PWMR_SRAM5ON_OFF                                                  \
  (0x0u << 21) /**< \brief (SUPC_PWMR) SRAMx is not powered. */
#define SUPC_PWMR_SRAM5ON_ON                                                   \
  (0x1u << 21) /**< \brief (SUPC_PWMR) SRAMx is powered. */
#define SUPC_PWMR_SRAM6ON                                                      \
  (0x1u << 22) /**< \brief (SUPC_PWMR) SRAM Power Control */
#define SUPC_PWMR_SRAM6ON_OFF                                                  \
  (0x0u << 22) /**< \brief (SUPC_PWMR) SRAMx is not powered. */
#define SUPC_PWMR_SRAM6ON_ON                                                   \
  (0x1u << 22) /**< \brief (SUPC_PWMR) SRAMx is powered. */
#define SUPC_PWMR_DPRAMON                                                      \
  (0x1u << 23) /**< \brief (SUPC_PWMR) Dual-port RAM Power Control */
#define SUPC_PWMR_DPRAMON_OFF                                                  \
  (0x0u << 23) /**< \brief (SUPC_PWMR) USB dual-port RAM is not powered. */
#define SUPC_PWMR_DPRAMON_ON                                                   \
  (0x1u << 23) /**< \brief (SUPC_PWMR) USB dual-port RAM is powered. */
#define SUPC_PWMR_KEY_Pos 24
#define SUPC_PWMR_KEY_Msk                                                      \
  (0xffu << SUPC_PWMR_KEY_Pos) /**< \brief (SUPC_PWMR) Password Key */
#define SUPC_PWMR_KEY_PASSWD                                                   \
  (0x5Au << 24) /**< \brief (SUPC_PWMR) Writing any other value in this field  \
                   aborts the write operation.Always reads as 0. */

/*@}*/

#endif /* _SAMG55_SUPC_COMPONENT_ */
