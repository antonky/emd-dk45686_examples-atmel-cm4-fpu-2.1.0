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

#ifndef _SAMG55_USART_COMPONENT_
#define _SAMG55_USART_COMPONENT_

/* =============================================================================
 */
/**  SOFTWARE API DEFINITION FOR Universal Synchronous Asynchronous Receiver
 * Transmitter */
/* =============================================================================
 */
/** \addtogroup SAMG55_USART Universal Synchronous Asynchronous Receiver
 * Transmitter */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Usart hardware registers */
typedef struct {
  __O uint32_t
      US_CR; /**< \brief (Usart Offset: 0x000) USART Control Register */
  __IO uint32_t US_MR; /**< \brief (Usart Offset: 0x004) USART Mode Register */
  __O uint32_t US_IER; /**< \brief (Usart Offset: 0x008) USART Interrupt Enable
                          Register */
  __O uint32_t US_IDR; /**< \brief (Usart Offset: 0x00C) USART Interrupt Disable
                          Register */
  __I uint32_t
      US_IMR; /**< \brief (Usart Offset: 0x010) USART Interrupt Mask Register */
  __I uint32_t
      US_CSR; /**< \brief (Usart Offset: 0x014) USART Channel Status Register */
  __I uint32_t US_RHR; /**< \brief (Usart Offset: 0x018) USART Receive Holding
                          Register */
  __O uint32_t US_THR; /**< \brief (Usart Offset: 0x01C) USART Transmit Holding
                          Register */
  __IO uint32_t US_BRGR; /**< \brief (Usart Offset: 0x020) USART Baud Rate
                            Generator Register */
  __IO uint32_t US_RTOR; /**< \brief (Usart Offset: 0x024) USART Receiver
                            Time-out Register */
  __IO uint32_t US_TTGR; /**< \brief (Usart Offset: 0x028) USART Transmitter
                            Timeguard Register */
  __I uint32_t Reserved1[5];
  __IO uint32_t
      US_FIDI; /**< \brief (Usart Offset: 0x040) USART FI DI Ratio Register */
  __I uint32_t US_NER; /**< \brief (Usart Offset: 0x044) USART Number of Errors
                          Register */
  __I uint32_t Reserved2[3];
  __IO uint32_t
      US_LINMR; /**< \brief (Usart Offset: 0x054) USART LIN Mode Register */
  __IO uint32_t US_LINIR; /**< \brief (Usart Offset: 0x058) USART LIN Identifier
                             Register */
  __I uint32_t US_LINBRR; /**< \brief (Usart Offset: 0x05C) USART LIN Baud Rate
                             Register */
  __I uint32_t Reserved3[12];
  __IO uint32_t
      US_CMPR; /**< \brief (Usart Offset: 0x090) USART Comparison Register */
  __I uint32_t Reserved4[20];
  __IO uint32_t US_WPMR; /**< \brief (Usart Offset: 0x0E4) USART Write
                            Protection Mode Register */
  __I uint32_t US_WPSR; /**< \brief (Usart Offset: 0x0E8) USART Write Protection
                           Status Register */
  __I uint32_t Reserved5[5];
  __IO uint32_t
      US_RPR; /**< \brief (Usart Offset: 0x100) Receive Pointer Register */
  __IO uint32_t
      US_RCR; /**< \brief (Usart Offset: 0x104) Receive Counter Register */
  __IO uint32_t
      US_TPR; /**< \brief (Usart Offset: 0x108) Transmit Pointer Register */
  __IO uint32_t
      US_TCR; /**< \brief (Usart Offset: 0x10C) Transmit Counter Register */
  __IO uint32_t US_RNPR; /**< \brief (Usart Offset: 0x110) Receive Next Pointer
                            Register */
  __IO uint32_t US_RNCR; /**< \brief (Usart Offset: 0x114) Receive Next Counter
                            Register */
  __IO uint32_t US_TNPR; /**< \brief (Usart Offset: 0x118) Transmit Next Pointer
                            Register */
  __IO uint32_t US_TNCR; /**< \brief (Usart Offset: 0x11C) Transmit Next Counter
                            Register */
  __O uint32_t
      US_PTCR; /**< \brief (Usart Offset: 0x120) Transfer Control Register */
  __I uint32_t
      US_PTSR; /**< \brief (Usart Offset: 0x124) Transfer Status Register */
} Usart;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- US_CR : (USART Offset: 0x000) USART Control Register -------- */
#define US_CR_RSTRX (0x1u << 2)    /**< \brief (US_CR) Reset Receiver */
#define US_CR_RSTTX (0x1u << 3)    /**< \brief (US_CR) Reset Transmitter */
#define US_CR_RXEN (0x1u << 4)     /**< \brief (US_CR) Receiver Enable */
#define US_CR_RXDIS (0x1u << 5)    /**< \brief (US_CR) Receiver Disable */
#define US_CR_TXEN (0x1u << 6)     /**< \brief (US_CR) Transmitter Enable */
#define US_CR_TXDIS (0x1u << 7)    /**< \brief (US_CR) Transmitter Disable */
#define US_CR_RSTSTA (0x1u << 8)   /**< \brief (US_CR) Reset Status Bits */
#define US_CR_STTBRK (0x1u << 9)   /**< \brief (US_CR) Start Break */
#define US_CR_STPBRK (0x1u << 10)  /**< \brief (US_CR) Stop Break */
#define US_CR_STTTO (0x1u << 11)   /**< \brief (US_CR) Start Time-out */
#define US_CR_SENDA (0x1u << 12)   /**< \brief (US_CR) Send Address */
#define US_CR_RSTIT (0x1u << 13)   /**< \brief (US_CR) Reset Iterations */
#define US_CR_RSTNACK (0x1u << 14) /**< \brief (US_CR) Reset Non Acknowledge   \
                                    */
#define US_CR_RETTO (0x1u << 15)   /**< \brief (US_CR) Rearm Time-out */
#define US_CR_RTSEN (0x1u << 18)   /**< \brief (US_CR) Request to Send Enable */
#define US_CR_RTSDIS (0x1u << 19)  /**< \brief (US_CR) Request to Send Disable \
                                    */
#define US_CR_LINABT (0x1u << 20)  /**< \brief (US_CR) Abort LIN Transmission  \
                                    */
#define US_CR_LINWKUP (0x1u << 21) /**< \brief (US_CR) Send LIN Wakeup Signal  \
                                    */
#define US_CR_REQCLR                                                           \
  (0x1u << 28) /**< \brief (US_CR) Request to Clear the Comparison Trigger */
#define US_CR_FCS (0x1u << 18) /**< \brief (US_CR) Force SPI Chip Select */
#define US_CR_RCS (0x1u << 19) /**< \brief (US_CR) Release SPI Chip Select */
/* -------- US_MR : (USART Offset: 0x004) USART Mode Register -------- */
#define US_MR_USART_MODE_Pos 0
#define US_MR_USART_MODE_Msk                                                   \
  (0xfu << US_MR_USART_MODE_Pos) /**< \brief (US_MR) USART Mode of Operation   \
                                  */
#define US_MR_USART_MODE_NORMAL (0x0u << 0) /**< \brief (US_MR) Normal mode */
#define US_MR_USART_MODE_RS485 (0x1u << 0)  /**< \brief (US_MR) RS485 mode */
#define US_MR_USART_MODE_HW_HANDSHAKING                                        \
  (0x2u << 0) /**< \brief (US_MR) Hardware Handshaking */
#define US_MR_USART_MODE_IS07816_T_0                                           \
  (0x4u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 0 */
#define US_MR_USART_MODE_IS07816_T_1                                           \
  (0x6u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 1 */
#define US_MR_USART_MODE_LIN_MASTER                                            \
  (0xAu << 0) /**< \brief (US_MR) LIN master mode */
#define US_MR_USART_MODE_LIN_SLAVE                                             \
  (0xBu << 0) /**< \brief (US_MR) LIN Slave mode */
#define US_MR_USART_MODE_SPI_MASTER                                            \
  (0xEu << 0) /**< \brief (US_MR) SPI master mode */
#define US_MR_USART_MODE_SPI_SLAVE                                             \
  (0xFu << 0) /**< \brief (US_MR) SPI Slave mode */
#define US_MR_USCLKS_Pos 4
#define US_MR_USCLKS_Msk                                                       \
  (0x3u << US_MR_USCLKS_Pos) /**< \brief (US_MR) Clock Selection */
#define US_MR_USCLKS_MCK                                                       \
  (0x0u << 4) /**< \brief (US_MR) Peripheral clock is selected */
#define US_MR_USCLKS_DIV                                                       \
  (0x1u                                                                        \
   << 4) /**< \brief (US_MR) Peripheral clock Divided (DIV=8) is selected */
#define US_MR_USCLKS_PMC_PCK                                                   \
  (0x2u << 4) /**< \brief (US_MR) PMC programmable clock (PCK) is selected.If  \
                 the SCK pin is driven (CLKO=1), the CD field must be greater  \
                 than 1. */
#define US_MR_USCLKS_SCK                                                       \
  (0x3u << 4) /**< \brief (US_MR) External pin (SCK) is selected */
#define US_MR_CHRL_Pos 6
#define US_MR_CHRL_Msk                                                         \
  (0x3u << US_MR_CHRL_Pos) /**< \brief (US_MR) Character Length */
#define US_MR_CHRL_5_BIT                                                       \
  (0x0u << 6) /**< \brief (US_MR) Character length is 5 bits */
#define US_MR_CHRL_6_BIT                                                       \
  (0x1u << 6) /**< \brief (US_MR) Character length is 6 bits */
#define US_MR_CHRL_7_BIT                                                       \
  (0x2u << 6) /**< \brief (US_MR) Character length is 7 bits */
#define US_MR_CHRL_8_BIT                                                       \
  (0x3u << 6)                  /**< \brief (US_MR) Character length is 8 bits */
#define US_MR_SYNC (0x1u << 8) /**< \brief (US_MR) Synchronous Mode Select */
#define US_MR_PAR_Pos 9
#define US_MR_PAR_Msk (0x7u << US_MR_PAR_Pos) /**< \brief (US_MR) Parity Type  \
                                               */
#define US_MR_PAR_EVEN (0x0u << 9)            /**< \brief (US_MR) Even parity */
#define US_MR_PAR_ODD (0x1u << 9)             /**< \brief (US_MR) Odd parity */
#define US_MR_PAR_SPACE                                                        \
  (0x2u << 9) /**< \brief (US_MR) Parity forced to 0 (Space) */
#define US_MR_PAR_MARK                                                         \
  (0x3u << 9) /**< \brief (US_MR) Parity forced to 1 (Mark) */
#define US_MR_PAR_NO (0x4u << 9)        /**< \brief (US_MR) No parity */
#define US_MR_PAR_MULTIDROP (0x6u << 9) /**< \brief (US_MR) Multidrop mode */
#define US_MR_NBSTOP_Pos 12
#define US_MR_NBSTOP_Msk                                                       \
  (0x3u << US_MR_NBSTOP_Pos) /**< \brief (US_MR) Number of Stop Bits */
#define US_MR_NBSTOP_1_BIT (0x0u << 12) /**< \brief (US_MR) 1 stop bit */
#define US_MR_NBSTOP_1_5_BIT                                                   \
  (0x1u << 12) /**< \brief (US_MR) 1.5 stop bits (SYNC = 0) or reserved (SYNC  \
                  = 1) */
#define US_MR_NBSTOP_2_BIT (0x2u << 12) /**< \brief (US_MR) 2 stop bits */
#define US_MR_CHMODE_Pos 14
#define US_MR_CHMODE_Msk                                                       \
  (0x3u << US_MR_CHMODE_Pos)             /**< \brief (US_MR) Channel Mode */
#define US_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (US_MR) Normal mode */
#define US_MR_CHMODE_AUTOMATIC                                                 \
  (0x1u << 14) /**< \brief (US_MR) Automatic Echo. Receiver input is connected \
                  to the TXD pin. */
#define US_MR_CHMODE_LOCAL_LOOPBACK                                            \
  (0x2u << 14) /**< \brief (US_MR) Local Loopback. Transmitter output is       \
                  connected to the Receiver Input. */
#define US_MR_CHMODE_REMOTE_LOOPBACK                                           \
  (0x3u << 14) /**< \brief (US_MR) Remote Loopback. RXD pin is internally      \
                  connected to the TXD pin. */
#define US_MR_MSBF (0x1u << 16)    /**< \brief (US_MR) Bit Order */
#define US_MR_MODE9 (0x1u << 17)   /**< \brief (US_MR) 9-bit Character Length */
#define US_MR_CLKO (0x1u << 18)    /**< \brief (US_MR) Clock Output Select */
#define US_MR_OVER (0x1u << 19)    /**< \brief (US_MR) Oversampling Mode */
#define US_MR_INACK (0x1u << 20)   /**< \brief (US_MR) Inhibit Non Acknowledge \
                                    */
#define US_MR_DSNACK (0x1u << 21)  /**< \brief (US_MR) Disable Successive NACK \
                                    */
#define US_MR_INVDATA (0x1u << 23) /**< \brief (US_MR) Inverted Data */
#define US_MR_MAX_ITERATION_Pos 24
#define US_MR_MAX_ITERATION_Msk                                                \
  (0x7u << US_MR_MAX_ITERATION_Pos) /**< \brief (US_MR) Maximum Number of      \
                                       Automatic Iteration */
#define US_MR_MAX_ITERATION(value)                                             \
  ((US_MR_MAX_ITERATION_Msk & ((value) << US_MR_MAX_ITERATION_Pos)))
#define US_MR_FILTER (0x1u << 28) /**< \brief (US_MR) Receive Line Filter */
#define US_MR_CPHA (0x1u << 8)    /**< \brief (US_MR) SPI Clock Phase */
#define US_MR_CPOL (0x1u << 16)   /**< \brief (US_MR) SPI Clock Polarity */
#define US_MR_WRDBT                                                            \
  (0x1u << 20) /**< \brief (US_MR) Wait Read Data Before Transfer */
/* -------- US_IER : (USART Offset: 0x008) USART Interrupt Enable Register
 * -------- */
#define US_IER_RXRDY (0x1u << 0) /**< \brief (US_IER) RXRDY Interrupt Enable   \
                                  */
#define US_IER_TXRDY (0x1u << 1) /**< \brief (US_IER) TXRDY Interrupt Enable   \
                                  */
#define US_IER_RXBRK                                                           \
  (0x1u << 2) /**< \brief (US_IER) Receiver Break Interrupt Enable */
#define US_IER_ENDRX                                                           \
  (0x1u << 3) /**< \brief (US_IER) End of Receive Buffer Interrupt Enable      \
                 (available in all USART modes of operation) */
#define US_IER_ENDTX                                                           \
  (0x1u << 4) /**< \brief (US_IER) End of Transmit Buffer Interrupt Enable     \
                 (available in all USART modes of operation) */
#define US_IER_OVRE                                                            \
  (0x1u << 5) /**< \brief (US_IER) Overrun Error Interrupt Enable */
#define US_IER_FRAME                                                           \
  (0x1u << 6) /**< \brief (US_IER) Framing Error Interrupt Enable */
#define US_IER_PARE                                                            \
  (0x1u << 7) /**< \brief (US_IER) Parity Error Interrupt Enable */
#define US_IER_TIMEOUT                                                         \
  (0x1u << 8) /**< \brief (US_IER) Time-out Interrupt Enable */
#define US_IER_TXEMPTY                                                         \
  (0x1u << 9) /**< \brief (US_IER) TXEMPTY Interrupt Enable */
#define US_IER_ITER                                                            \
  (0x1u << 10) /**< \brief (US_IER) Max number of Repetitions Reached          \
                  Interrupt Enable */
#define US_IER_TXBUFE                                                          \
  (0x1u << 11) /**< \brief (US_IER) Transmit Buffer Empty Interrupt Enable     \
                  (available in all USART modes of operation) */
#define US_IER_RXBUFF                                                          \
  (0x1u << 12) /**< \brief (US_IER) Receive Buffer Full Interrupt Enable       \
                  (available in all USART modes of operation) */
#define US_IER_NACK                                                            \
  (0x1u << 13) /**< \brief (US_IER) Non Acknowledge Interrupt Enable */
#define US_IER_CTSIC                                                           \
  (0x1u                                                                        \
   << 19) /**< \brief (US_IER) Clear to Send Input Change Interrupt Enable */
#define US_IER_CMP                                                             \
  (0x1u << 22) /**< \brief (US_IER) Comparison Interrupt Enable */
#define US_IER_UNRE                                                            \
  (0x1u << 10) /**< \brief (US_IER) SPI Underrun Error Interrupt Enable */
#define US_IER_LINBK                                                           \
  (0x1u << 13) /**< \brief (US_IER) LIN Break Sent or LIN Break Received       \
                  Interrupt Enable */
#define US_IER_LINID                                                           \
  (0x1u << 14) /**< \brief (US_IER) LIN Identifier Sent or LIN Identifier      \
                  Received Interrupt Enable */
#define US_IER_LINTC                                                           \
  (0x1u << 15) /**< \brief (US_IER) LIN Transfer Completed Interrupt Enable */
#define US_IER_LINBE                                                           \
  (0x1u << 25) /**< \brief (US_IER) LIN Bus Error Interrupt Enable */
#define US_IER_LINISFE                                                         \
  (0x1u << 26) /**< \brief (US_IER) LIN Inconsistent Synch Field Error         \
                  Interrupt Enable */
#define US_IER_LINIPE                                                          \
  (0x1u << 27) /**< \brief (US_IER) LIN Identifier Parity Interrupt Enable */
#define US_IER_LINCE                                                           \
  (0x1u << 28) /**< \brief (US_IER) LIN Checksum Error Interrupt Enable */
#define US_IER_LINSNRE                                                         \
  (0x1u << 29) /**< \brief (US_IER) LIN Slave Not Responding Error Interrupt   \
                  Enable */
#define US_IER_LINSTE                                                          \
  (0x1u                                                                        \
   << 30) /**< \brief (US_IER) LIN Synch Tolerance Error Interrupt Enable */
#define US_IER_LINHTE                                                          \
  (0x1u << 31) /**< \brief (US_IER) LIN Header Timeout Error Interrupt Enable  \
                */
/* -------- US_IDR : (USART Offset: 0x00C) USART Interrupt Disable Register
 * -------- */
#define US_IDR_RXRDY (0x1u << 0) /**< \brief (US_IDR) RXRDY Interrupt Disable  \
                                  */
#define US_IDR_TXRDY (0x1u << 1) /**< \brief (US_IDR) TXRDY Interrupt Disable  \
                                  */
#define US_IDR_RXBRK                                                           \
  (0x1u << 2) /**< \brief (US_IDR) Receiver Break Interrupt Disable */
#define US_IDR_ENDRX                                                           \
  (0x1u << 3) /**< \brief (US_IDR) End of Receive Buffer Interrupt Enable      \
                 (available in all USART modes of operation) */
#define US_IDR_ENDTX                                                           \
  (0x1u << 4) /**< \brief (US_IDR) End of Transmit Buffer Interrupt Disable    \
                 (available in all USART modes of operation) */
#define US_IDR_OVRE                                                            \
  (0x1u << 5) /**< \brief (US_IDR) Overrun Error Interrupt Enable */
#define US_IDR_FRAME                                                           \
  (0x1u << 6) /**< \brief (US_IDR) Framing Error Interrupt Disable */
#define US_IDR_PARE                                                            \
  (0x1u << 7) /**< \brief (US_IDR) Parity Error Interrupt Disable */
#define US_IDR_TIMEOUT                                                         \
  (0x1u << 8) /**< \brief (US_IDR) Time-out Interrupt Disable */
#define US_IDR_TXEMPTY                                                         \
  (0x1u << 9) /**< \brief (US_IDR) TXEMPTY Interrupt Disable */
#define US_IDR_ITER                                                            \
  (0x1u << 10) /**< \brief (US_IDR) Max Number of Repetitions Reached          \
                  Interrupt Disable */
#define US_IDR_TXBUFE                                                          \
  (0x1u << 11) /**< \brief (US_IDR) Transmit Buffer Empty Interrupt Enable     \
                  (available in all USART modes of operation) */
#define US_IDR_RXBUFF                                                          \
  (0x1u << 12) /**< \brief (US_IDR) Receive Buffer Full Interrupt Enable       \
                  (available in all USART modes of operation) */
#define US_IDR_NACK                                                            \
  (0x1u << 13) /**< \brief (US_IDR) Non Acknowledge Interrupt Disable */
#define US_IDR_CTSIC                                                           \
  (0x1u                                                                        \
   << 19) /**< \brief (US_IDR) Clear to Send Input Change Interrupt Disable */
#define US_IDR_CMP                                                             \
  (0x1u << 22) /**< \brief (US_IDR) Comparison Interrupt Disable */
#define US_IDR_UNRE                                                            \
  (0x1u << 10) /**< \brief (US_IDR) SPI Underrun Error Interrupt Disable */
#define US_IDR_LINBK                                                           \
  (0x1u << 13) /**< \brief (US_IDR) LIN Break Sent or LIN Break Received       \
                  Interrupt Disable */
#define US_IDR_LINID                                                           \
  (0x1u << 14) /**< \brief (US_IDR) LIN Identifier Sent or LIN Identifier      \
                  Received Interrupt Disable */
#define US_IDR_LINTC                                                           \
  (0x1u << 15) /**< \brief (US_IDR) LIN Transfer Completed Interrupt Disable   \
                */
#define US_IDR_LINBE                                                           \
  (0x1u << 25) /**< \brief (US_IDR) LIN Bus Error Interrupt Disable */
#define US_IDR_LINISFE                                                         \
  (0x1u << 26) /**< \brief (US_IDR) LIN Inconsistent Synch Field Error         \
                  Interrupt Disable */
#define US_IDR_LINIPE                                                          \
  (0x1u << 27) /**< \brief (US_IDR) LIN Identifier Parity Interrupt Disable */
#define US_IDR_LINCE                                                           \
  (0x1u << 28) /**< \brief (US_IDR) LIN Checksum Error Interrupt Disable */
#define US_IDR_LINSNRE                                                         \
  (0x1u << 29) /**< \brief (US_IDR) LIN Slave Not Responding Error Interrupt   \
                  Disable */
#define US_IDR_LINSTE                                                          \
  (0x1u                                                                        \
   << 30) /**< \brief (US_IDR) LIN Synch Tolerance Error Interrupt Disable */
#define US_IDR_LINHTE                                                          \
  (0x1u                                                                        \
   << 31) /**< \brief (US_IDR) LIN Header Timeout Error Interrupt Disable */
/* -------- US_IMR : (USART Offset: 0x010) USART Interrupt Mask Register
 * -------- */
#define US_IMR_RXRDY (0x1u << 0) /**< \brief (US_IMR) RXRDY Interrupt Mask */
#define US_IMR_TXRDY (0x1u << 1) /**< \brief (US_IMR) TXRDY Interrupt Mask */
#define US_IMR_RXBRK                                                           \
  (0x1u << 2) /**< \brief (US_IMR) Receiver Break Interrupt Mask */
#define US_IMR_ENDRX                                                           \
  (0x1u << 3) /**< \brief (US_IMR) End of Receive Buffer Interrupt Mask        \
                 (available in all USART modes of operation) */
#define US_IMR_ENDTX                                                           \
  (0x1u << 4) /**< \brief (US_IMR) End of Transmit Buffer Interrupt Mask       \
                 (available in all USART modes of operation) */
#define US_IMR_OVRE                                                            \
  (0x1u << 5) /**< \brief (US_IMR) Overrun Error Interrupt Mask */
#define US_IMR_FRAME                                                           \
  (0x1u << 6) /**< \brief (US_IMR) Framing Error Interrupt Mask */
#define US_IMR_PARE                                                            \
  (0x1u << 7) /**< \brief (US_IMR) Parity Error Interrupt Mask */
#define US_IMR_TIMEOUT                                                         \
  (0x1u << 8) /**< \brief (US_IMR) Time-out Interrupt Mask */
#define US_IMR_TXEMPTY                                                         \
  (0x1u << 9) /**< \brief (US_IMR) TXEMPTY Interrupt Mask */
#define US_IMR_ITER                                                            \
  (0x1u << 10) /**< \brief (US_IMR) Max Number of Repetitions Reached          \
                  Interrupt Mask */
#define US_IMR_TXBUFE                                                          \
  (0x1u << 11) /**< \brief (US_IMR) Transmit Buffer Empty Interrupt Mask       \
                  (available in all USART modes of operation) */
#define US_IMR_RXBUFF                                                          \
  (0x1u << 12) /**< \brief (US_IMR) Receive Buffer Full Interrupt Mask         \
                  (available in all USART modes of operation) */
#define US_IMR_NACK                                                            \
  (0x1u << 13) /**< \brief (US_IMR) Non Acknowledge Interrupt Mask */
#define US_IMR_CTSIC                                                           \
  (0x1u << 19) /**< \brief (US_IMR) Clear to Send Input Change Interrupt Mask  \
                */
#define US_IMR_CMP                                                             \
  (0x1u << 22) /**< \brief (US_IMR) Comparison Interrupt Mask */
#define US_IMR_UNRE                                                            \
  (0x1u << 10) /**< \brief (US_IMR) SPI Underrun Error Interrupt Mask */
#define US_IMR_LINBK                                                           \
  (0x1u << 13) /**< \brief (US_IMR) LIN Break Sent or LIN Break Received       \
                  Interrupt Mask */
#define US_IMR_LINID                                                           \
  (0x1u << 14) /**< \brief (US_IMR) LIN Identifier Sent or LIN Identifier      \
                  Received Interrupt Mask */
#define US_IMR_LINTC                                                           \
  (0x1u << 15) /**< \brief (US_IMR) LIN Transfer Completed Interrupt Mask */
#define US_IMR_LINBE                                                           \
  (0x1u << 25) /**< \brief (US_IMR) LIN Bus Error Interrupt Mask */
#define US_IMR_LINISFE                                                         \
  (0x1u << 26) /**< \brief (US_IMR) LIN Inconsistent Synch Field Error         \
                  Interrupt Mask */
#define US_IMR_LINIPE                                                          \
  (0x1u << 27) /**< \brief (US_IMR) LIN Identifier Parity Interrupt Mask */
#define US_IMR_LINCE                                                           \
  (0x1u << 28) /**< \brief (US_IMR) LIN Checksum Error Interrupt Mask */
#define US_IMR_LINSNRE                                                         \
  (0x1u << 29) /**< \brief (US_IMR) LIN Slave Not Responding Error Interrupt   \
                  Mask */
#define US_IMR_LINSTE                                                          \
  (0x1u << 30) /**< \brief (US_IMR) LIN Synch Tolerance Error Interrupt Mask   \
                */
#define US_IMR_LINHTE                                                          \
  (0x1u << 31) /**< \brief (US_IMR) LIN Header Timeout Error Interrupt Mask */
/* -------- US_CSR : (USART Offset: 0x014) USART Channel Status Register
 * -------- */
#define US_CSR_RXRDY                                                           \
  (0x1u                                                                        \
   << 0) /**< \brief (US_CSR) Receiver Ready (automatically set / cleared) */
#define US_CSR_TXRDY                                                           \
  (0x1u << 1) /**< \brief (US_CSR) Transmitter Ready (automatically set /      \
                 cleared) */
#define US_CSR_RXBRK                                                           \
  (0x1u << 2) /**< \brief (US_CSR) Break Received/End of Break (cleared by     \
                 US_CR.RSTSTA command) */
#define US_CSR_ENDRX                                                           \
  (0x1u << 3) /**< \brief (US_CSR) End of RX Buffer (automatically set /       \
                 cleared) */
#define US_CSR_ENDTX                                                           \
  (0x1u << 4) /**< \brief (US_CSR) End of TX Buffer (automatically set /       \
                 cleared) */
#define US_CSR_OVRE                                                            \
  (0x1u << 5) /**< \brief (US_CSR) Overrun Error (cleared by US_CR.RSTSTA      \
                 command) */
#define US_CSR_FRAME                                                           \
  (0x1u << 6) /**< \brief (US_CSR) Framing Error (cleared by US_CR.RSTSTA      \
                 command) */
#define US_CSR_PARE                                                            \
  (0x1u << 7) /**< \brief (US_CSR) Parity Error (cleared by US_CR.RSTSTA       \
                 command) */
#define US_CSR_TIMEOUT                                                         \
  (0x1u << 8) /**< \brief (US_CSR) Receiver Time-out (cleared by US_CR.STTTO   \
                 command) */
#define US_CSR_TXEMPTY                                                         \
  (0x1u << 9) /**< \brief (US_CSR) Transmitter Empty (automatically set /      \
                 cleared) */
#define US_CSR_ITER                                                            \
  (0x1u << 10) /**< \brief (US_CSR) Max Number of Repetitions Reached (cleared \
                  by US_CR.RSTIT command) */
#define US_CSR_TXBUFE                                                          \
  (0x1u << 11) /**< \brief (US_CSR) TX Buffer Empty (automatically set /       \
                  cleared) */
#define US_CSR_RXBUFF                                                          \
  (0x1u                                                                        \
   << 12) /**< \brief (US_CSR) RX Buffer Full (automatically set / cleared) */
#define US_CSR_NACK                                                            \
  (0x1u << 13) /**< \brief (US_CSR) Non Acknowledge Interrupt (cleared by      \
                  US_CR.RSTNACK command) */
#define US_CSR_CTSIC                                                           \
  (0x1u << 19) /**< \brief (US_CSR) Clear to Send Input Change Flag (clear on  \
                  read) */
#define US_CSR_CMP                                                             \
  (0x1u << 22) /**< \brief (US_CSR) Comparison Status (cleared by US_CR.RSTSTA \
                  command) */
#define US_CSR_CTS                                                             \
  (0x1u << 23) /**< \brief (US_CSR) Image of CTS Input (automatically set /    \
                  cleared) */
#define US_CSR_UNRE                                                            \
  (0x1u << 10) /**< \brief (US_CSR) Underrun Error (cleared by US_CR.RSTSTA)   \
                */
#define US_CSR_LINBK                                                           \
  (0x1u << 13) /**< \brief (US_CSR) LIN Break Sent or LIN Break Received       \
                  (cleared by US_CR.RSTSTA command) */
#define US_CSR_LINID                                                           \
  (0x1u << 14) /**< \brief (US_CSR) LIN Identifier Sent or LIN Identifier      \
                  Received (cleared by US_CR.RSTSTA command) */
#define US_CSR_LINTC                                                           \
  (0x1u << 15) /**< \brief (US_CSR) LIN Transfer Completed (cleared by         \
                  US_CR.RSTSTA command) */
#define US_CSR_LINBLS (0x1u << 23) /**< \brief (US_CSR) LIN Bus Line Status */
#define US_CSR_LINBE                                                           \
  (0x1u << 25) /**< \brief (US_CSR) LIN Bit Error (cleared by US_CR.RSTSTA     \
                  command) */
#define US_CSR_LINISFE                                                         \
  (0x1u << 26) /**< \brief (US_CSR) LIN Inconsistent Synch Field Error         \
                  (cleared by US_CR.RSTSTA command) */
#define US_CSR_LINIPE                                                          \
  (0x1u << 27) /**< \brief (US_CSR) LIN Identifier Parity Error (cleared by    \
                  US_CR.RSTSTA command) */
#define US_CSR_LINCE                                                           \
  (0x1u << 28) /**< \brief (US_CSR) LIN Checksum Error (cleared by             \
                  US_CR.RSTSTA command) */
#define US_CSR_LINSNRE                                                         \
  (0x1u << 29) /**< \brief (US_CSR) LIN Slave Not Responding Error (cleared by \
                  US_CR.RSTSTA command) */
#define US_CSR_LINSTE                                                          \
  (0x1u << 30) /**< \brief (US_CSR) LIN Synch Tolerance Error (cleared by      \
                  US_CR.RSTSTA command) */
#define US_CSR_LINHTE                                                          \
  (0x1u << 31) /**< \brief (US_CSR) LIN Header Timeout Error (cleared by       \
                  US_CR.RSTSTA command) */
/* -------- US_RHR : (USART Offset: 0x018) USART Receive Holding Register
 * -------- */
#define US_RHR_RXCHR_Pos 0
#define US_RHR_RXCHR_Msk                                                       \
  (0x1ffu << US_RHR_RXCHR_Pos)     /**< \brief (US_RHR) Received Character */
#define US_RHR_RXSYNH (0x1u << 15) /**< \brief (US_RHR) Received Sync */
/* -------- US_THR : (USART Offset: 0x01C) USART Transmit Holding Register
 * -------- */
#define US_THR_TXCHR_Pos 0
#define US_THR_TXCHR_Msk                                                       \
  (0x1ffu                                                                      \
   << US_THR_TXCHR_Pos) /**< \brief (US_THR) Character to be Transmitted */
#define US_THR_TXCHR(value) ((US_THR_TXCHR_Msk & ((value) << US_THR_TXCHR_Pos)))
#define US_THR_TXSYNH                                                          \
  (0x1u << 15) /**< \brief (US_THR) Sync Field to be Transmitted */
/* -------- US_BRGR : (USART Offset: 0x020) USART Baud Rate Generator Register
 * -------- */
#define US_BRGR_CD_Pos 0
#define US_BRGR_CD_Msk                                                         \
  (0xffffu << US_BRGR_CD_Pos) /**< \brief (US_BRGR) Clock Divider */
#define US_BRGR_CD(value) ((US_BRGR_CD_Msk & ((value) << US_BRGR_CD_Pos)))
#define US_BRGR_FP_Pos 16
#define US_BRGR_FP_Msk                                                         \
  (0x7u << US_BRGR_FP_Pos) /**< \brief (US_BRGR) Fractional Part */
#define US_BRGR_FP(value) ((US_BRGR_FP_Msk & ((value) << US_BRGR_FP_Pos)))
/* -------- US_RTOR : (USART Offset: 0x024) USART Receiver Time-out Register
 * -------- */
#define US_RTOR_TO_Pos 0
#define US_RTOR_TO_Msk                                                         \
  (0x1ffffu << US_RTOR_TO_Pos) /**< \brief (US_RTOR) Time-out Value */
#define US_RTOR_TO(value) ((US_RTOR_TO_Msk & ((value) << US_RTOR_TO_Pos)))
/* -------- US_TTGR : (USART Offset: 0x028) USART Transmitter Timeguard Register
 * -------- */
#define US_TTGR_TG_Pos 0
#define US_TTGR_TG_Msk                                                         \
  (0xffu << US_TTGR_TG_Pos) /**< \brief (US_TTGR) Timeguard Value */
#define US_TTGR_TG(value) ((US_TTGR_TG_Msk & ((value) << US_TTGR_TG_Pos)))
/* -------- US_FIDI : (USART Offset: 0x040) USART FI DI Ratio Register --------
 */
#define US_FIDI_FI_DI_RATIO_Pos 0
#define US_FIDI_FI_DI_RATIO_Msk                                                \
  (0xffffu                                                                     \
   << US_FIDI_FI_DI_RATIO_Pos) /**< \brief (US_FIDI) FI Over DI Ratio Value */
#define US_FIDI_FI_DI_RATIO(value)                                             \
  ((US_FIDI_FI_DI_RATIO_Msk & ((value) << US_FIDI_FI_DI_RATIO_Pos)))
/* -------- US_NER : (USART Offset: 0x044) USART Number of Errors Register
 * -------- */
#define US_NER_NB_ERRORS_Pos 0
#define US_NER_NB_ERRORS_Msk                                                   \
  (0xffu << US_NER_NB_ERRORS_Pos) /**< \brief (US_NER) Number of Errors */
/* -------- US_LINMR : (USART Offset: 0x054) USART LIN Mode Register -------- */
#define US_LINMR_NACT_Pos 0
#define US_LINMR_NACT_Msk                                                      \
  (0x3u << US_LINMR_NACT_Pos) /**< \brief (US_LINMR) LIN Node Action */
#define US_LINMR_NACT_PUBLISH                                                  \
  (0x0u << 0) /**< \brief (US_LINMR) The USART transmits the response. */
#define US_LINMR_NACT_SUBSCRIBE                                                \
  (0x1u << 0) /**< \brief (US_LINMR) The USART receives the response. */
#define US_LINMR_NACT_IGNORE                                                   \
  (0x2u << 0) /**< \brief (US_LINMR) The USART does not transmit and does not  \
                 receive the response. */
#define US_LINMR_PARDIS (0x1u << 2) /**< \brief (US_LINMR) Parity Disable */
#define US_LINMR_CHKDIS (0x1u << 3) /**< \brief (US_LINMR) Checksum Disable */
#define US_LINMR_CHKTYP (0x1u << 4) /**< \brief (US_LINMR) Checksum Type */
#define US_LINMR_DLM (0x1u << 5)    /**< \brief (US_LINMR) Data Length Mode */
#define US_LINMR_FSDIS                                                         \
  (0x1u << 6) /**< \brief (US_LINMR) Frame Slot Mode Disable */
#define US_LINMR_WKUPTYP                                                       \
  (0x1u << 7) /**< \brief (US_LINMR) Wakeup Signal Type */
#define US_LINMR_DLC_Pos 8
#define US_LINMR_DLC_Msk                                                       \
  (0xffu << US_LINMR_DLC_Pos) /**< \brief (US_LINMR) Data Length Control */
#define US_LINMR_DLC(value) ((US_LINMR_DLC_Msk & ((value) << US_LINMR_DLC_Pos)))
#define US_LINMR_PDCM (0x1u << 16) /**< \brief (US_LINMR) PDC Mode */
#define US_LINMR_SYNCDIS                                                       \
  (0x1u << 17) /**< \brief (US_LINMR) Synchronization Disable */
/* -------- US_LINIR : (USART Offset: 0x058) USART LIN Identifier Register
 * -------- */
#define US_LINIR_IDCHR_Pos 0
#define US_LINIR_IDCHR_Msk                                                     \
  (0xffu << US_LINIR_IDCHR_Pos) /**< \brief (US_LINIR) Identifier Character */
#define US_LINIR_IDCHR(value)                                                  \
  ((US_LINIR_IDCHR_Msk & ((value) << US_LINIR_IDCHR_Pos)))
/* -------- US_LINBRR : (USART Offset: 0x05C) USART LIN Baud Rate Register
 * -------- */
#define US_LINBRR_LINCD_Pos 0
#define US_LINBRR_LINCD_Msk                                                    \
  (0xffffu << US_LINBRR_LINCD_Pos) /**< \brief (US_LINBRR) Clock Divider after \
                                      Synchronization */
#define US_LINBRR_LINFP_Pos 16
#define US_LINBRR_LINFP_Msk                                                    \
  (0x7u << US_LINBRR_LINFP_Pos) /**< \brief (US_LINBRR) Fractional Part after  \
                                   Synchronization */
/* -------- US_CMPR : (USART Offset: 0x090) USART Comparison Register --------
 */
#define US_CMPR_VAL1_Pos 0
#define US_CMPR_VAL1_Msk                                                       \
  (0x1ffu << US_CMPR_VAL1_Pos) /**< \brief (US_CMPR) First Comparison Value    \
                                  for Received Character */
#define US_CMPR_VAL1(value) ((US_CMPR_VAL1_Msk & ((value) << US_CMPR_VAL1_Pos)))
#define US_CMPR_CMPMODE (0x1u << 12) /**< \brief (US_CMPR) Comparison Mode */
#define US_CMPR_CMPMODE_FLAG_ONLY                                              \
  (0x0u << 12) /**< \brief (US_CMPR) Any character is received and comparison  \
                  function drives CMP flag. */
#define US_CMPR_CMPMODE_START_CONDITION                                        \
  (0x1u << 12) /**< \brief (US_CMPR) Comparison condition must be met to start \
                  reception of all incoming charactersuntil REQCLR is set. */
#define US_CMPR_CMPPAR (0x1u << 14) /**< \brief (US_CMPR) Compare Parity */
#define US_CMPR_VAL2_Pos 16
#define US_CMPR_VAL2_Msk                                                       \
  (0x1ffu << US_CMPR_VAL2_Pos) /**< \brief (US_CMPR) Second Comparison Value   \
                                  for Received Character */
#define US_CMPR_VAL2(value) ((US_CMPR_VAL2_Msk & ((value) << US_CMPR_VAL2_Pos)))
/* -------- US_WPMR : (USART Offset: 0x0E4) USART Write Protection Mode Register
 * -------- */
#define US_WPMR_WPEN                                                           \
  (0x1u << 0) /**< \brief (US_WPMR) Write Protection Enable */
#define US_WPMR_WPKEY_Pos 8
#define US_WPMR_WPKEY_Msk                                                      \
  (0xffffffu << US_WPMR_WPKEY_Pos) /**< \brief (US_WPMR) Write Protection Key  \
                                    */
#define US_WPMR_WPKEY_PASSWD                                                   \
  (0x555341u                                                                   \
   << 8) /**< \brief (US_WPMR) Writing any other value in this field aborts    \
            the write operation of the WPEN bit. Always reads as 0. */
/* -------- US_WPSR : (USART Offset: 0x0E8) USART Write Protection Status
 * Register -------- */
#define US_WPSR_WPVS                                                           \
  (0x1u << 0) /**< \brief (US_WPSR) Write Protection Violation Status */
#define US_WPSR_WPVSRC_Pos 8
#define US_WPSR_WPVSRC_Msk                                                     \
  (0xffffu << US_WPSR_WPVSRC_Pos) /**< \brief (US_WPSR) Write Protection       \
                                     Violation Source */
/* -------- US_RPR : (USART Offset: 0x100) Receive Pointer Register -------- */
#define US_RPR_RXPTR_Pos 0
#define US_RPR_RXPTR_Msk                                                       \
  (0xffffffffu                                                                 \
   << US_RPR_RXPTR_Pos) /**< \brief (US_RPR) Receive Pointer Register */
#define US_RPR_RXPTR(value) ((US_RPR_RXPTR_Msk & ((value) << US_RPR_RXPTR_Pos)))
/* -------- US_RCR : (USART Offset: 0x104) Receive Counter Register -------- */
#define US_RCR_RXCTR_Pos 0
#define US_RCR_RXCTR_Msk                                                       \
  (0xffffu << US_RCR_RXCTR_Pos) /**< \brief (US_RCR) Receive Counter Register  \
                                 */
#define US_RCR_RXCTR(value) ((US_RCR_RXCTR_Msk & ((value) << US_RCR_RXCTR_Pos)))
/* -------- US_TPR : (USART Offset: 0x108) Transmit Pointer Register -------- */
#define US_TPR_TXPTR_Pos 0
#define US_TPR_TXPTR_Msk                                                       \
  (0xffffffffu                                                                 \
   << US_TPR_TXPTR_Pos) /**< \brief (US_TPR) Transmit Counter Register */
#define US_TPR_TXPTR(value) ((US_TPR_TXPTR_Msk & ((value) << US_TPR_TXPTR_Pos)))
/* -------- US_TCR : (USART Offset: 0x10C) Transmit Counter Register -------- */
#define US_TCR_TXCTR_Pos 0
#define US_TCR_TXCTR_Msk                                                       \
  (0xffffu                                                                     \
   << US_TCR_TXCTR_Pos) /**< \brief (US_TCR) Transmit Counter Register */
#define US_TCR_TXCTR(value) ((US_TCR_TXCTR_Msk & ((value) << US_TCR_TXCTR_Pos)))
/* -------- US_RNPR : (USART Offset: 0x110) Receive Next Pointer Register
 * -------- */
#define US_RNPR_RXNPTR_Pos 0
#define US_RNPR_RXNPTR_Msk                                                     \
  (0xffffffffu                                                                 \
   << US_RNPR_RXNPTR_Pos) /**< \brief (US_RNPR) Receive Next Pointer */
#define US_RNPR_RXNPTR(value)                                                  \
  ((US_RNPR_RXNPTR_Msk & ((value) << US_RNPR_RXNPTR_Pos)))
/* -------- US_RNCR : (USART Offset: 0x114) Receive Next Counter Register
 * -------- */
#define US_RNCR_RXNCTR_Pos 0
#define US_RNCR_RXNCTR_Msk                                                     \
  (0xffffu << US_RNCR_RXNCTR_Pos) /**< \brief (US_RNCR) Receive Next Counter   \
                                   */
#define US_RNCR_RXNCTR(value)                                                  \
  ((US_RNCR_RXNCTR_Msk & ((value) << US_RNCR_RXNCTR_Pos)))
/* -------- US_TNPR : (USART Offset: 0x118) Transmit Next Pointer Register
 * -------- */
#define US_TNPR_TXNPTR_Pos 0
#define US_TNPR_TXNPTR_Msk                                                     \
  (0xffffffffu                                                                 \
   << US_TNPR_TXNPTR_Pos) /**< \brief (US_TNPR) Transmit Next Pointer */
#define US_TNPR_TXNPTR(value)                                                  \
  ((US_TNPR_TXNPTR_Msk & ((value) << US_TNPR_TXNPTR_Pos)))
/* -------- US_TNCR : (USART Offset: 0x11C) Transmit Next Counter Register
 * -------- */
#define US_TNCR_TXNCTR_Pos 0
#define US_TNCR_TXNCTR_Msk                                                     \
  (0xffffu << US_TNCR_TXNCTR_Pos) /**< \brief (US_TNCR) Transmit Counter Next  \
                                   */
#define US_TNCR_TXNCTR(value)                                                  \
  ((US_TNCR_TXNCTR_Msk & ((value) << US_TNCR_TXNCTR_Pos)))
/* -------- US_PTCR : (USART Offset: 0x120) Transfer Control Register --------
 */
#define US_PTCR_RXTEN                                                          \
  (0x1u << 0) /**< \brief (US_PTCR) Receiver Transfer Enable */
#define US_PTCR_RXTDIS                                                         \
  (0x1u << 1) /**< \brief (US_PTCR) Receiver Transfer Disable */
#define US_PTCR_TXTEN                                                          \
  (0x1u << 8) /**< \brief (US_PTCR) Transmitter Transfer Enable */
#define US_PTCR_TXTDIS                                                         \
  (0x1u << 9) /**< \brief (US_PTCR) Transmitter Transfer Disable */
#define US_PTCR_RXCBEN                                                         \
  (0x1u << 16) /**< \brief (US_PTCR) Receiver Circular Buffer Enable */
#define US_PTCR_RXCBDIS                                                        \
  (0x1u << 17) /**< \brief (US_PTCR) Receiver Circular Buffer Disable */
#define US_PTCR_TXCBEN                                                         \
  (0x1u << 18) /**< \brief (US_PTCR) Transmitter Circular Buffer Enable */
#define US_PTCR_TXCBDIS                                                        \
  (0x1u << 19) /**< \brief (US_PTCR) Transmitter Circular Buffer Disable */
#define US_PTCR_ERRCLR                                                         \
  (0x1u << 24) /**< \brief (US_PTCR) Transfer Bus Error Clear */
/* -------- US_PTSR : (USART Offset: 0x124) Transfer Status Register -------- */
#define US_PTSR_RXTEN                                                          \
  (0x1u << 0) /**< \brief (US_PTSR) Receiver Transfer Enable */
#define US_PTSR_TXTEN                                                          \
  (0x1u << 8) /**< \brief (US_PTSR) Transmitter Transfer Enable */
#define US_PTSR_RXCBEN                                                         \
  (0x1u << 16) /**< \brief (US_PTSR) Receiver Transfer Enable */
#define US_PTSR_TXCBEN                                                         \
  (0x1u << 18) /**< \brief (US_PTSR) Transmitter Transfer Enable */
#define US_PTSR_ERR                                                            \
  (0x1u << 24) /**< \brief (US_PTSR) Transfer Bus Error (clear on read) */

/*@}*/

#endif /* _SAMG55_USART_COMPONENT_ */
