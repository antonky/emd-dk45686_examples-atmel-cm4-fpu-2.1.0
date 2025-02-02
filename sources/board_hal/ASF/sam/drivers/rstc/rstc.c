/**
 * \file
 *
 * \brief SAM Reset Controller (RSTC) driver.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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

#include "rstc.h"

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define RSTC_KEY 0xA5000000

/**
 * \brief Set the external reset length.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 * \param[in] ul_length The length of external reset
 */
void rstc_set_external_reset(Rstc *p_rstc, const uint32_t ul_length) {
  /* Validate the parameters. */
  Assert(p_rstc);

  uint32_t mode = p_rstc->RSTC_MR;

  mode &= ~(RSTC_MR_ERSTL_Msk | RSTC_MR_KEY_Msk);
  mode |= (RSTC_MR_ERSTL(ul_length) | RSTC_KEY);

  p_rstc->RSTC_MR = mode;
}

/**
 * \brief Enable User Reset.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_enable_user_reset(Rstc *p_rstc) {
  /* Validate the parameters. */
  Assert(p_rstc);

  uint32_t mode = p_rstc->RSTC_MR;

  mode &= ~RSTC_MR_KEY_Msk;
  mode |= (RSTC_MR_URSTEN | RSTC_KEY);

  p_rstc->RSTC_MR = mode;
}

/**
 * \brief Disable User Reset.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_disable_user_reset(Rstc *p_rstc) {
  /* Validate the parameters. */
  Assert(p_rstc);

  uint32_t mode = p_rstc->RSTC_MR;

  mode &= ~(RSTC_MR_URSTEN | RSTC_MR_KEY_Msk);
  mode |= RSTC_KEY;

  p_rstc->RSTC_MR = mode;
}

/**
 * \brief Enable the User Reset interrupt.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_enable_user_reset_interrupt(Rstc *p_rstc) {
  /* Validate the parameters. */
  Assert(p_rstc);

  uint32_t mode = p_rstc->RSTC_MR;

  mode &= ~RSTC_MR_KEY_Msk;
  mode |= (RSTC_MR_URSTIEN | RSTC_KEY);

  p_rstc->RSTC_MR = mode;
}

/**
 * \brief Disable the User Reset interrupt.
 *
 * \param[in,out] p_rstc Module hardware register base address pointer
 */
void rstc_disable_user_reset_interrupt(Rstc *p_rstc) {
  /* Validate the parameters. */
  Assert(p_rstc);

  uint32_t mode = p_rstc->RSTC_MR;

  mode &= ~(RSTC_MR_URSTIEN | RSTC_MR_KEY_Msk);
  mode |= RSTC_KEY;

  p_rstc->RSTC_MR = mode;
}

/**
 * \brief Perform a Software Reset.
 *
 * \param[out] p_rstc Module hardware register base address pointer
 */
void rstc_start_software_reset(Rstc *p_rstc) {
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
  p_rstc->RSTC_CR = RSTC_KEY | RSTC_CR_PROCRST;
#else
  p_rstc->RSTC_CR = RSTC_KEY | RSTC_CR_PROCRST | RSTC_CR_PERRST;
#endif
}

/**
 * \brief Asserts the NRST pin for external resets.
 *
 * \param[out] p_rstc Module hardware register base address pointer
 */
void rstc_reset_extern(Rstc *p_rstc) {
  p_rstc->RSTC_CR = RSTC_KEY | RSTC_CR_EXTRST;
}

/**
 * \brief Get the RSTC status.
 *
 * \param[in] p_rstc Module hardware register base address pointer
 *
 * \return RSTC status.
 */
uint32_t rstc_get_status(Rstc *p_rstc) { return p_rstc->RSTC_SR; }

/**
 * \brief Get the reset cause.
 *
 * \param[in] p_rstc Module hardware register base address pointer
 *
 * \return The last reset cause.
 */
uint32_t rstc_get_reset_cause(Rstc *p_rstc) {
  return (p_rstc->RSTC_SR & RSTC_SR_RSTTYP_Msk);
}

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
