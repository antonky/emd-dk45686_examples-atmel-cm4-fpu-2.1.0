/**
 * \file
 *
 * \brief Enhanced Embedded Flash Controller (EEFC) driver for SAM.
 *
 * Copyright (c) 2011-2016 Atmel Corporation. All rights reserved.
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

#include "efc.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_efc_group Enhanced Embedded Flash Controller (EEFC)
 *
 * The Enhanced Embedded Flash Controller ensures the interface of the Flash
 * block with the 32-bit internal bus.
 *
 * @{
 */

/* Address definition for read operation */
#if (SAM3XA || SAM3U4 || SAM4SD16 || SAM4SD32)
#define READ_BUFF_ADDR0 IFLASH0_ADDR
#define READ_BUFF_ADDR1 IFLASH1_ADDR
#elif (SAM3S || SAM3N || SAM4E || SAM4N || SAMG || SAMV71 || SAMV70 ||         \
       SAMS70 || SAME70)
#define READ_BUFF_ADDR IFLASH_ADDR
#elif (SAM4C || SAM4CP || SAM4CM)
#if (SAM4C32 || SAM4CMS32 || SAM4CMP32)
#define READ_BUFF_ADDR0 IFLASH0_CNC_ADDR
#define READ_BUFF_ADDR1 IFLASH1_CNC_ADDR
#else
#define READ_BUFF_ADDR IFLASH_CNC_ADDR
#endif
#elif (SAM3U || SAM4S)
#define READ_BUFF_ADDR IFLASH0_ADDR
#else
#warning Only reading unique ID for sam3/4 is implemented.
#endif

/* Flash Writing Protection Key */
#define FWP_KEY 0x5Au

#if (SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM)
#define EEFC_FCR_FCMD(value)                                                   \
  ((EEFC_FCR_FCMD_Msk & ((value) << EEFC_FCR_FCMD_Pos)))
#define EEFC_ERROR_FLAGS (EEFC_FSR_FLOCKE | EEFC_FSR_FCMDE | EEFC_FSR_FLERR)
#elif (SAMV71 || SAMV70 || SAMS70 || SAME70)
#define EEFC_ERROR_FLAGS                                                       \
  (EEFC_FSR_FLOCKE | EEFC_FSR_FCMDE | EEFC_FSR_FLERR | EEFC_FSR_UECCELSB |     \
   EEFC_FSR_MECCELSB | EEFC_FSR_UECCEMSB | EEFC_FSR_MECCEMSB)
#else
#define EEFC_ERROR_FLAGS (EEFC_FSR_FLOCKE | EEFC_FSR_FCMDE)
#endif

#ifndef EEFC_FCR_FKEY_PASSWD
#define EEFC_FCR_FKEY_PASSWD EEFC_FCR_FKEY(FWP_KEY)
#endif

/*
 * Local function declaration.
 * Because they are RAM functions, they need 'extern' declaration.
 */
extern void efc_write_fmr(Efc *p_efc, uint32_t ul_fmr);
extern uint32_t efc_perform_fcr(Efc *p_efc, uint32_t ul_fcr);

/**
 * \brief Initialize the EFC controller.
 *
 * \param ul_access_mode 0 for 128-bit, EEFC_FMR_FAM for 64-bit.
 * \param ul_fws The number of wait states in cycle (no shift).
 *
 * \return 0 if successful.
 */
uint32_t efc_init(Efc *p_efc, uint32_t ul_access_mode, uint32_t ul_fws) {
#if (SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || \
     SAMV70 || SAMS70 || SAME70)
  efc_write_fmr(p_efc, ul_access_mode | EEFC_FMR_FWS(ul_fws) | EEFC_FMR_CLOE);
#else
  efc_write_fmr(p_efc, ul_access_mode | EEFC_FMR_FWS(ul_fws));
#endif
  return EFC_RC_OK;
}

#if (SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || \
     SAMV70 || SAMS70 || SAME70)
/**
 * \brief Enable code loop optimization.
 *
 * \param p_efc Pointer to an EFC instance.
 */
void efc_enable_cloe(Efc *p_efc) {
  uint32_t ul_fmr = p_efc->EEFC_FMR;
  efc_write_fmr(p_efc, ul_fmr | EEFC_FMR_CLOE);
}

/**
 * \brief Disable code loop optimization.
 *
 * \param p_efc Pointer to an EFC instance.
 */
void efc_disable_cloe(Efc *p_efc) {
  uint32_t ul_fmr = p_efc->EEFC_FMR;
  efc_write_fmr(p_efc, ul_fmr & (~EEFC_FMR_CLOE));
}
#endif

/**
 * \brief Enable the flash ready interrupt.
 *
 * \param p_efc Pointer to an EFC instance.
 */
void efc_enable_frdy_interrupt(Efc *p_efc) {
  uint32_t ul_fmr = p_efc->EEFC_FMR;

  efc_write_fmr(p_efc, ul_fmr | EEFC_FMR_FRDY);
}

/**
 * \brief Disable the flash ready interrupt.
 *
 * \param p_efc Pointer to an EFC instance.
 */
void efc_disable_frdy_interrupt(Efc *p_efc) {
  uint32_t ul_fmr = p_efc->EEFC_FMR;

  efc_write_fmr(p_efc, ul_fmr & (~EEFC_FMR_FRDY));
}

#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
/**
 * \brief Enable the write protection.
 *
 * \param p_efc Pointer to an EFC instance.
 */
void efc_enable_write_protection(Efc *p_efc) {
  p_efc->EEFC_WPMR = EEFC_WPMR_WPKEY_PASSWD | EEFC_WPMR_WPEN;
}

/**
 * \brief Disable the write protection.
 *
 * \param p_efc Pointer to an EFC instance.
 */
void efc_disable_write_protection(Efc *p_efc) {
  p_efc->EEFC_WPMR = EEFC_WPMR_WPKEY_PASSWD;
}
#else
/**
 * \brief Set flash access mode.
 *
 * \param p_efc Pointer to an EFC instance.
 * \param ul_mode 0 for 128-bit, EEFC_FMR_FAM for 64-bit.
 */
void efc_set_flash_access_mode(Efc *p_efc, uint32_t ul_mode) {
  uint32_t ul_fmr = p_efc->EEFC_FMR & (~EEFC_FMR_FAM);

  efc_write_fmr(p_efc, ul_fmr | ul_mode);
}

/**
 * \brief Get flash access mode.
 *
 * \param p_efc Pointer to an EFC instance.
 *
 * \return 0 for 128-bit or EEFC_FMR_FAM for 64-bit.
 */
uint32_t efc_get_flash_access_mode(Efc *p_efc) {
  return (p_efc->EEFC_FMR & EEFC_FMR_FAM);
}
#endif

/**
 * \brief Set flash wait state.
 *
 * \param p_efc Pointer to an EFC instance.
 * \param ul_fws The number of wait states in cycle (no shift).
 */
void efc_set_wait_state(Efc *p_efc, uint32_t ul_fws) {
  uint32_t ul_fmr = p_efc->EEFC_FMR & (~EEFC_FMR_FWS_Msk);

  efc_write_fmr(p_efc, ul_fmr | EEFC_FMR_FWS(ul_fws));
}

/**
 * \brief Get flash wait state.
 *
 * \param p_efc Pointer to an EFC instance.
 *
 * \return The number of wait states in cycle (no shift).
 */
uint32_t efc_get_wait_state(Efc *p_efc) {
  return ((p_efc->EEFC_FMR & EEFC_FMR_FWS_Msk) >> EEFC_FMR_FWS_Pos);
}

/**
 * \brief Perform the given command and wait until its completion (or an error).
 *
 * \note Unique ID commands are not supported, use efc_perform_read_sequence.
 *
 * \param p_efc Pointer to an EFC instance.
 * \param ul_command Command to perform.
 * \param ul_argument Optional command argument.
 *
 * \note This function will automatically choose to use IAP function.
 *
 * \return 0 if successful, otherwise returns an error code.
 */
uint32_t efc_perform_command(Efc *p_efc, uint32_t ul_command,
                             uint32_t ul_argument) {
  uint32_t result;
  irqflags_t flags;

  /* Unique ID commands are not supported. */
  if (ul_command == EFC_FCMD_STUI || ul_command == EFC_FCMD_SPUI) {
    return EFC_RC_NOT_SUPPORT;
  }

  flags = cpu_irq_save();
  /* Use RAM Function. */
  result =
      efc_perform_fcr(p_efc, EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FARG(ul_argument) |
                                 EEFC_FCR_FCMD(ul_command));
  cpu_irq_restore(flags);
  return result;
}

/**
 * \brief Get the current status of the EEFC.
 *
 * \note This function clears the value of some status bits (FLOCKE, FCMDE).
 *
 * \param p_efc Pointer to an EFC instance.
 *
 * \return The current status.
 */
uint32_t efc_get_status(Efc *p_efc) { return p_efc->EEFC_FSR; }

/**
 * \brief Get the result of the last executed command.
 *
 * \param p_efc Pointer to an EFC instance.
 *
 * \return The result of the last executed command.
 */
uint32_t efc_get_result(Efc *p_efc) { return p_efc->EEFC_FRR; }

/**
 * \brief Perform read sequence. Supported sequences are read Unique ID and
 * read User Signature
 *
 * \param p_efc Pointer to an EFC instance.
 * \param ul_cmd_st Start command to perform.
 * \param ul_cmd_sp Stop command to perform.
 * \param p_ul_buf Pointer to an data buffer.
 * \param ul_size Buffer size.
 *
 * \return 0 if successful, otherwise returns an error code.
 */
__no_inline RAMFUNC uint32_t efc_perform_read_sequence(Efc *p_efc,
                                                       uint32_t ul_cmd_st,
                                                       uint32_t ul_cmd_sp,
                                                       uint32_t *p_ul_buf,
                                                       uint32_t ul_size) {
  volatile uint32_t ul_status;
  uint32_t ul_cnt;

#if (SAM3U4 || SAM3XA || SAM4SD16 || SAM4SD32 || SAM4C32 || SAM4CMS32 ||       \
     SAM4CMP32)
  uint32_t *p_ul_data =
      (uint32_t *)((p_efc == EFC0) ? READ_BUFF_ADDR0 : READ_BUFF_ADDR1);
#elif (SAM3S || SAM4S || SAM3N || SAM3U || SAM4E || SAM4N || SAM4C || SAMG ||  \
       SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAMS70 || SAME70)
  uint32_t *p_ul_data = (uint32_t *)READ_BUFF_ADDR;
#else
  return EFC_RC_NOT_SUPPORT;
#endif

  if (p_ul_buf == NULL) {
    return EFC_RC_INVALID;
  }

  p_efc->EEFC_FMR |= (0x1u << 16);

  /* Send the Start Read command */
#if (SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || \
     SAMV70 || SAMS70 || SAME70)
  p_efc->EEFC_FCR =
      EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FARG(0) | EEFC_FCR_FCMD(ul_cmd_st);
#else
  p_efc->EEFC_FCR =
      EEFC_FCR_FKEY(FWP_KEY) | EEFC_FCR_FARG(0) | EEFC_FCR_FCMD(ul_cmd_st);
#endif
  /* Wait for the FRDY bit in the Flash Programming Status Register
   * (EEFC_FSR) falls.
   */
  do {
    ul_status = p_efc->EEFC_FSR;
  } while ((ul_status & EEFC_FSR_FRDY) == EEFC_FSR_FRDY);

  /* The data is located in the first address of the Flash
   * memory mapping.
   */
  for (ul_cnt = 0; ul_cnt < ul_size; ul_cnt++) {
    p_ul_buf[ul_cnt] = p_ul_data[ul_cnt];
  }

  /* To stop the read mode */
  p_efc->EEFC_FCR =
#if (SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || \
     SAMV70 || SAMS70 || SAME70)
      EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FARG(0) | EEFC_FCR_FCMD(ul_cmd_sp);
#else
      EEFC_FCR_FKEY(FWP_KEY) | EEFC_FCR_FARG(0) | EEFC_FCR_FCMD(ul_cmd_sp);
#endif
  /* Wait for the FRDY bit in the Flash Programming Status Register (EEFC_FSR)
   * rises.
   */
  do {
    ul_status = p_efc->EEFC_FSR;
  } while ((ul_status & EEFC_FSR_FRDY) != EEFC_FSR_FRDY);

  p_efc->EEFC_FMR &= ~(0x1u << 16);

  return EFC_RC_OK;
}

/**
 * \brief Set mode register.
 *
 * \param p_efc Pointer to an EFC instance.
 * \param ul_fmr Value of mode register
 */
__no_inline RAMFUNC void efc_write_fmr(Efc *p_efc, uint32_t ul_fmr) {
  p_efc->EEFC_FMR = ul_fmr;
}

/**
 * \brief Perform command.
 *
 * \param p_efc Pointer to an EFC instance.
 * \param ul_fcr Flash command.
 *
 * \return The current status.
 */
__no_inline RAMFUNC uint32_t efc_perform_fcr(Efc *p_efc, uint32_t ul_fcr) {
  volatile uint32_t ul_status;

  p_efc->EEFC_FCR = ul_fcr;
  do {
    ul_status = p_efc->EEFC_FSR;
  } while ((ul_status & EEFC_FSR_FRDY) != EEFC_FSR_FRDY);

  return (ul_status & EEFC_ERROR_FLAGS);
}

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
