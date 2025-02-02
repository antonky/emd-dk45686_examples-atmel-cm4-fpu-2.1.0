/* ----------------------------------------------------------------------------
 */
/*                  Atmel Microcontroller Software Support */
/*                       SAM Software Package License */
/* ----------------------------------------------------------------------------
 */
/* Copyright (c) 2014-2015 Atmel Corporation. All rights reserved. */
/*                                                                              */
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

#ifndef _SAMG55_ADC_COMPONENT_
#define _SAMG55_ADC_COMPONENT_

/* =============================================================================
 */
/**  SOFTWARE API DEFINITION FOR Analog-to-Digital Converter */
/* =============================================================================
 */
/** \addtogroup SAMG55_ADC Analog-to-Digital Converter */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Adc hardware registers */
typedef struct {
  __O uint32_t ADC_CR;  /**< \brief (Adc Offset: 0x00) Control Register */
  __IO uint32_t ADC_MR; /**< \brief (Adc Offset: 0x04) Mode Register */
  __IO uint32_t
      ADC_SEQR1; /**< \brief (Adc Offset: 0x08) Channel Sequence Register 1 */
  __I uint32_t Reserved1[1];
  __O uint32_t
      ADC_CHER; /**< \brief (Adc Offset: 0x10) Channel Enable Register */
  __O uint32_t
      ADC_CHDR; /**< \brief (Adc Offset: 0x14) Channel Disable Register */
  __I uint32_t
      ADC_CHSR; /**< \brief (Adc Offset: 0x18) Channel Status Register */
  __I uint32_t Reserved2[1];
  __I uint32_t
      ADC_LCDR; /**< \brief (Adc Offset: 0x20) Last Converted Data Register */
  __O uint32_t
      ADC_IER; /**< \brief (Adc Offset: 0x24) Interrupt Enable Register */
  __O uint32_t
      ADC_IDR; /**< \brief (Adc Offset: 0x28) Interrupt Disable Register */
  __I uint32_t
      ADC_IMR; /**< \brief (Adc Offset: 0x2C) Interrupt Mask Register */
  __I uint32_t
      ADC_ISR; /**< \brief (Adc Offset: 0x30) Interrupt Status Register */
  __IO uint32_t ADC_LCTMR; /**< \brief (Adc Offset: 0x34) Last Channel Trigger
                              Mode Register */
  __IO uint32_t ADC_LCCWR; /**< \brief (Adc Offset: 0x38) Last Channel Compare
                              Window Register */
  __I uint32_t
      ADC_OVER; /**< \brief (Adc Offset: 0x3C) Overrun Status Register */
  __IO uint32_t
      ADC_EMR; /**< \brief (Adc Offset: 0x40) Extended Mode Register */
  __IO uint32_t
      ADC_CWR; /**< \brief (Adc Offset: 0x44) Compare Window Register */
  __I uint32_t Reserved3[1];
  __IO uint32_t
      ADC_COR; /**< \brief (Adc Offset: 0x4C) Channel Offset Register */
  __I uint32_t
      ADC_CDR[8]; /**< \brief (Adc Offset: 0x50) Channel Data Register */
  __I uint32_t Reserved4[29];
  __IO uint32_t
      ADC_WPMR; /**< \brief (Adc Offset: 0xE4) Write Protection Mode Register */
  __I uint32_t ADC_WPSR; /**< \brief (Adc Offset: 0xE8) Write Protection Status
                            Register */
  __I uint32_t Reserved5[5];
  __IO uint32_t
      ADC_RPR; /**< \brief (Adc Offset: 0x100) Receive Pointer Register */
  __IO uint32_t
      ADC_RCR; /**< \brief (Adc Offset: 0x104) Receive Counter Register */
  __I uint32_t Reserved6[2];
  __IO uint32_t
      ADC_RNPR; /**< \brief (Adc Offset: 0x110) Receive Next Pointer Register */
  __IO uint32_t
      ADC_RNCR; /**< \brief (Adc Offset: 0x114) Receive Next Counter Register */
  __I uint32_t Reserved7[2];
  __O uint32_t
      ADC_PTCR; /**< \brief (Adc Offset: 0x120) Transfer Control Register */
  __I uint32_t
      ADC_PTSR; /**< \brief (Adc Offset: 0x124) Transfer Status Register */
} Adc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- ADC_CR : (ADC Offset: 0x00) Control Register -------- */
#define ADC_CR_SWRST (0x1u << 0) /**< \brief (ADC_CR) Software Reset */
#define ADC_CR_START (0x1u << 1) /**< \brief (ADC_CR) Start Conversion */
#define ADC_CR_AUTOCAL                                                         \
  (0x1u << 3) /**< \brief (ADC_CR) Automatic Calibration of ADC */
#define ADC_CR_CMPRST (0x1u << 4) /**< \brief (ADC_CR) Comparison Restart */
/* -------- ADC_MR : (ADC Offset: 0x04) Mode Register -------- */
#define ADC_MR_TRGEN (0x1u << 0) /**< \brief (ADC_MR) Trigger Enable */
#define ADC_MR_TRGEN_DIS                                                       \
  (0x0u << 0) /**< \brief (ADC_MR) Hardware triggers are disabled. Starting a  \
                 conversion is only possible by software. */
#define ADC_MR_TRGEN_EN                                                        \
  (0x1u << 0) /**< \brief (ADC_MR) Hardware trigger selected by TRGSEL field   \
                 is enabled. */
#define ADC_MR_TRGSEL_Pos 1
#define ADC_MR_TRGSEL_Msk                                                      \
  (0x7u << ADC_MR_TRGSEL_Pos) /**< \brief (ADC_MR) Trigger Selection */
#define ADC_MR_TRGSEL_ADC_TRIG0                                                \
  (0x0u << 1) /**< \brief (ADC_MR) ADTRG External trigger */
#define ADC_MR_TRGSEL_ADC_TRIG1                                                \
  (0x1u                                                                        \
   << 1) /**< \brief (ADC_MR) TIOA0 Output of the Timer Counter Channel 0 */
#define ADC_MR_TRGSEL_ADC_TRIG2                                                \
  (0x2u                                                                        \
   << 1) /**< \brief (ADC_MR) TIOA1 Output of the Timer Counter Channel 1 */
#define ADC_MR_TRGSEL_ADC_TRIG3                                                \
  (0x3u                                                                        \
   << 1) /**< \brief (ADC_MR) TIOA2 Output of the Timer Counter Channel 2 */
#define ADC_MR_TRGSEL_ADC_TRIG4 (0x4u << 1) /**< \brief (ADC_MR) RTCOUT0 */
#define ADC_MR_TRGSEL_ADC_TRIG5 (0x5u << 1) /**< \brief (ADC_MR) RTTINC */
#define ADC_MR_TRGSEL_ADC_TRIG6 (0x6u << 1) /**< \brief (ADC_MR) RTTEVENT */
#define ADC_MR_TRGSEL_ADC_TRIG7 (0x7u << 1) /**< \brief (ADC_MR) - */
#define ADC_MR_SLEEP (0x1u << 5)            /**< \brief (ADC_MR) Sleep Mode */
#define ADC_MR_SLEEP_NORMAL                                                    \
  (0x0u << 5) /**< \brief (ADC_MR) Normal Mode: The ADC core and reference     \
                 voltage circuitry are kept ON between conversions. */
#define ADC_MR_SLEEP_SLEEP                                                     \
  (0x1u << 5) /**< \brief (ADC_MR) Sleep Mode: The wake-up time can be         \
                 modified by programming FWUP bit. */
#define ADC_MR_FWUP (0x1u << 6) /**< \brief (ADC_MR) Fast Wake Up */
#define ADC_MR_FWUP_OFF                                                        \
  (0x0u << 6) /**< \brief (ADC_MR) If SLEEP is 1, then both ADC core and       \
                 reference voltage circuitry are OFF between conversions */
#define ADC_MR_FWUP_ON                                                         \
  (0x1u                                                                        \
   << 6) /**< \brief (ADC_MR) If SLEEP is 1, then Fast Wake-up Sleep mode: The \
            voltage reference is ON between conversions and ADC core is OFF */
#define ADC_MR_FREERUN (0x1u << 7)     /**< \brief (ADC_MR) Free Run Mode */
#define ADC_MR_FREERUN_OFF (0x0u << 7) /**< \brief (ADC_MR) Normal Mode */
#define ADC_MR_FREERUN_ON                                                      \
  (0x1u << 7) /**< \brief (ADC_MR) Free Run Mode: Never wait for any trigger.  \
               */
#define ADC_MR_PRESCAL_Pos 8
#define ADC_MR_PRESCAL_Msk                                                     \
  (0xffu << ADC_MR_PRESCAL_Pos) /**< \brief (ADC_MR) Prescaler Rate Selection  \
                                 */
#define ADC_MR_PRESCAL(value)                                                  \
  ((ADC_MR_PRESCAL_Msk & ((value) << ADC_MR_PRESCAL_Pos)))
#define ADC_MR_STARTUP_Pos 16
#define ADC_MR_STARTUP_Msk                                                     \
  (0xfu << ADC_MR_STARTUP_Pos) /**< \brief (ADC_MR) Start Up Time */
#define ADC_MR_STARTUP_SUT0                                                    \
  (0x0u << 16) /**< \brief (ADC_MR) 0 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT8                                                    \
  (0x1u << 16) /**< \brief (ADC_MR) 8 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT16                                                   \
  (0x2u << 16) /**< \brief (ADC_MR) 16 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT24                                                   \
  (0x3u << 16) /**< \brief (ADC_MR) 24 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT64                                                   \
  (0x4u << 16) /**< \brief (ADC_MR) 64 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT80                                                   \
  (0x5u << 16) /**< \brief (ADC_MR) 80 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT96                                                   \
  (0x6u << 16) /**< \brief (ADC_MR) 96 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT112                                                  \
  (0x7u << 16) /**< \brief (ADC_MR) 112 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT512                                                  \
  (0x8u << 16) /**< \brief (ADC_MR) 512 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT576                                                  \
  (0x9u << 16) /**< \brief (ADC_MR) 576 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT640                                                  \
  (0xAu << 16) /**< \brief (ADC_MR) 640 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT704                                                  \
  (0xBu << 16) /**< \brief (ADC_MR) 704 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT768                                                  \
  (0xCu << 16) /**< \brief (ADC_MR) 768 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT832                                                  \
  (0xDu << 16) /**< \brief (ADC_MR) 832 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT896                                                  \
  (0xEu << 16) /**< \brief (ADC_MR) 896 periods of ADCCLK */
#define ADC_MR_STARTUP_SUT960                                                  \
  (0xFu << 16) /**< \brief (ADC_MR) 960 periods of ADCCLK */
#define ADC_MR_SETTLING_Pos 20
#define ADC_MR_SETTLING_Msk                                                    \
  (0x3u << ADC_MR_SETTLING_Pos) /**< \brief (ADC_MR) Analog Settling Time */
#define ADC_MR_SETTLING_AST3                                                   \
  (0x0u << 20) /**< \brief (ADC_MR) 3 periods of ADCCLK */
#define ADC_MR_SETTLING_AST5                                                   \
  (0x1u << 20) /**< \brief (ADC_MR) 5 periods of ADCCLK */
#define ADC_MR_SETTLING_AST9                                                   \
  (0x2u << 20) /**< \brief (ADC_MR) 9 periods of ADCCLK */
#define ADC_MR_SETTLING_AST17                                                  \
  (0x3u << 20)                    /**< \brief (ADC_MR) 17 periods of ADCCLK */
#define ADC_MR_ANACH (0x1u << 23) /**< \brief (ADC_MR) Analog Change */
#define ADC_MR_ANACH_NONE                                                      \
  (0x0u << 23) /**< \brief (ADC_MR) No analog change on channel switching:     \
                  DIFF0, and OFF0 are used for all channels. */
#define ADC_MR_ANACH_ALLOWED                                                   \
  (0x1u << 23) /**< \brief (ADC_MR) Allows different analog settings for each  \
                  channel. See ADC_COR registers. */
#define ADC_MR_TRACKTIM_Pos 24
#define ADC_MR_TRACKTIM_Msk                                                    \
  (0xfu << ADC_MR_TRACKTIM_Pos) /**< \brief (ADC_MR) Tracking Time */
#define ADC_MR_TRACKTIM(value)                                                 \
  ((ADC_MR_TRACKTIM_Msk & ((value) << ADC_MR_TRACKTIM_Pos)))
#define ADC_MR_TRANSFER_Pos 28
#define ADC_MR_TRANSFER_Msk                                                    \
  (0x3u << ADC_MR_TRANSFER_Pos) /**< \brief (ADC_MR) Transfer Period */
#define ADC_MR_TRANSFER(value)                                                 \
  ((ADC_MR_TRANSFER_Msk & ((value) << ADC_MR_TRANSFER_Pos)))
#define ADC_MR_USEQ (0x1u << 31) /**< \brief (ADC_MR) Use Sequence Enable */
#define ADC_MR_USEQ_NUM_ORDER                                                  \
  (0x0u                                                                        \
   << 31) /**< \brief (ADC_MR) Normal Mode: The controller converts channels   \
             in a simple numeric order depending only on the channel index. */
#define ADC_MR_USEQ_REG_ORDER                                                  \
  (0x1u << 31) /**< \brief (ADC_MR) User Sequence Mode: The sequence respects  \
                  what is defined in ADC_SEQR1 register and can be used to     \
                  convert the same channel several times. */
/* -------- ADC_SEQR1 : (ADC Offset: 0x08) Channel Sequence Register 1 --------
 */
#define ADC_SEQR1_USCH1_Pos 0
#define ADC_SEQR1_USCH1_Msk                                                    \
  (0xfu                                                                        \
   << ADC_SEQR1_USCH1_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 1 */
#define ADC_SEQR1_USCH1(value)                                                 \
  ((ADC_SEQR1_USCH1_Msk & ((value) << ADC_SEQR1_USCH1_Pos)))
#define ADC_SEQR1_USCH2_Pos 4
#define ADC_SEQR1_USCH2_Msk                                                    \
  (0xfu                                                                        \
   << ADC_SEQR1_USCH2_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 2 */
#define ADC_SEQR1_USCH2(value)                                                 \
  ((ADC_SEQR1_USCH2_Msk & ((value) << ADC_SEQR1_USCH2_Pos)))
#define ADC_SEQR1_USCH3_Pos 8
#define ADC_SEQR1_USCH3_Msk                                                    \
  (0xfu                                                                        \
   << ADC_SEQR1_USCH3_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 3 */
#define ADC_SEQR1_USCH3(value)                                                 \
  ((ADC_SEQR1_USCH3_Msk & ((value) << ADC_SEQR1_USCH3_Pos)))
#define ADC_SEQR1_USCH4_Pos 12
#define ADC_SEQR1_USCH4_Msk                                                    \
  (0xfu                                                                        \
   << ADC_SEQR1_USCH4_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 4 */
#define ADC_SEQR1_USCH4(value)                                                 \
  ((ADC_SEQR1_USCH4_Msk & ((value) << ADC_SEQR1_USCH4_Pos)))
#define ADC_SEQR1_USCH5_Pos 16
#define ADC_SEQR1_USCH5_Msk                                                    \
  (0xfu                                                                        \
   << ADC_SEQR1_USCH5_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 5 */
#define ADC_SEQR1_USCH5(value)                                                 \
  ((ADC_SEQR1_USCH5_Msk & ((value) << ADC_SEQR1_USCH5_Pos)))
#define ADC_SEQR1_USCH6_Pos 20
#define ADC_SEQR1_USCH6_Msk                                                    \
  (0xfu                                                                        \
   << ADC_SEQR1_USCH6_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 6 */
#define ADC_SEQR1_USCH6(value)                                                 \
  ((ADC_SEQR1_USCH6_Msk & ((value) << ADC_SEQR1_USCH6_Pos)))
#define ADC_SEQR1_USCH7_Pos 24
#define ADC_SEQR1_USCH7_Msk                                                    \
  (0xfu                                                                        \
   << ADC_SEQR1_USCH7_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 7 */
#define ADC_SEQR1_USCH7(value)                                                 \
  ((ADC_SEQR1_USCH7_Msk & ((value) << ADC_SEQR1_USCH7_Pos)))
/* -------- ADC_CHER : (ADC Offset: 0x10) Channel Enable Register -------- */
#define ADC_CHER_CH0 (0x1u << 0) /**< \brief (ADC_CHER) Channel 0 Enable */
#define ADC_CHER_CH1 (0x1u << 1) /**< \brief (ADC_CHER) Channel 1 Enable */
#define ADC_CHER_CH2 (0x1u << 2) /**< \brief (ADC_CHER) Channel 2 Enable */
#define ADC_CHER_CH3 (0x1u << 3) /**< \brief (ADC_CHER) Channel 3 Enable */
#define ADC_CHER_CH4 (0x1u << 4) /**< \brief (ADC_CHER) Channel 4 Enable */
#define ADC_CHER_CH5 (0x1u << 5) /**< \brief (ADC_CHER) Channel 5 Enable */
#define ADC_CHER_CH6 (0x1u << 6) /**< \brief (ADC_CHER) Channel 6 Enable */
#define ADC_CHER_CH7 (0x1u << 7) /**< \brief (ADC_CHER) Channel 7 Enable */
/* -------- ADC_CHDR : (ADC Offset: 0x14) Channel Disable Register -------- */
#define ADC_CHDR_CH0 (0x1u << 0) /**< \brief (ADC_CHDR) Channel 0 Disable */
#define ADC_CHDR_CH1 (0x1u << 1) /**< \brief (ADC_CHDR) Channel 1 Disable */
#define ADC_CHDR_CH2 (0x1u << 2) /**< \brief (ADC_CHDR) Channel 2 Disable */
#define ADC_CHDR_CH3 (0x1u << 3) /**< \brief (ADC_CHDR) Channel 3 Disable */
#define ADC_CHDR_CH4 (0x1u << 4) /**< \brief (ADC_CHDR) Channel 4 Disable */
#define ADC_CHDR_CH5 (0x1u << 5) /**< \brief (ADC_CHDR) Channel 5 Disable */
#define ADC_CHDR_CH6 (0x1u << 6) /**< \brief (ADC_CHDR) Channel 6 Disable */
#define ADC_CHDR_CH7 (0x1u << 7) /**< \brief (ADC_CHDR) Channel 7 Disable */
/* -------- ADC_CHSR : (ADC Offset: 0x18) Channel Status Register -------- */
#define ADC_CHSR_CH0 (0x1u << 0) /**< \brief (ADC_CHSR) Channel 0 Status */
#define ADC_CHSR_CH1 (0x1u << 1) /**< \brief (ADC_CHSR) Channel 1 Status */
#define ADC_CHSR_CH2 (0x1u << 2) /**< \brief (ADC_CHSR) Channel 2 Status */
#define ADC_CHSR_CH3 (0x1u << 3) /**< \brief (ADC_CHSR) Channel 3 Status */
#define ADC_CHSR_CH4 (0x1u << 4) /**< \brief (ADC_CHSR) Channel 4 Status */
#define ADC_CHSR_CH5 (0x1u << 5) /**< \brief (ADC_CHSR) Channel 5 Status */
#define ADC_CHSR_CH6 (0x1u << 6) /**< \brief (ADC_CHSR) Channel 6 Status */
#define ADC_CHSR_CH7 (0x1u << 7) /**< \brief (ADC_CHSR) Channel 7 Status */
/* -------- ADC_LCDR : (ADC Offset: 0x20) Last Converted Data Register --------
 */
#define ADC_LCDR_LDATA_Pos 0
#define ADC_LCDR_LDATA_Msk                                                     \
  (0xffffu << ADC_LCDR_LDATA_Pos) /**< \brief (ADC_LCDR) Last Data Converted   \
                                   */
#define ADC_LCDR_CHNBOSR_Pos 24
#define ADC_LCDR_CHNBOSR_Msk                                                   \
  (0x1fu << ADC_LCDR_CHNBOSR_Pos) /**< \brief (ADC_LCDR) Channel Number in     \
                                     Oversampling Mode */
/* -------- ADC_IER : (ADC Offset: 0x24) Interrupt Enable Register -------- */
#define ADC_IER_EOC0                                                           \
  (0x1u << 0) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 0 */
#define ADC_IER_EOC1                                                           \
  (0x1u << 1) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 1 */
#define ADC_IER_EOC2                                                           \
  (0x1u << 2) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 2 */
#define ADC_IER_EOC3                                                           \
  (0x1u << 3) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 3 */
#define ADC_IER_EOC4                                                           \
  (0x1u << 4) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 4 */
#define ADC_IER_EOC5                                                           \
  (0x1u << 5) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 5 */
#define ADC_IER_EOC6                                                           \
  (0x1u << 6) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 6 */
#define ADC_IER_EOC7                                                           \
  (0x1u << 7) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 7 */
#define ADC_IER_LCCHG                                                          \
  (0x1u << 19) /**< \brief (ADC_IER) Last Channel Change Interrupt Enable */
#define ADC_IER_EOCAL                                                          \
  (0x1u << 23) /**< \brief (ADC_IER) End of Calibration Sequence */
#define ADC_IER_DRDY                                                           \
  (0x1u << 24) /**< \brief (ADC_IER) Data Ready Interrupt Enable */
#define ADC_IER_GOVRE                                                          \
  (0x1u << 25) /**< \brief (ADC_IER) General Overrun Error Interrupt Enable */
#define ADC_IER_COMPE                                                          \
  (0x1u << 26) /**< \brief (ADC_IER) Comparison Event Interrupt Enable */
#define ADC_IER_ENDRX                                                          \
  (0x1u << 27) /**< \brief (ADC_IER) End of Receive Buffer Interrupt Enable */
#define ADC_IER_RXBUFF                                                         \
  (0x1u << 28) /**< \brief (ADC_IER) Receive Buffer Full Interrupt Enable */
/* -------- ADC_IDR : (ADC Offset: 0x28) Interrupt Disable Register -------- */
#define ADC_IDR_EOC0                                                           \
  (0x1u << 0) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 0 */
#define ADC_IDR_EOC1                                                           \
  (0x1u << 1) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 1 */
#define ADC_IDR_EOC2                                                           \
  (0x1u << 2) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 2 */
#define ADC_IDR_EOC3                                                           \
  (0x1u << 3) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 3 */
#define ADC_IDR_EOC4                                                           \
  (0x1u << 4) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 4 */
#define ADC_IDR_EOC5                                                           \
  (0x1u << 5) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 5 */
#define ADC_IDR_EOC6                                                           \
  (0x1u << 6) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 6 */
#define ADC_IDR_EOC7                                                           \
  (0x1u << 7) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 7 */
#define ADC_IDR_LCCHG                                                          \
  (0x1u << 19) /**< \brief (ADC_IDR) Last Channel Change Interrupt Disable */
#define ADC_IDR_EOCAL                                                          \
  (0x1u << 23) /**< \brief (ADC_IDR) End of Calibration Sequence */
#define ADC_IDR_DRDY                                                           \
  (0x1u << 24) /**< \brief (ADC_IDR) Data Ready Interrupt Disable */
#define ADC_IDR_GOVRE                                                          \
  (0x1u << 25) /**< \brief (ADC_IDR) General Overrun Error Interrupt Disable   \
                */
#define ADC_IDR_COMPE                                                          \
  (0x1u << 26) /**< \brief (ADC_IDR) Comparison Event Interrupt Disable */
#define ADC_IDR_ENDRX                                                          \
  (0x1u << 27) /**< \brief (ADC_IDR) End of Receive Buffer Interrupt Disable   \
                */
#define ADC_IDR_RXBUFF                                                         \
  (0x1u << 28) /**< \brief (ADC_IDR) Receive Buffer Full Interrupt Disable */
/* -------- ADC_IMR : (ADC Offset: 0x2C) Interrupt Mask Register -------- */
#define ADC_IMR_EOC0                                                           \
  (0x1u << 0) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 0 */
#define ADC_IMR_EOC1                                                           \
  (0x1u << 1) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 1 */
#define ADC_IMR_EOC2                                                           \
  (0x1u << 2) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 2 */
#define ADC_IMR_EOC3                                                           \
  (0x1u << 3) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 3 */
#define ADC_IMR_EOC4                                                           \
  (0x1u << 4) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 4 */
#define ADC_IMR_EOC5                                                           \
  (0x1u << 5) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 5 */
#define ADC_IMR_EOC6                                                           \
  (0x1u << 6) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 6 */
#define ADC_IMR_EOC7                                                           \
  (0x1u << 7) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 7 */
#define ADC_IMR_LCCHG                                                          \
  (0x1u << 19) /**< \brief (ADC_IMR) Last Channel Change Interrupt Mask */
#define ADC_IMR_EOCAL                                                          \
  (0x1u << 23) /**< \brief (ADC_IMR) End of Calibration Sequence */
#define ADC_IMR_DRDY                                                           \
  (0x1u << 24) /**< \brief (ADC_IMR) Data Ready Interrupt Mask */
#define ADC_IMR_GOVRE                                                          \
  (0x1u << 25) /**< \brief (ADC_IMR) General Overrun Error Interrupt Mask */
#define ADC_IMR_COMPE                                                          \
  (0x1u << 26) /**< \brief (ADC_IMR) Comparison Event Interrupt Mask */
#define ADC_IMR_ENDRX                                                          \
  (0x1u << 27) /**< \brief (ADC_IMR) End of Receive Buffer Interrupt Mask */
#define ADC_IMR_RXBUFF                                                         \
  (0x1u << 28) /**< \brief (ADC_IMR) Receive Buffer Full Interrupt Mask */
/* -------- ADC_ISR : (ADC Offset: 0x30) Interrupt Status Register -------- */
#define ADC_ISR_EOC0                                                           \
  (0x1u << 0) /**< \brief (ADC_ISR) End of Conversion 0 (automatically set /   \
                 cleared) */
#define ADC_ISR_EOC1                                                           \
  (0x1u << 1) /**< \brief (ADC_ISR) End of Conversion 1 (automatically set /   \
                 cleared) */
#define ADC_ISR_EOC2                                                           \
  (0x1u << 2) /**< \brief (ADC_ISR) End of Conversion 2 (automatically set /   \
                 cleared) */
#define ADC_ISR_EOC3                                                           \
  (0x1u << 3) /**< \brief (ADC_ISR) End of Conversion 3 (automatically set /   \
                 cleared) */
#define ADC_ISR_EOC4                                                           \
  (0x1u << 4) /**< \brief (ADC_ISR) End of Conversion 4 (automatically set /   \
                 cleared) */
#define ADC_ISR_EOC5                                                           \
  (0x1u << 5) /**< \brief (ADC_ISR) End of Conversion 5 (automatically set /   \
                 cleared) */
#define ADC_ISR_EOC6                                                           \
  (0x1u << 6) /**< \brief (ADC_ISR) End of Conversion 6 (automatically set /   \
                 cleared) */
#define ADC_ISR_EOC7                                                           \
  (0x1u << 7) /**< \brief (ADC_ISR) End of Conversion 7 (automatically set /   \
                 cleared) */
#define ADC_ISR_LCCHG                                                          \
  (0x1u << 19) /**< \brief (ADC_ISR) Last Channel Change (cleared on read) */
#define ADC_ISR_EOCAL                                                          \
  (0x1u << 23) /**< \brief (ADC_ISR) End of Calibration Sequence */
#define ADC_ISR_DRDY                                                           \
  (0x1u << 24) /**< \brief (ADC_ISR) Data Ready (automatically set / cleared)  \
                */
#define ADC_ISR_GOVRE                                                          \
  (0x1u << 25) /**< \brief (ADC_ISR) General Overrun Error (cleared on read)   \
                */
#define ADC_ISR_COMPE                                                          \
  (0x1u << 26) /**< \brief (ADC_ISR) Comparison Event (cleared on read) */
#define ADC_ISR_ENDRX                                                          \
  (0x1u << 27) /**< \brief (ADC_ISR) End of Receiver Transfer (automatically   \
                  set / cleared) */
#define ADC_ISR_RXBUFF                                                         \
  (0x1u << 28) /**< \brief (ADC_ISR) Reception Buffer Full (automatically set  \
                  / cleared) */
/* -------- ADC_LCTMR : (ADC Offset: 0x34) Last Channel Trigger Mode Register
 * -------- */
#define ADC_LCTMR_DUALTRIG                                                     \
  (0x1u << 0) /**< \brief (ADC_LCTMR) Dual Trigger ON */
#define ADC_LCTMR_CMPMOD_Pos 4
#define ADC_LCTMR_CMPMOD_Msk                                                   \
  (0x3u << ADC_LCTMR_CMPMOD_Pos) /**< \brief (ADC_LCTMR) Last Channel          \
                                    Comparison Mode */
#define ADC_LCTMR_CMPMOD_LOW                                                   \
  (0x0u << 4) /**< \brief (ADC_LCTMR) Generates an event when the converted    \
                 data is lower than the low threshold of the window. */
#define ADC_LCTMR_CMPMOD_HIGH                                                  \
  (0x1u << 4) /**< \brief (ADC_LCTMR) Generates an event when the converted    \
                 data is higher than the high threshold of the window. */
#define ADC_LCTMR_CMPMOD_IN                                                    \
  (0x2u << 4) /**< \brief (ADC_LCTMR) Generates an event when the converted    \
                 data is in the comparison window. */
#define ADC_LCTMR_CMPMOD_OUT                                                   \
  (0x3u << 4) /**< \brief (ADC_LCTMR) Generates an event when the converted    \
                 data is out of the comparison window. */
/* -------- ADC_LCCWR : (ADC Offset: 0x38) Last Channel Compare Window Register
 * -------- */
#define ADC_LCCWR_LOWTHRES_Pos 0
#define ADC_LCCWR_LOWTHRES_Msk                                                 \
  (0xfffu << ADC_LCCWR_LOWTHRES_Pos) /**< \brief (ADC_LCCWR) Low Threshold */
#define ADC_LCCWR_LOWTHRES(value)                                              \
  ((ADC_LCCWR_LOWTHRES_Msk & ((value) << ADC_LCCWR_LOWTHRES_Pos)))
#define ADC_LCCWR_HIGHTHRES_Pos 16
#define ADC_LCCWR_HIGHTHRES_Msk                                                \
  (0xfffu << ADC_LCCWR_HIGHTHRES_Pos) /**< \brief (ADC_LCCWR) High Threshold   \
                                       */
#define ADC_LCCWR_HIGHTHRES(value)                                             \
  ((ADC_LCCWR_HIGHTHRES_Msk & ((value) << ADC_LCCWR_HIGHTHRES_Pos)))
/* -------- ADC_OVER : (ADC Offset: 0x3C) Overrun Status Register -------- */
#define ADC_OVER_OVRE0 (0x1u << 0) /**< \brief (ADC_OVER) Overrun Error 0 */
#define ADC_OVER_OVRE1 (0x1u << 1) /**< \brief (ADC_OVER) Overrun Error 1 */
#define ADC_OVER_OVRE2 (0x1u << 2) /**< \brief (ADC_OVER) Overrun Error 2 */
#define ADC_OVER_OVRE3 (0x1u << 3) /**< \brief (ADC_OVER) Overrun Error 3 */
#define ADC_OVER_OVRE4 (0x1u << 4) /**< \brief (ADC_OVER) Overrun Error 4 */
#define ADC_OVER_OVRE5 (0x1u << 5) /**< \brief (ADC_OVER) Overrun Error 5 */
#define ADC_OVER_OVRE6 (0x1u << 6) /**< \brief (ADC_OVER) Overrun Error 6 */
#define ADC_OVER_OVRE7 (0x1u << 7) /**< \brief (ADC_OVER) Overrun Error 7 */
/* -------- ADC_EMR : (ADC Offset: 0x40) Extended Mode Register -------- */
#define ADC_EMR_CMPMODE_Pos 0
#define ADC_EMR_CMPMODE_Msk                                                    \
  (0x3u << ADC_EMR_CMPMODE_Pos) /**< \brief (ADC_EMR) Comparison Mode */
#define ADC_EMR_CMPMODE_LOW                                                    \
  (0x0u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data \
                 is lower than the low threshold of the window. */
#define ADC_EMR_CMPMODE_HIGH                                                   \
  (0x1u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data \
                 is higher than the high threshold of the window. */
#define ADC_EMR_CMPMODE_IN                                                     \
  (0x2u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data \
                 is in the comparison window. */
#define ADC_EMR_CMPMODE_OUT                                                    \
  (0x3u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data \
                 is out of the comparison window. */
#define ADC_EMR_CMPTYPE (0x1u << 2) /**< \brief (ADC_EMR) Comparison Type */
#define ADC_EMR_CMPTYPE_FLAG_ONLY                                              \
  (0x0u << 2) /**< \brief (ADC_EMR) Any conversion is performed and comparison \
                 function drives the COMPE flag. */
#define ADC_EMR_CMPTYPE_START_CONDITION                                        \
  (0x1u                                                                        \
   << 2) /**< \brief (ADC_EMR) Comparison conditions must be met to start the  \
            storage of all conversions until the CMPRST bit is set. */
#define ADC_EMR_CMPSEL_Pos 4
#define ADC_EMR_CMPSEL_Msk                                                     \
  (0xfu                                                                        \
   << ADC_EMR_CMPSEL_Pos) /**< \brief (ADC_EMR) Comparison Selected Channel */
#define ADC_EMR_CMPSEL(value)                                                  \
  ((ADC_EMR_CMPSEL_Msk & ((value) << ADC_EMR_CMPSEL_Pos)))
#define ADC_EMR_CMPALL (0x1u << 9) /**< \brief (ADC_EMR) Compare All Channels  \
                                    */
#define ADC_EMR_CMPFILTER_Pos 12
#define ADC_EMR_CMPFILTER_Msk                                                  \
  (0x3u                                                                        \
   << ADC_EMR_CMPFILTER_Pos) /**< \brief (ADC_EMR) Compare Event Filtering */
#define ADC_EMR_CMPFILTER(value)                                               \
  ((ADC_EMR_CMPFILTER_Msk & ((value) << ADC_EMR_CMPFILTER_Pos)))
#define ADC_EMR_OSR_Pos 16
#define ADC_EMR_OSR_Msk                                                        \
  (0x7u << ADC_EMR_OSR_Pos) /**< \brief (ADC_EMR) Over Sampling Rate */
#define ADC_EMR_OSR_NO_AVERAGE                                                 \
  (0x0u                                                                        \
   << 16) /**< \brief (ADC_EMR) No averaging. ADC sample rate is maximum. */
#define ADC_EMR_OSR_OSR4                                                       \
  (0x1u << 16) /**< \brief (ADC_EMR) 1-bit enhanced resolution by averaging.   \
                  ADC sample rate divided by 4. */
#define ADC_EMR_OSR_OSR16                                                      \
  (0x2u << 16) /**< \brief (ADC_EMR) 2-bit enhanced resolution by averaging.   \
                  ADC sample rate divided by 16. */
#define ADC_EMR_OSR_OSR64                                                      \
  (0x3u << 16) /**< \brief (ADC_EMR) 3-bit enhanced resolution by averaging.   \
                  ADC sample rate divided by 64. */
#define ADC_EMR_OSR_OSR256                                                     \
  (0x4u << 16) /**< \brief (ADC_EMR) 4-bit enhanced resolution by averaging.   \
                  ADC sample rate divided by 256. */
#define ADC_EMR_ASTE                                                           \
  (0x1u << 20) /**< \brief (ADC_EMR) Averaging on Single Trigger Event */
#define ADC_EMR_ASTE_MULTI_TRIG_AVERAGE                                        \
  (0x0u << 20) /**< \brief (ADC_EMR) The average requests several trigger      \
                  events. */
#define ADC_EMR_ASTE_SINGLE_TRIG_AVERAGE                                       \
  (0x1u << 20) /**< \brief (ADC_EMR) The average requests only one trigger     \
                  event. */
#define ADC_EMR_SRCCLK                                                         \
  (0x1u << 21) /**< \brief (ADC_EMR) External Clock Selection */
#define ADC_EMR_SRCCLK_PERIPH_CLK                                              \
  (0x0u << 21) /**< \brief (ADC_EMR) The peripheral clock is the source for    \
                  the ADC prescaler. */
#define ADC_EMR_SRCCLK_PMC_PCK                                                 \
  (0x1u << 21) /**< \brief (ADC_EMR) PMC PCKx is the source clock for the ADC  \
                  prescaler, thus the ADC clock can be independent of the      \
                  core/peripheral clock. */
#define ADC_EMR_TAG (0x1u << 24) /**< \brief (ADC_EMR) Tag of the ADC_LCDR */
/* -------- ADC_CWR : (ADC Offset: 0x44) Compare Window Register -------- */
#define ADC_CWR_LOWTHRES_Pos 0
#define ADC_CWR_LOWTHRES_Msk                                                   \
  (0xffffu << ADC_CWR_LOWTHRES_Pos) /**< \brief (ADC_CWR) Low Threshold */
#define ADC_CWR_LOWTHRES(value)                                                \
  ((ADC_CWR_LOWTHRES_Msk & ((value) << ADC_CWR_LOWTHRES_Pos)))
#define ADC_CWR_HIGHTHRES_Pos 16
#define ADC_CWR_HIGHTHRES_Msk                                                  \
  (0xffffu << ADC_CWR_HIGHTHRES_Pos) /**< \brief (ADC_CWR) High Threshold */
#define ADC_CWR_HIGHTHRES(value)                                               \
  ((ADC_CWR_HIGHTHRES_Msk & ((value) << ADC_CWR_HIGHTHRES_Pos)))
/* -------- ADC_COR : (ADC Offset: 0x4C) Channel Offset Register -------- */
#define ADC_COR_OFF0 (0x1u << 0) /**< \brief (ADC_COR) Offset for Channel 0 */
#define ADC_COR_OFF1 (0x1u << 1) /**< \brief (ADC_COR) Offset for Channel 1 */
#define ADC_COR_OFF2 (0x1u << 2) /**< \brief (ADC_COR) Offset for Channel 2 */
#define ADC_COR_OFF3 (0x1u << 3) /**< \brief (ADC_COR) Offset for Channel 3 */
#define ADC_COR_OFF4 (0x1u << 4) /**< \brief (ADC_COR) Offset for Channel 4 */
#define ADC_COR_OFF5 (0x1u << 5) /**< \brief (ADC_COR) Offset for Channel 5 */
#define ADC_COR_OFF6 (0x1u << 6) /**< \brief (ADC_COR) Offset for Channel 6 */
#define ADC_COR_OFF7 (0x1u << 7) /**< \brief (ADC_COR) Offset for Channel 7 */
#define ADC_COR_DIFF0                                                          \
  (0x1u << 16) /**< \brief (ADC_COR) Differential Inputs for Channel 0 */
#define ADC_COR_DIFF1                                                          \
  (0x1u << 17) /**< \brief (ADC_COR) Differential Inputs for Channel 1 */
#define ADC_COR_DIFF2                                                          \
  (0x1u << 18) /**< \brief (ADC_COR) Differential Inputs for Channel 2 */
#define ADC_COR_DIFF3                                                          \
  (0x1u << 19) /**< \brief (ADC_COR) Differential Inputs for Channel 3 */
#define ADC_COR_DIFF4                                                          \
  (0x1u << 20) /**< \brief (ADC_COR) Differential Inputs for Channel 4 */
#define ADC_COR_DIFF5                                                          \
  (0x1u << 21) /**< \brief (ADC_COR) Differential Inputs for Channel 5 */
#define ADC_COR_DIFF6                                                          \
  (0x1u << 22) /**< \brief (ADC_COR) Differential Inputs for Channel 6 */
#define ADC_COR_DIFF7                                                          \
  (0x1u << 23) /**< \brief (ADC_COR) Differential Inputs for Channel 7 */
/* -------- ADC_CDR[8] : (ADC Offset: 0x50) Channel Data Register -------- */
#define ADC_CDR_DATA_Pos 0
#define ADC_CDR_DATA_Msk                                                       \
  (0xffffu << ADC_CDR_DATA_Pos) /**< \brief (ADC_CDR[8]) Converted Data */
/* -------- ADC_WPMR : (ADC Offset: 0xE4) Write Protection Mode Register
 * -------- */
#define ADC_WPMR_WPEN                                                          \
  (0x1u << 0) /**< \brief (ADC_WPMR) Write Protection Enable */
#define ADC_WPMR_WPKEY_Pos 8
#define ADC_WPMR_WPKEY_Msk                                                     \
  (0xffffffu                                                                   \
   << ADC_WPMR_WPKEY_Pos) /**< \brief (ADC_WPMR) Write Protection Key */
#define ADC_WPMR_WPKEY_PASSWD                                                  \
  (0x414443u                                                                   \
   << 8) /**< \brief (ADC_WPMR) Writing any other value in this field aborts   \
            the write operation of the WPEN bit.Always reads as 0 */
/* -------- ADC_WPSR : (ADC Offset: 0xE8) Write Protection Status Register
 * -------- */
#define ADC_WPSR_WPVS                                                          \
  (0x1u << 0) /**< \brief (ADC_WPSR) Write Protection Violation Status */
#define ADC_WPSR_WPVSRC_Pos 8
#define ADC_WPSR_WPVSRC_Msk                                                    \
  (0xffffu << ADC_WPSR_WPVSRC_Pos) /**< \brief (ADC_WPSR) Write Protection     \
                                      Violation Source */
/* -------- ADC_RPR : (ADC Offset: 0x100) Receive Pointer Register -------- */
#define ADC_RPR_RXPTR_Pos 0
#define ADC_RPR_RXPTR_Msk                                                      \
  (0xffffffffu                                                                 \
   << ADC_RPR_RXPTR_Pos) /**< \brief (ADC_RPR) Receive Pointer Register */
#define ADC_RPR_RXPTR(value)                                                   \
  ((ADC_RPR_RXPTR_Msk & ((value) << ADC_RPR_RXPTR_Pos)))
/* -------- ADC_RCR : (ADC Offset: 0x104) Receive Counter Register -------- */
#define ADC_RCR_RXCTR_Pos 0
#define ADC_RCR_RXCTR_Msk                                                      \
  (0xffffu                                                                     \
   << ADC_RCR_RXCTR_Pos) /**< \brief (ADC_RCR) Receive Counter Register */
#define ADC_RCR_RXCTR(value)                                                   \
  ((ADC_RCR_RXCTR_Msk & ((value) << ADC_RCR_RXCTR_Pos)))
/* -------- ADC_RNPR : (ADC Offset: 0x110) Receive Next Pointer Register
 * -------- */
#define ADC_RNPR_RXNPTR_Pos 0
#define ADC_RNPR_RXNPTR_Msk                                                    \
  (0xffffffffu                                                                 \
   << ADC_RNPR_RXNPTR_Pos) /**< \brief (ADC_RNPR) Receive Next Pointer */
#define ADC_RNPR_RXNPTR(value)                                                 \
  ((ADC_RNPR_RXNPTR_Msk & ((value) << ADC_RNPR_RXNPTR_Pos)))
/* -------- ADC_RNCR : (ADC Offset: 0x114) Receive Next Counter Register
 * -------- */
#define ADC_RNCR_RXNCTR_Pos 0
#define ADC_RNCR_RXNCTR_Msk                                                    \
  (0xffffu                                                                     \
   << ADC_RNCR_RXNCTR_Pos) /**< \brief (ADC_RNCR) Receive Next Counter */
#define ADC_RNCR_RXNCTR(value)                                                 \
  ((ADC_RNCR_RXNCTR_Msk & ((value) << ADC_RNCR_RXNCTR_Pos)))
/* -------- ADC_PTCR : (ADC Offset: 0x120) Transfer Control Register -------- */
#define ADC_PTCR_RXTEN                                                         \
  (0x1u << 0) /**< \brief (ADC_PTCR) Receiver Transfer Enable */
#define ADC_PTCR_RXTDIS                                                        \
  (0x1u << 1) /**< \brief (ADC_PTCR) Receiver Transfer Disable */
#define ADC_PTCR_TXTEN                                                         \
  (0x1u << 8) /**< \brief (ADC_PTCR) Transmitter Transfer Enable */
#define ADC_PTCR_TXTDIS                                                        \
  (0x1u << 9) /**< \brief (ADC_PTCR) Transmitter Transfer Disable */
#define ADC_PTCR_RXCBEN                                                        \
  (0x1u << 16) /**< \brief (ADC_PTCR) Receiver Circular Buffer Enable */
#define ADC_PTCR_RXCBDIS                                                       \
  (0x1u << 17) /**< \brief (ADC_PTCR) Receiver Circular Buffer Disable */
#define ADC_PTCR_TXCBEN                                                        \
  (0x1u << 18) /**< \brief (ADC_PTCR) Transmitter Circular Buffer Enable */
#define ADC_PTCR_TXCBDIS                                                       \
  (0x1u << 19) /**< \brief (ADC_PTCR) Transmitter Circular Buffer Disable */
#define ADC_PTCR_ERRCLR                                                        \
  (0x1u << 24) /**< \brief (ADC_PTCR) Transfer Bus Error Clear */
/* -------- ADC_PTSR : (ADC Offset: 0x124) Transfer Status Register -------- */
#define ADC_PTSR_RXTEN                                                         \
  (0x1u << 0) /**< \brief (ADC_PTSR) Receiver Transfer Enable */
#define ADC_PTSR_TXTEN                                                         \
  (0x1u << 8) /**< \brief (ADC_PTSR) Transmitter Transfer Enable */
#define ADC_PTSR_RXCBEN                                                        \
  (0x1u << 16) /**< \brief (ADC_PTSR) Receiver Transfer Enable */
#define ADC_PTSR_TXCBEN                                                        \
  (0x1u << 18) /**< \brief (ADC_PTSR) Transmitter Transfer Enable */
#define ADC_PTSR_ERR                                                           \
  (0x1u << 24) /**< \brief (ADC_PTSR) Transfer Bus Error (clear on read) */

/*@}*/

#endif /* _SAMG55_ADC_COMPONENT_ */
