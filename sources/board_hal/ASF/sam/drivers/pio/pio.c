/**
 * \file
 *
 * \brief Parallel Input/Output (PIO) Controller driver for SAM.
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

#include "pio.h"
#include "component/pio.h"

/**
 * \defgroup sam_drivers_pio_group Peripheral Parallel Input/Output (PIO)
 * Controller
 *
 * \par Purpose
 *
 * The Parallel Input/Output Controller (PIO) manages up to 32 fully
 * programmable input/output lines. Each I/O line may be dedicated as a
 * general-purpose I/O or be assigned to a function of an embedded peripheral.
 * This assures effective optimization of the pins of a product.
 *
 * @{
 */

/**
 * \brief Configure IO of a PIO controller as being controlled by a specific
 * peripheral.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_type PIO type.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
void pio_set_peripheral(Pio *p_pio, const pio_type_t ul_type,
                        const uint32_t ul_mask) {
  uint32_t ul_sr;

  /* Disable interrupts on the pin(s) */
  p_pio->PIO_IDR = ul_mask;

#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP ||   \
     SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
  switch (ul_type) {
  case PIO_PERIPH_A:
    ul_sr = p_pio->PIO_ABCDSR[0];
    p_pio->PIO_ABCDSR[0] &= (~ul_mask & ul_sr);

    ul_sr = p_pio->PIO_ABCDSR[1];
    p_pio->PIO_ABCDSR[1] &= (~ul_mask & ul_sr);
    break;
  case PIO_PERIPH_B:
    ul_sr = p_pio->PIO_ABCDSR[0];
    p_pio->PIO_ABCDSR[0] = (ul_mask | ul_sr);

    ul_sr = p_pio->PIO_ABCDSR[1];
    p_pio->PIO_ABCDSR[1] &= (~ul_mask & ul_sr);
    break;
#if (!SAMG)
  case PIO_PERIPH_C:
    ul_sr = p_pio->PIO_ABCDSR[0];
    p_pio->PIO_ABCDSR[0] &= (~ul_mask & ul_sr);

    ul_sr = p_pio->PIO_ABCDSR[1];
    p_pio->PIO_ABCDSR[1] = (ul_mask | ul_sr);
    break;
  case PIO_PERIPH_D:
    ul_sr = p_pio->PIO_ABCDSR[0];
    p_pio->PIO_ABCDSR[0] = (ul_mask | ul_sr);

    ul_sr = p_pio->PIO_ABCDSR[1];
    p_pio->PIO_ABCDSR[1] = (ul_mask | ul_sr);
    break;
#endif
    /* Other types are invalid in this function */
  case PIO_INPUT:
  case PIO_OUTPUT_0:
  case PIO_OUTPUT_1:
  case PIO_NOT_A_PIN:
    return;
  }
#elif (SAM3XA || SAM3U)
  switch (ul_type) {
  case PIO_PERIPH_A:
    ul_sr = p_pio->PIO_ABSR;
    p_pio->PIO_ABSR &= (~ul_mask & ul_sr);
    break;

  case PIO_PERIPH_B:
    ul_sr = p_pio->PIO_ABSR;
    p_pio->PIO_ABSR = (ul_mask | ul_sr);
    break;

    // other types are invalid in this function
  case PIO_INPUT:
  case PIO_OUTPUT_0:
  case PIO_OUTPUT_1:
  case PIO_NOT_A_PIN:
    return;
  }
#else
#error "Unsupported device"
#endif

  /* Remove the pins from under the control of PIO */
  p_pio->PIO_PDR = ul_mask;
}

/**
 * \brief Configure one or more pin(s) or a PIO controller as inputs.
 * Optionally, the corresponding internal pull-up(s) and glitch filter(s) can
 * be enabled.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask indicating which pin(s) to configure as input(s).
 * \param ul_attribute PIO attribute(s).
 */
void pio_set_input(Pio *p_pio, const uint32_t ul_mask,
                   const uint32_t ul_attribute) {
  pio_disable_interrupt(p_pio, ul_mask);
  pio_pull_up(p_pio, ul_mask, ul_attribute & PIO_PULLUP);

  /* Enable Input Filter if necessary */
  if (ul_attribute & (PIO_DEGLITCH | PIO_DEBOUNCE)) {
    p_pio->PIO_IFER = ul_mask;
  } else {
    p_pio->PIO_IFDR = ul_mask;
  }

#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP ||   \
     SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
  /* Enable de-glitch or de-bounce if necessary */
  if (ul_attribute & PIO_DEGLITCH) {
    p_pio->PIO_IFSCDR = ul_mask;
  } else {
    if (ul_attribute & PIO_DEBOUNCE) {
      p_pio->PIO_IFSCER = ul_mask;
    }
  }
#elif (SAM3XA || SAM3U)
  /* Enable de-glitch or de-bounce if necessary */
  if (ul_attribute & PIO_DEGLITCH) {
    p_pio->PIO_SCIFSR = ul_mask;
  } else {
    if (ul_attribute & PIO_DEBOUNCE) {
      p_pio->PIO_DIFSR = ul_mask;
    }
  }
#else
#error "Unsupported device"
#endif

  /* Configure pin as input */
  p_pio->PIO_ODR = ul_mask;
  p_pio->PIO_PER = ul_mask;
}

/**
 * \brief Configure one or more pin(s) of a PIO controller as outputs, with
 * the given default value. Optionally, the multi-drive feature can be enabled
 * on the pin(s).
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask indicating which pin(s) to configure.
 * \param ul_default_level Default level on the pin(s).
 * \param ul_multidrive_enable Indicates if the pin(s) shall be configured as
 * open-drain.
 * \param ul_pull_up_enable Indicates if the pin shall have its pull-up
 * activated.
 */
void pio_set_output(Pio *p_pio, const uint32_t ul_mask,
                    const uint32_t ul_default_level,
                    const uint32_t ul_multidrive_enable,
                    const uint32_t ul_pull_up_enable) {
  pio_disable_interrupt(p_pio, ul_mask);
  pio_pull_up(p_pio, ul_mask, ul_pull_up_enable);

  /* Enable multi-drive if necessary */
  if (ul_multidrive_enable) {
    p_pio->PIO_MDER = ul_mask;
  } else {
    p_pio->PIO_MDDR = ul_mask;
  }

  /* Set default value */
  if (ul_default_level) {
    p_pio->PIO_SODR = ul_mask;
  } else {
    p_pio->PIO_CODR = ul_mask;
  }

  /* Configure pin(s) as output(s) */
  p_pio->PIO_OER = ul_mask;
  p_pio->PIO_PER = ul_mask;
}

/**
 * \brief Perform complete pin(s) configuration; general attributes and PIO init
 * if necessary.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_type PIO type.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_attribute Pins attributes.
 *
 * \return Whether the pin(s) have been configured properly.
 */
uint32_t pio_configure(Pio *p_pio, const pio_type_t ul_type,
                       const uint32_t ul_mask, const uint32_t ul_attribute) {
  /* Configure pins */
  switch (ul_type) {
  case PIO_PERIPH_A:
  case PIO_PERIPH_B:
#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CP || SAM4CM || \
     SAMV71 || SAMV70 || SAME70 || SAMS70)
  case PIO_PERIPH_C:
  case PIO_PERIPH_D:
#endif
    pio_set_peripheral(p_pio, ul_type, ul_mask);
    pio_pull_up(p_pio, ul_mask, (ul_attribute & PIO_PULLUP));
    break;

  case PIO_INPUT:
    pio_set_input(p_pio, ul_mask, ul_attribute);
    break;

  case PIO_OUTPUT_0:
  case PIO_OUTPUT_1:
    pio_set_output(p_pio, ul_mask, (ul_type == PIO_OUTPUT_1),
                   (ul_attribute & PIO_OPENDRAIN) ? 1 : 0,
                   (ul_attribute & PIO_PULLUP) ? 1 : 0);
    break;

  default:
    return 0;
  }

  return 1;
}

/**
 * \brief Configure the given interrupt source.
 * Interrupt can be configured to trigger on rising edge, falling edge,
 * high level, low level or simply on level change.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Interrupt source bit map.
 * \param ul_attr Interrupt source attributes.
 */
void pio_configure_interrupt(Pio *p_pio, const uint32_t ul_mask,
                             const uint32_t ul_attr) {
  /* Configure additional interrupt mode registers. */
  if (ul_attr & PIO_IT_AIME) {
    /* Enable additional interrupt mode. */
    p_pio->PIO_AIMER = ul_mask;

    /* If bit field of the selected pin is 1, set as
       Rising Edge/High level detection event. */
    if (ul_attr & PIO_IT_RE_OR_HL) {
      /* Rising Edge or High Level */
      p_pio->PIO_REHLSR = ul_mask;
    } else {
      /* Falling Edge or Low Level */
      p_pio->PIO_FELLSR = ul_mask;
    }

    /* If bit field of the selected pin is 1, set as
       edge detection source. */
    if (ul_attr & PIO_IT_EDGE) {
      /* Edge select */
      p_pio->PIO_ESR = ul_mask;
    } else {
      /* Level select */
      p_pio->PIO_LSR = ul_mask;
    }
  } else {
    /* Disable additional interrupt mode. */
    p_pio->PIO_AIMDR = ul_mask;
  }
}

/**
 * \brief Set additional interrupt mode.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Interrupt sources bit map.
 * \param ul_attribute Pin(s) attributes.
 */
void pio_set_additional_interrupt_mode(Pio *p_pio, const uint32_t ul_mask,
                                       const uint32_t ul_attribute) {
  /* Enables additional interrupt mode if needed */
  if (ul_attribute & PIO_IT_AIME) {
    /* Enables additional interrupt mode */
    p_pio->PIO_AIMER = ul_mask;

    /* Configures the Polarity of the event detection */
    /* (Rising/Falling Edge or High/Low Level) */
    if (ul_attribute & PIO_IT_RE_OR_HL) {
      /* Rising Edge or High Level */
      p_pio->PIO_REHLSR = ul_mask;
    } else {
      /* Falling Edge or Low Level */
      p_pio->PIO_FELLSR = ul_mask;
    }

    /* Configures the type of event detection (Edge or Level) */
    if (ul_attribute & PIO_IT_EDGE) {
      /* Edge select */
      p_pio->PIO_ESR = ul_mask;
    } else {
      /* Level select */
      p_pio->PIO_LSR = ul_mask;
    }
  } else {
    /* Disable additional interrupt mode */
    p_pio->PIO_AIMDR = ul_mask;
  }
}

/**
 * \brief Perform complete pin(s) configuration; general attributes and PIO init
 * if necessary.
 *
 * \param ul_pin The pin index.
 * \param ul_flags Pins attributes.
 *
 * \return Whether the pin(s) have been configured properly.
 */
uint32_t pio_configure_pin(uint32_t ul_pin, const uint32_t ul_flags) {
  Pio *p_pio = pio_get_pin_group(ul_pin);

  /* Configure pins */
  switch (ul_flags & PIO_TYPE_Msk) {
  case PIO_TYPE_PIO_PERIPH_A:
    pio_set_peripheral(p_pio, PIO_PERIPH_A, (1 << (ul_pin & 0x1F)));
    pio_pull_up(p_pio, (1 << (ul_pin & 0x1F)), (ul_flags & PIO_PULLUP));
    break;
  case PIO_TYPE_PIO_PERIPH_B:
    pio_set_peripheral(p_pio, PIO_PERIPH_B, (1 << (ul_pin & 0x1F)));
    pio_pull_up(p_pio, (1 << (ul_pin & 0x1F)), (ul_flags & PIO_PULLUP));
    break;
#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CP || SAM4CM || \
     SAMV71 || SAMV70 || SAME70 || SAMS70)
  case PIO_TYPE_PIO_PERIPH_C:
    pio_set_peripheral(p_pio, PIO_PERIPH_C, (1 << (ul_pin & 0x1F)));
    pio_pull_up(p_pio, (1 << (ul_pin & 0x1F)), (ul_flags & PIO_PULLUP));
    break;
  case PIO_TYPE_PIO_PERIPH_D:
    pio_set_peripheral(p_pio, PIO_PERIPH_D, (1 << (ul_pin & 0x1F)));
    pio_pull_up(p_pio, (1 << (ul_pin & 0x1F)), (ul_flags & PIO_PULLUP));
    break;
#endif

  case PIO_TYPE_PIO_INPUT:
    pio_set_input(p_pio, (1 << (ul_pin & 0x1F)), ul_flags);
    break;

  case PIO_TYPE_PIO_OUTPUT_0:
  case PIO_TYPE_PIO_OUTPUT_1:
    pio_set_output(
        p_pio, (1 << (ul_pin & 0x1F)),
        ((ul_flags & PIO_TYPE_PIO_OUTPUT_1) == PIO_TYPE_PIO_OUTPUT_1) ? 1 : 0,
        (ul_flags & PIO_OPENDRAIN) ? 1 : 0, (ul_flags & PIO_PULLUP) ? 1 : 0);
    break;

  default:
    return 0;
  }

  return 1;
}

/**
 * \brief Perform complete pin(s) configuration; general attributes and PIO init
 * if necessary.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_flags Pin(s) attributes.
 *
 * \return Whether the pin(s) have been configured properly.
 */
uint32_t pio_configure_pin_group(Pio *p_pio, uint32_t ul_mask,
                                 const uint32_t ul_flags) {
  /* Configure pins */
  switch (ul_flags & PIO_TYPE_Msk) {
  case PIO_TYPE_PIO_PERIPH_A:
    pio_set_peripheral(p_pio, PIO_PERIPH_A, ul_mask);
    pio_pull_up(p_pio, ul_mask, (ul_flags & PIO_PULLUP));
    break;
  case PIO_TYPE_PIO_PERIPH_B:
    pio_set_peripheral(p_pio, PIO_PERIPH_B, ul_mask);
    pio_pull_up(p_pio, ul_mask, (ul_flags & PIO_PULLUP));
    break;
#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CP || SAM4CM || \
     SAMV71 || SAMV70 || SAME70 || SAMS70)
  case PIO_TYPE_PIO_PERIPH_C:
    pio_set_peripheral(p_pio, PIO_PERIPH_C, ul_mask);
    pio_pull_up(p_pio, ul_mask, (ul_flags & PIO_PULLUP));
    break;
  case PIO_TYPE_PIO_PERIPH_D:
    pio_set_peripheral(p_pio, PIO_PERIPH_D, ul_mask);
    pio_pull_up(p_pio, ul_mask, (ul_flags & PIO_PULLUP));
    break;
#endif

  case PIO_TYPE_PIO_INPUT:
    pio_set_input(p_pio, ul_mask, ul_flags);
    break;

  case PIO_TYPE_PIO_OUTPUT_0:
  case PIO_TYPE_PIO_OUTPUT_1:
    pio_set_output(
        p_pio, ul_mask,
        ((ul_flags & PIO_TYPE_PIO_OUTPUT_1) == PIO_TYPE_PIO_OUTPUT_1) ? 1 : 0,
        (ul_flags & PIO_OPENDRAIN) ? 1 : 0, (ul_flags & PIO_PULLUP) ? 1 : 0);
    break;

  default:
    return 0;
  }

  return 1;
}

#if (SAM3S || SAM4S || SAM4E || SAMV71 || SAMV70 || SAME70 || SAMS70)
/* Capture mode enable flag */
uint32_t pio_capture_enable_flag;

/**
 * \brief Configure PIO capture mode.
 * \note PIO capture mode will be disabled automatically.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mode Bitmask of one or more modes.
 */
void pio_capture_set_mode(Pio *p_pio, uint32_t ul_mode) {
  ul_mode &= (~PIO_PCMR_PCEN); /* Disable PIO capture mode */
  p_pio->PIO_PCMR = ul_mode;
}

/**
 * \brief Enable PIO capture mode.
 *
 * \param p_pio Pointer to a PIO instance.
 */
void pio_capture_enable(Pio *p_pio) {
  p_pio->PIO_PCMR |= PIO_PCMR_PCEN;
  pio_capture_enable_flag = true;
}

/**
 * \brief Disable PIO capture mode.
 *
 * \param p_pio Pointer to a PIO instance.
 */
void pio_capture_disable(Pio *p_pio) {
  p_pio->PIO_PCMR &= (~PIO_PCMR_PCEN);
  pio_capture_enable_flag = false;
}

/**
 * \brief Read from Capture Reception Holding Register.
 * \note Data presence should be tested before any read attempt.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param pul_data Pointer to store the data.
 *
 * \retval 0 Success.
 * \retval 1 I/O Failure, Capture data is not ready.
 */
uint32_t pio_capture_read(const Pio *p_pio, uint32_t *pul_data) {
  /* Check if the data is ready */
  if ((p_pio->PIO_PCISR & PIO_PCISR_DRDY) == 0) {
    return 1;
  }

  /* Read data */
  *pul_data = p_pio->PIO_PCRHR;
  return 0;
}

/**
 * \brief Enable the given interrupt source of PIO capture. The status
 * register of the corresponding PIO capture controller is cleared prior
 * to enabling the interrupt.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Interrupt sources bit map.
 */
void pio_capture_enable_interrupt(Pio *p_pio, const uint32_t ul_mask) {
  p_pio->PIO_PCISR;
  p_pio->PIO_PCIER = ul_mask;
}

/**
 * \brief Disable a given interrupt source of PIO capture.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Interrupt sources bit map.
 */
void pio_capture_disable_interrupt(Pio *p_pio, const uint32_t ul_mask) {
  p_pio->PIO_PCIDR = ul_mask;
}

/**
 * \brief Read PIO interrupt status of PIO capture.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return The interrupt status mask value.
 */
uint32_t pio_capture_get_interrupt_status(const Pio *p_pio) {
  return p_pio->PIO_PCISR;
}

/**
 * \brief Read PIO interrupt mask of PIO capture.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return The interrupt mask value.
 */
uint32_t pio_capture_get_interrupt_mask(const Pio *p_pio) {
  return p_pio->PIO_PCIMR;
}
#if !(SAMV71 || SAMV70 || SAME70 || SAMS70)
/**
 * \brief Get PDC registers base address.
 *
 * \param p_pio Pointer to an PIO peripheral.
 *
 * \return PIOA PDC register base address.
 */
Pdc *pio_capture_get_pdc_base(const Pio *p_pio) {
  UNUSED(p_pio); /* Stop warning */
  return PDC_PIOA;
}
#endif
#endif

//@}
