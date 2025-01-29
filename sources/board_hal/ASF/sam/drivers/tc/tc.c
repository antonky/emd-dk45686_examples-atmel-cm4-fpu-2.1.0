/**
 * \file
 *
 * \brief SAM Timer Counter (TC) driver.
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

#include "tc.h"
#include <assert.h>

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#ifndef TC_WPMR_WPKEY_PASSWD
#define TC_WPMR_WPKEY_PASSWD TC_WPMR_WPKEY((uint32_t)0x54494D)
#endif

/**
 * \brief Configure TC for timer, waveform generation, or capture.
 *
 * \param[in,out] p_tc   Module hardware register base address pointer
 * \param[in] ul_channel Channel to configure
 * \param[in] ul_mode    Control mode register bitmask value to set
 *
 * \note For more information regarding <i>ul_mode</i> configuration refer to
 * the section entitled "Channel Mode Register: Capture Mode" and/or section
 * "Waveform Operating Mode" in the device-specific datasheet.
 *
 * \note If the TC is configured for waveform generation then the external event
 * selection (EEVT) should only be set to TC_CMR_EEVT_TIOB, or the
 * equivalent value of 0, if it really is the intention to use TIOB as an
 * external event trigger. This is because this setting forces TIOB to be
 * an input, even if the external event trigger has not been enabled with
 * TC_CMR_ENETRG, and thus prevents normal operation of TIOB.
 */
void tc_init(Tc *p_tc, uint32_t ul_channel, uint32_t ul_mode) {
  TcChannel *tc_channel;

  /* Validate inputs. */
  Assert(p_tc);
  Assert(ul_channel < (sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
  tc_channel = p_tc->TC_CHANNEL + ul_channel;

  /*  Disable TC clock. */
  tc_channel->TC_CCR = TC_CCR_CLKDIS;

  /*  Disable interrupts. */
  tc_channel->TC_IDR = 0xFFFFFFFF;

  /*  Clear status register. */
  tc_channel->TC_SR;

  /*  Set mode. */
  tc_channel->TC_CMR = ul_mode;
}

/* TC divisor used to find the lowest acceptable timer frequency */
#define TC_DIV_FACTOR 65536

#if (!SAM4L) && !defined(__DOXYGEN__)

#ifndef FREQ_SLOW_CLOCK_EXT
#define FREQ_SLOW_CLOCK_EXT 32768 /* External slow clock frequency (hz) */
#endif

/**
 * \brief Find the best MCK divisor.
 *
 * Finds the best MCK divisor given the timer frequency and MCK. The result
 * is guaranteed to satisfy the following equation:
 * \code (MCK / (DIV * 65536)) <= freq <= (MCK / DIV) \endcode
 * With DIV being the lowest possible value, to maximize timing adjust
 * resolution.
 *
 * \param[in] ul_freq     Desired timer frequency
 * \param[in] ul_mck      Master clock frequency
 * \param[out] p_uldiv    Divisor value
 * \param[out] p_ultcclks TCCLKS field value for divisor
 * \param[in] ul_boardmck Board clock frequency
 *
 * \return The divisor found status.
 * \retval 0 No suitable divisor was found
 * \retval 1 A divisor was found
 */
uint32_t tc_find_mck_divisor(uint32_t ul_freq, uint32_t ul_mck,
                             uint32_t *p_uldiv, uint32_t *p_ultcclks,
                             uint32_t ul_boardmck) {
  const uint32_t divisors[5] = {2, 8, 32, 128,
                                ul_boardmck / FREQ_SLOW_CLOCK_EXT};
  uint32_t ul_index;
  uint32_t ul_high, ul_low;

  /*  Satisfy frequency bound. */
  for (ul_index = 0; ul_index < (sizeof(divisors) / sizeof(divisors[0]));
       ul_index++) {
    ul_high = ul_mck / divisors[ul_index];
    ul_low = ul_high / TC_DIV_FACTOR;
    if (ul_freq > ul_high) {
      return 0;
    } else if (ul_freq >= ul_low) {
      break;
    }
  }
  if (ul_index >= (sizeof(divisors) / sizeof(divisors[0]))) {
    return 0;
  }

  /*  Store results. */
  if (p_uldiv) {
    *p_uldiv = divisors[ul_index];
  }

  if (p_ultcclks) {
    *p_ultcclks = ul_index;
  }

  return 1;
}

#endif /* (!SAM4L) */

#if (SAM4L) || defined(__DOXYGEN__)
/**
 * \brief Find the best PBA/MCK divisor.
 *
 * <b>For SAM4L devices:</b> Finds the best PBA divisor given the timer
 * frequency and PBA clock. The result is guaranteed to satisfy the following
 * equation:
 * \code  (ul_pbaclk / (2* DIV * 65536)) <= freq <= (ul_pbaclk / (2* DIV))
 * \endcode with DIV being the lowest possible value, to maximize timing adjust
 * resolution.
 *
 * <b>For non SAM4L devices:</b> Finds the best MCK divisor given the timer
 * frequency and MCK. The result is guaranteed to satisfy the following
 * equation:
 * \code (MCK / (DIV * 65536)) <= freq <= (MCK / DIV) \endcode
 * with DIV being the lowest possible value, to maximize timing adjust
 * resolution.
 *
 * \param[in] ul_freq     Desired timer frequency
 * \param[in] ul_mck      PBA clock frequency
 * \param[out] p_uldiv    Divisor value
 * \param[out] p_ultcclks TCCLKS field value for divisor
 * \param[in] ul_boardmck Board clock frequency (set to 0 for SAM4L devices)
 *
 * \return The divisor found status.
 * \retval 0 No suitable divisor was found
 * \retval 1 A divisor was found
 */
uint32_t tc_find_mck_divisor(uint32_t ul_freq, uint32_t ul_mck,
                             uint32_t *p_uldiv, uint32_t *p_ultcclks,
                             uint32_t ul_boardmck) {
  const uint32_t divisors[5] = {0, 2, 8, 32, 128};
  uint32_t ul_index;
  uint32_t ul_high, ul_low;

  UNUSED(ul_boardmck);

  /*  Satisfy frequency bound. */
  for (ul_index = 1; ul_index < (sizeof(divisors) / sizeof(divisors[0]));
       ul_index++) {
    ul_high = ul_mck / divisors[ul_index];
    ul_low = ul_high / TC_DIV_FACTOR;
    if (ul_freq > ul_high) {
      return 0;
    } else if (ul_freq >= ul_low) {
      break;
    }
  }
  if (ul_index >= (sizeof(divisors) / sizeof(divisors[0]))) {
    return 0;
  }

  /*  Store results. */
  if (p_uldiv) {
    *p_uldiv = divisors[ul_index];
  }

  if (p_ultcclks) {
    *p_ultcclks = ul_index;
  }

  return 1;
}

#endif /* (SAM4L) || defined(__DOXYGEN__) */

#if (!SAM4L && !SAMG) || defined(__DOXYGEN__)

/**
 * \brief Enable TC QDEC interrupts.
 *
 * \note This function is not available on SAM4L or SAMG devices.
 *
 * \param[out] p_tc      Module hardware register base address pointer
 * \param[in] ul_sources A bitmask of QDEC interrupts to be enabled
 *
 * Where the input parameter <i>ul_sources</i> can be one or more of the
 * following: <table> <tr> <th>Parameter Value</th> <th>Description</th>
 * </tr>
 *     <tr><td>TC_QIER_IDX</td><td>Enable the rising edge detected on IDX input
 * interrupt</td></tr> <tr><td>TC_QIER_DIRCHG</td><td>Enable the change in
 * rotation direction detected interrupt</td></tr>
 *     <tr><td>TC_QIER_QERR</td><td>Enable the quadrature error detected on
 * PHA/PHB interrupt</td></tr>
 * </table>
 */
void tc_enable_qdec_interrupt(Tc *p_tc, uint32_t ul_sources) {
  /* Validate inputs. */
  Assert(p_tc);

  p_tc->TC_QIER = ul_sources;
}

/**
 * \brief Disable TC QDEC interrupts.
 *
 * \note This function is not available on SAM4L or SAMG devices.
 *
 * \param[out] p_tc      Module hardware register base address pointer
 * \param[in] ul_sources A bitmask of QDEC interrupts to be disabled
 *
 * Where the input parameter <i>ul_sources</i> can be one or more of the
 * following: <table> <tr> <th>Parameter Value</th> <th>Description</th>
 * </tr>
 *     <tr><td>TC_QIDR_IDX</td><td>Disable the rising edge detected on IDX input
 * interrupt</td></tr> <tr><td>TC_QIDR_DIRCHG</td><td>Disable the change in
 * rotation direction detected interrupt</td></tr>
 *     <tr><td>TC_QIDR_QERR</td><td>Disable the quadrature error detected on
 * PHA/PHB interrupt</td></tr>
 * </table>
 */
void tc_disable_qdec_interrupt(Tc *p_tc, uint32_t ul_sources) {
  /* Validate inputs. */
  Assert(p_tc);

  p_tc->TC_QIDR = ul_sources;
}

/**
 * \brief Read TC QDEC interrupt mask.
 *
 * \note This function is not available on SAM4L or SAMG devices.
 *
 * \param[in] p_tc Module hardware register base address pointer
 *
 * \return The QDEC interrupt mask value.
 */
uint32_t tc_get_qdec_interrupt_mask(Tc *p_tc) {
  /* Validate inputs. */
  Assert(p_tc);

  return p_tc->TC_QIMR;
}

/**
 * \brief Get current TC QDEC interrupt status.
 *
 * \note This function is not available on SAM4L or SAMG devices.
 *
 * \param[in] p_tc Module hardware register base address pointer
 *
 * \return The TC QDEC interrupt status.
 */
uint32_t tc_get_qdec_interrupt_status(Tc *p_tc) {
  /* Validate inputs. */
  Assert(p_tc);

  return p_tc->TC_QISR;
}

#endif /* (!SAM4L && !SAMG) || defined(__DOXYGEN__) */

#if (!SAM3U) || defined(__DOXYGEN__)

/**
 * \brief Enable or disable write protection of TC registers.
 *
 * \note This function is not available on SAM3U devices.
 *
 * \param[out] p_tc     Module hardware register base address pointer
 * \param[in] ul_enable 1 to enable, 0 to disable
 */
void tc_set_writeprotect(Tc *p_tc, uint32_t ul_enable) {
  /* Validate inputs. */
  Assert(p_tc);

  if (ul_enable) {
    p_tc->TC_WPMR = TC_WPMR_WPKEY_PASSWD | TC_WPMR_WPEN;
  } else {
    p_tc->TC_WPMR = TC_WPMR_WPKEY_PASSWD;
  }
}

#endif /* (!SAM3U) || defined(__DOXYGEN__) */

#if SAM4L || defined(__DOXYGEN__)

/**
 * \brief Indicate TC features.
 *
 * \note This function is only available on SAM4L devices.
 *
 * \param[in] p_tc Module hardware register base address pointer
 *
 * \return The TC FEATURES register contents.
 */
uint32_t tc_get_feature(Tc *p_tc) {
  /* Validate inputs. */
  Assert(p_tc);

  return p_tc->TC_FEATURES;
}

/**
 * \brief Indicate TC version.
 *
 * \note This function is only available on SAM4L devices.
 *
 * \param[in] p_tc Module hardware register base address pointer
 *
 * \return The TC VERSION register contents.
 */
uint32_t tc_get_version(Tc *p_tc) {
  /* Validate inputs. */
  Assert(p_tc);

  return p_tc->TC_VERSION;
}

#endif /* SAM4L || defined(__DOXYGEN__) */

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
