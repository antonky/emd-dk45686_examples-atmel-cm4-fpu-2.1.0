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
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef PIO_H_INCLUDED
#define PIO_H_INCLUDED

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Compute PIO register length */
#define PIO_DELTA   ((uint32_t) PIOB - (uint32_t) PIOA)

/* GPIO Support */
#define PIO_TYPE_Pos                  27
/* PIO Type Mask */
#define PIO_TYPE_Msk                  (0xFu << PIO_TYPE_Pos)
/* The pin is not a function pin. */
#define PIO_TYPE_NOT_A_PIN            (0x0u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral A. */
#define PIO_TYPE_PIO_PERIPH_A         (0x1u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral B. */
#define PIO_TYPE_PIO_PERIPH_B         (0x2u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral C. */
#define PIO_TYPE_PIO_PERIPH_C         (0x3u << PIO_TYPE_Pos)
/* The pin is controlled by the peripheral D. */
#define PIO_TYPE_PIO_PERIPH_D         (0x4u << PIO_TYPE_Pos)
/* The pin is an input. */
#define PIO_TYPE_PIO_INPUT            (0x5u << PIO_TYPE_Pos)
/* The pin is an output and has a default level of 0. */
#define PIO_TYPE_PIO_OUTPUT_0         (0x6u << PIO_TYPE_Pos)
/* The pin is an output and has a default level of 1. */
#define PIO_TYPE_PIO_OUTPUT_1         (0x7u << PIO_TYPE_Pos)

typedef enum _pio_type {
	PIO_NOT_A_PIN   = PIO_TYPE_NOT_A_PIN,
	PIO_PERIPH_A    = PIO_TYPE_PIO_PERIPH_A,
	PIO_PERIPH_B    = PIO_TYPE_PIO_PERIPH_B,
#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
	PIO_PERIPH_C    = PIO_TYPE_PIO_PERIPH_C,
	PIO_PERIPH_D    = PIO_TYPE_PIO_PERIPH_D,
#endif
	PIO_INPUT       = PIO_TYPE_PIO_INPUT,
	PIO_OUTPUT_0    = PIO_TYPE_PIO_OUTPUT_0,
	PIO_OUTPUT_1    = PIO_TYPE_PIO_OUTPUT_1
} pio_type_t;

/*  Default pin configuration (no attribute). */
#define PIO_DEFAULT             (0u << 0)
/*  The internal pin pull-up is active. */
#define PIO_PULLUP              (1u << 0)
/*  The internal glitch filter is active. */
#define PIO_DEGLITCH            (1u << 1)
/*  The pin is open-drain. */
#define PIO_OPENDRAIN           (1u << 2)

/*  The internal debouncing filter is active. */
#define PIO_DEBOUNCE            (1u << 3)

/*  Enable additional interrupt modes. */
#define PIO_IT_AIME             (1u << 4)

/*  Interrupt High Level/Rising Edge detection is active. */
#define PIO_IT_RE_OR_HL         (1u << 5)
/*  Interrupt Edge detection is active. */
#define PIO_IT_EDGE             (1u << 6)

/*  Low level interrupt is active */
#define PIO_IT_LOW_LEVEL        (0               | 0 | PIO_IT_AIME)
/*  High level interrupt is active */
#define PIO_IT_HIGH_LEVEL       (PIO_IT_RE_OR_HL | 0 | PIO_IT_AIME)
/*  Falling edge interrupt is active */
#define PIO_IT_FALL_EDGE        (0               | PIO_IT_EDGE | PIO_IT_AIME)
/*  Rising edge interrupt is active */
#define PIO_IT_RISE_EDGE        (PIO_IT_RE_OR_HL | PIO_IT_EDGE | PIO_IT_AIME)

#ifndef FREQ_SLOW_CLOCK_EXT
/* External slow clock frequency (hz) */
#define FREQ_SLOW_CLOCK_EXT 32768
#endif

#ifndef PIO_WPMR_WPKEY_PASSWD
#  define PIO_WPMR_WPKEY_PASSWD PIO_WPMR_WPKEY(0x50494Fu)
#endif

/*
 *  The #attribute# field is a bitmask that can either be set to PIO_DEFAULT,
 *  or combine (using bitwise OR '|') any number of the following constants:
 *     - PIO_PULLUP
 *     - PIO_DEGLITCH
 *     - PIO_DEBOUNCE
 *     - PIO_OPENDRAIN
 *     - PIO_IT_LOW_LEVEL
 *     - PIO_IT_HIGH_LEVEL
 *     - PIO_IT_FALL_EDGE
 *     - PIO_IT_RISE_EDGE
 */

/**
 * \brief Return GPIO port for a GPIO pin.
 *
 * \param ul_pin The pin index.
 *
 * \return Pointer to \ref Pio struct for GPIO port.
 */
 __always_inline static Pio *pio_get_pin_group(uint32_t ul_pin)
{
	Pio *p_pio;

#if (SAM4C || SAM4CP)
#  ifdef ID_PIOD
	if (ul_pin > PIO_PC9_IDX) {
		p_pio = PIOD;
	} else if (ul_pin > PIO_PB31_IDX) {
#  else
	if  (ul_pin > PIO_PB31_IDX) {
#  endif
		p_pio = PIOC;
	} else {
		p_pio = (Pio *)((uint32_t)PIOA + (PIO_DELTA * (ul_pin >> 5)));
	}
#elif (SAM4CM)
	if (ul_pin > PIO_PB21_IDX) {
		p_pio = PIOC;
	} else {
		p_pio = (Pio *)((uint32_t)PIOA + (PIO_DELTA * (ul_pin >> 5)));
	}
#else
	p_pio = (Pio *)((uint32_t)PIOA + (PIO_DELTA * (ul_pin >> 5)));
#endif
	return p_pio;
}

/**
 * \brief Configure PIO internal pull-up.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_pull_up_enable Indicates if the pin(s) internal pull-up shall be
 * configured.
 */
 __always_inline static void pio_pull_up(Pio *p_pio, const uint32_t ul_mask,
		const uint32_t ul_pull_up_enable)
{
	/* Enable the pull-up(s) if necessary */
	if (ul_pull_up_enable) {
		p_pio->PIO_PUER = ul_mask;
	} else {
		p_pio->PIO_PUDR = ul_mask;
	}
}
		
/**
 * \brief Configure Glitch or Debouncing filter for the specified input(s).
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_cut_off Cuts off frequency for debouncing filter.
 */
 __always_inline static void pio_set_debounce_filter(Pio *p_pio, const uint32_t ul_mask,
		const uint32_t ul_cut_off)
{
#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
	/* Set Debouncing, 0 bit field no effect */
	p_pio->PIO_IFSCER = ul_mask;
#elif (SAM3XA || SAM3U)
	/* Set Debouncing, 0 bit field no effect */
	p_pio->PIO_DIFSR = ul_mask;
#else
#error "Unsupported device"
#endif

	/*
	 * The debouncing filter can filter a pulse of less than 1/2 Period of a
	 * programmable Divided Slow Clock:
	 * Tdiv_slclk = ((DIV+1)*2).Tslow_clock
	 */
	p_pio->PIO_SCDR = PIO_SCDR_DIV((FREQ_SLOW_CLOCK_EXT /
			(2 * (ul_cut_off))) - 1);
}

/**
 * \brief Set a high output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
 __always_inline static void pio_set(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_SODR = ul_mask;
}

/**
 * \brief Set a low output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
 __always_inline static void pio_clear(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_CODR = ul_mask;
}

/**
 * \brief Return 1 if one or more PIOs of the given Pin instance currently have
 * a high level; otherwise returns 0. This method returns the actual value that
 * is being read on the pin. To return the supposed output value of a pin, use
 * pio_get_output_data_status() instead.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_type PIO type.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 *
 * \retval 1 at least one PIO currently has a high level.
 * \retval 0 all PIOs have a low level.
 */
 __always_inline static uint32_t pio_get(Pio *p_pio, const pio_type_t ul_type,
		const uint32_t ul_mask)
{
	uint32_t ul_reg;

	if ((ul_type == PIO_OUTPUT_0) || (ul_type == PIO_OUTPUT_1)) {
		ul_reg = p_pio->PIO_ODSR;
	} else {
		ul_reg = p_pio->PIO_PDSR;
	}

	if ((ul_reg & ul_mask) == 0) {
		return 0;
	} else {
		return 1;
	}
}

void pio_set_peripheral(Pio *p_pio, const pio_type_t ul_type,
		const uint32_t ul_mask);
void pio_set_input(Pio *p_pio, const uint32_t ul_mask,
		const uint32_t ul_attribute);
void pio_set_output(Pio *p_pio, const uint32_t ul_mask,
		const uint32_t ul_default_level,
		const uint32_t ul_multidrive_enable,
		const uint32_t ul_pull_up_enable);
uint32_t pio_configure(Pio *p_pio, const pio_type_t ul_type,
		const uint32_t ul_mask, const uint32_t ul_attribute);

/**
 * \brief Return 1 if one or more PIOs of the given Pin are configured to
 * output a high level (even if they are not output).
 * To get the actual value of the pin, use PIO_Get() instead.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s).
 *
 * \retval 1 At least one PIO is configured to output a high level.
 * \retval 0 All PIOs are configured to output a low level.
 */
 __always_inline static uint32_t pio_get_output_data_status(const Pio *p_pio,
		const uint32_t ul_mask)
{
	if ((p_pio->PIO_ODSR & ul_mask) == 0) {
		return 0;
	} else {
		return 1;
	}
}

/**
 * \brief Configure PIO pin multi-driver.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_multi_driver_enable Indicates if the pin(s) multi-driver shall be
 * configured.
 */
 __always_inline static void pio_set_multi_driver(Pio *p_pio, const uint32_t ul_mask,
		const uint32_t ul_multi_driver_enable)
{
	/* Enable the multi-driver if necessary */
	if (ul_multi_driver_enable) {
		p_pio->PIO_MDER = ul_mask;
	} else {
		p_pio->PIO_MDDR = ul_mask;
	}
}

/**
 * \brief Get multi-driver status.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return The multi-driver mask value.
 */
 __always_inline static uint32_t pio_get_multi_driver_status(const Pio *p_pio)
{
	return p_pio->PIO_MDSR;
}

#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
/**
 * \brief Configure PIO pin internal pull-down.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_pull_down_enable Indicates if the pin(s) internal pull-down shall
 * be configured.
 */
 __always_inline static void pio_pull_down(Pio *p_pio, const uint32_t ul_mask,
		const uint32_t ul_pull_down_enable)
{
	/* Enable the pull-down if necessary */
	if (ul_pull_down_enable) {
		p_pio->PIO_PPDER = ul_mask;
	} else {
		p_pio->PIO_PPDDR = ul_mask;
	}
}
#endif

/**
 * \brief Enable PIO output write for synchronous data output.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
 __always_inline static void pio_enable_output_write(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_OWER = ul_mask;
}

/**
 * \brief Disable PIO output write.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
 __always_inline static void pio_disable_output_write(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_OWDR = ul_mask;
}

/**
 * \brief Read PIO output write status.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return The output write mask value.
 */
 __always_inline static uint32_t pio_get_output_write_status(const Pio *p_pio)
{
	return p_pio->PIO_OWSR;
}

/**
 * \brief Synchronously write on output pins.
 * \note Only bits unmasked by PIO_OWSR (Output Write Status Register) are
 * written.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
 __always_inline static void pio_sync_output_write(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_ODSR = ul_mask;
}

#if (SAM3S || SAM3N || SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAME70 || SAMS70)
/**
 * \brief Configure PIO pin schmitt trigger. By default the Schmitt trigger is
 * active.
 * Disabling the Schmitt Trigger is requested when using the QTouch Library.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
 __always_inline static void pio_set_schmitt_trigger(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_SCHMITT = ul_mask;
}

/**
 * \brief Get PIO pin schmitt trigger status.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return The schmitt trigger mask value.
 */
 __always_inline static uint32_t pio_get_schmitt_trigger(const Pio *p_pio)
{
	return p_pio->PIO_SCHMITT;
}
#endif

void pio_configure_interrupt(Pio *p_pio, const uint32_t ul_mask,
		const uint32_t ul_attr);

/**
 * \brief Enable the given interrupt source.
 * The PIO must be configured as an NVIC interrupt source as well.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Interrupt sources bit map.
 */
 __always_inline static void pio_enable_interrupt(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_IER = ul_mask;
}

/**
 * \brief Disable a given interrupt source, with no added side effects.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Interrupt sources bit map.
 */
 __always_inline static void pio_disable_interrupt(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_IDR = ul_mask;
}

/**
 * \brief Read and clear PIO interrupt status.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return The interrupt status value.
 */
 __always_inline static uint32_t pio_get_interrupt_status(const Pio *p_pio)
{
	return p_pio->PIO_ISR;
}

/**
 * \brief Read PIO interrupt mask.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return The interrupt mask value.
 */
 __always_inline static uint32_t pio_get_interrupt_mask(const Pio *p_pio)
{
	return p_pio->PIO_IMR;
}

void pio_set_additional_interrupt_mode(Pio *p_pio,
		const uint32_t ul_mask, const uint32_t ul_attribute);

/**
 * \brief Enable or disable write protect of PIO registers.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_enable 1 to enable, 0 to disable.
 */
 __always_inline static void pio_set_writeprotect(Pio *p_pio, const uint32_t ul_enable)
{
	p_pio->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD | (ul_enable & PIO_WPMR_WPEN);
}

/**
 * \brief Read write protect status.
 *
 * \param p_pio Pointer to a PIO instance.
 *
 * \return Return write protect status.
 */
 __always_inline static uint32_t pio_get_writeprotect_status(const Pio *p_pio)
{
	return p_pio->PIO_WPSR;
}

#if (SAM3S || SAM4S || SAM4E || SAMV71 || SAMV70 || SAME70 || SAMS70)
void pio_capture_set_mode(Pio *p_pio, uint32_t ul_mode);
void pio_capture_enable(Pio *p_pio);
void pio_capture_disable(Pio *p_pio);
uint32_t pio_capture_read(const Pio *p_pio, uint32_t * pul_data);
void pio_capture_enable_interrupt(Pio *p_pio, const uint32_t ul_mask);
void pio_capture_disable_interrupt(Pio * p_pio, const uint32_t ul_mask);
uint32_t pio_capture_get_interrupt_status(const Pio *p_pio);
uint32_t pio_capture_get_interrupt_mask(const Pio *p_pio);
#if !(SAMV71 || SAMV70 || SAME70 || SAMS70)
Pdc *pio_capture_get_pdc_base(const Pio *p_pio);
#endif
#endif

/* GPIO Support */


/**
 * \brief Return the value of a pin.
 *
 * \param ul_pin The pin number.
 *
 * \return The pin value.
 *
 * \note If pin is output: a pull-up or pull-down could hide the actual value.
 *       The function \ref pio_get can be called to get the actual pin output
 *       level.
 * \note If pin is input: PIOx must be clocked to sample the signal.
 *       See PMC driver.
 */
 __always_inline static uint32_t pio_get_pin_value(uint32_t ul_pin)
{
	Pio *p_pio = pio_get_pin_group(ul_pin);

	return (p_pio->PIO_PDSR >> (ul_pin & 0x1F)) & 1;
}

/**
 * \brief Drive a GPIO pin to 1.
 *
 * \param ul_pin The pin index.
 *
 * \note The function \ref pio_configure_pin must be called beforehand.
 */
__always_inline static void pio_set_pin_high(uint32_t ul_pin)
{
	Pio *p_pio = pio_get_pin_group(ul_pin);

	/* Value to be driven on the I/O line: 1. */
	p_pio->PIO_SODR = 1 << (ul_pin & 0x1F);
}

/**
 * \brief Drive a GPIO pin to 0.
 *
 * \param ul_pin The pin index.
 *
 * \note The function \ref pio_configure_pin must be called before.
 */
__always_inline static void pio_set_pin_low(uint32_t ul_pin)
{
	Pio *p_pio = pio_get_pin_group(ul_pin);

	/* Value to be driven on the I/O line: 0. */
	p_pio->PIO_CODR = 1 << (ul_pin & 0x1F);
}

/**
 * \brief Toggle a GPIO pin.
 *
 * \param ul_pin The pin index.
 *
 * \note The function \ref pio_configure_pin must be called before.
 */
__always_inline static void pio_toggle_pin(uint32_t ul_pin)
{
	Pio *p_pio = pio_get_pin_group(ul_pin);

	if (p_pio->PIO_ODSR & (1 << (ul_pin & 0x1F))) {
		/* Value to be driven on the I/O line: 0. */
		p_pio->PIO_CODR = 1 << (ul_pin & 0x1F);
	} else {
		/* Value to be driven on the I/O line: 1. */
		p_pio->PIO_SODR = 1 << (ul_pin & 0x1F);
	}
}

/**
 * \brief Enable interrupt for a GPIO pin.
 *
 * \param ul_pin The pin index.
 *
 * \note The function \ref gpio_configure_pin must be called before.
 */
__always_inline static void pio_enable_pin_interrupt(uint32_t ul_pin)
{
	Pio *p_pio = pio_get_pin_group(ul_pin);

	p_pio->PIO_IER = 1 << (ul_pin & 0x1F);
}

/**
 * \brief Disable interrupt for a GPIO pin.
 *
 * \param ul_pin The pin index.
 *
 * \note The function \ref gpio_configure_pin must be called before.
 */
__always_inline static void pio_disable_pin_interrupt(uint32_t ul_pin)
{
	Pio *p_pio = pio_get_pin_group(ul_pin);

	p_pio->PIO_IDR = 1 << (ul_pin & 0x1F);
}

/**
 * \brief Return GPIO port peripheral ID for a GPIO pin.
 *
 * \param ul_pin The pin index.
 *
 * \return GPIO port peripheral ID.
 */
__always_inline static uint32_t pio_get_pin_group_id(uint32_t ul_pin)
{
	uint32_t ul_id;

#if (SAM4C || SAM4CP)
#  ifdef ID_PIOD
	if (ul_pin > PIO_PC9_IDX) {
		ul_id = ID_PIOD;
	} else if (ul_pin > PIO_PB31_IDX) {
#  else
	if (ul_pin > PIO_PB31_IDX) {
#  endif
		ul_id = ID_PIOC;
	} else {
		ul_id = ID_PIOA + (ul_pin >> 5);
	}
#elif (SAM4CM)
	if (ul_pin > PIO_PB21_IDX) {
		ul_id = ID_PIOC;
	} else {
		ul_id = ID_PIOA + (ul_pin >> 5);
	}
#elif (SAMV70 || SAMV71 || SAME70 || SAMS70)
	ul_id = ID_PIOA + (ul_pin >> 5);

	#ifdef ID_PIOD 
	if (ul_pin >= PIO_PD0_IDX) ul_id = ID_PIOD; 
	#endif
	
	#ifdef ID_PIOE 
	if (ul_pin >= PIO_PE0_IDX) ul_id = ID_PIOE; 
	#endif 
#else
	ul_id = ID_PIOA + (ul_pin >> 5);
#endif
	return ul_id;
}

/**
 * \brief Return GPIO port pin mask for a GPIO pin.
 *
 * \param ul_pin The pin index.
 *
 * \return GPIO port pin mask.
 */
__always_inline static uint32_t pio_get_pin_group_mask(uint32_t ul_pin)
{
	uint32_t ul_mask = 1 << (ul_pin & 0x1F);
	return ul_mask;
}

uint32_t pio_configure_pin(uint32_t ul_pin, const uint32_t ul_flags);

/**
 * \brief Drive a GPIO port to 1.
 *
 * \param p_pio Base address of the PIO port.
 * \param ul_mask Bitmask of one or more pin(s) to toggle.
 */
__always_inline static void pio_set_pin_group_high(Pio *p_pio, uint32_t ul_mask)
{
	/* Value to be driven on the I/O line: 1. */
	p_pio->PIO_SODR = ul_mask;
}

/**
 * \brief Drive a GPIO port to 0.
 *
 * \param p_pio Base address of the PIO port.
 * \param ul_mask Bitmask of one or more pin(s) to toggle.
 */
__always_inline static void pio_set_pin_group_low(Pio *p_pio, uint32_t ul_mask)
{
	/* Value to be driven on the I/O line: 0. */
	p_pio->PIO_CODR = ul_mask;
}

/**
 * \brief Toggle a GPIO group.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
__always_inline static void pio_toggle_pin_group(Pio *p_pio, uint32_t ul_mask)
{
	if (p_pio->PIO_ODSR & ul_mask) {
		/* Value to be driven on the I/O line: 0. */
		p_pio->PIO_CODR = ul_mask;
	} else {
		/* Value to be driven on the I/O line: 1. */
		p_pio->PIO_SODR = ul_mask;
	}
}

uint32_t pio_configure_pin_group(Pio *p_pio, uint32_t ul_mask,
		const uint32_t ul_flags);

#if (SAM4C || SAM4CP || SAM4CM || SAMG55 || SAMV71 || SAMV70 || SAME70 || SAMS70)
enum pio_io_drive_mode {
	PIO_IO_DRIVE_LOW = 0,
	PIO_IO_DRIVE_HIGH,
};

/**
 * \brief Set PIO IO drive.
 *
 * \param p_pio Pointer to an PIO peripheral.
 * \param ul_line Line index (0..31).
 * \param mode IO drive mode.
 */
__always_inline static void pio_set_io_drive(Pio *p_pio, uint32_t ul_line,
		enum pio_io_drive_mode mode)
{
	p_pio->PIO_DRIVER &= ~(1 << ul_line);
	p_pio->PIO_DRIVER |= mode << ul_line;
}
#endif

#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
void pio_keypad_enable(Pio *p_pio);
void pio_keypad_disable(Pio *p_pio);
void pio_keypad_set_row_num(Pio *p_pio, uint8_t num);
uint8_t pio_keypad_get_row_num(const Pio *p_pio);
void pio_keypad_set_column_num(Pio *p_pio, uint8_t num);
uint8_t pio_keypad_get_column_num(const Pio *p_pio);
void pio_keypad_set_debouncing_value(Pio *p_pio, uint16_t value);
uint16_t pio_keypad_get_debouncing_value(const Pio *p_pio);
void pio_keypad_enable_interrupt(Pio *p_pio, uint32_t ul_mask);
void pio_keypad_disable_interrupt(Pio *p_pio, uint32_t ul_mask);
uint32_t pio_keypad_get_interrupt_mask(const Pio *p_pio);
uint32_t pio_keypad_get_press_status(const Pio *p_pio);
uint32_t pio_keypad_get_release_status(const Pio *p_pio);
uint8_t pio_keypad_get_simult_press_num(const Pio *p_pio);
uint8_t pio_keypad_get_simult_release_num(const Pio *p_pio);
uint8_t pio_keypad_get_press_row_index(const Pio *p_pio, uint8_t queue);
uint8_t pio_keypad_get_press_column_index(const Pio *p_pio, uint8_t queue);
uint8_t pio_keypad_get_release_row_index(const Pio *p_pio, uint8_t queue);
uint8_t pio_keypad_get_release_column_index(const Pio *p_pio, uint8_t queue);
#endif
/**
 * \page sam_pio_quickstart Quick Start Guide for the SAM PIO driver
 *
 * This is the quick start guide for the \ref sam_drivers_pio_group "PIO Driver",
 * with step-by-step instructions on how to configure and use the driver for
 * specific use cases.
 *
 * The section described below can be compiled into e.g. the main application
 * loop or any other function that will need to interface with the IO port.
 *
 * \section sam_pio_usecases PIO use cases
 * - \ref sam_pio_quickstart_basic
 * - \ref sam_pio_quickstart_use_case_2
 *
 * \section sam_pio_quickstart_basic Basic usage of the PIO driver
 * This section will present a basic use case for the PIO driver. This use case
 * will configure pin 23 on port A as output and pin 16 as an input with pullup,
 * and then toggle the output pin's value to match that of the input pin.
 *
 * \subsection sam_pio_quickstart_use_case_1_prereq Prerequisites
 *  - \ref group_pmc "Power Management Controller driver"
 *
 * \subsection sam_pio_quickstart_use_case_1_setup_steps Initialization code
 * Add to the application initialization code:
 * \code
	    pmc_enable_periph_clk(ID_PIOA);

	    pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE);
	    pio_set_input(PIOA, PIO_PA16, PIO_PULLUP);
\endcode
 *
 * \subsection sam_pio_quickstart_use_case_1_setup_steps_workflow Workflow
 * -# Enable the module clock to the PIOA peripheral:
 *    \code pmc_enable_periph_clk(ID_PIOA); \endcode
 * -# Set pin 23 direction on PIOA as output, default low level:
 *     \code pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE); \endcode
 * -# Set pin 16 direction on PIOA as input, with pullup:
 *     \code pio_set_input(PIOA, PIO_PA16, PIO_PULLUP); \endcode
 *
 * \subsection sam_pio_quickstart_use_case_1_example_code Example code
 *   Set the state of output pin 23 to match input pin 16:
 *   \code
	if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA16))
	    pio_clear(PIOA, PIO_PA23);
	else
	    pio_set(PIOA, PIO_PA23);
\endcode
 *
 * \subsection sam_pio_quickstart_use_case_1_example_workflow Workflow
 * -# We check the value of the pin:
 *     \code
	if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA16))
\endcode
 * -# Then we set the new output value based on the read pin value:
 *     \code
	    pio_clear(PIOA, PIO_PA23);
	else
	    pio_set(PIOA, PIO_PA23);
\endcode
 */

/**
 * \page sam_pio_quickstart_use_case_2 Advanced use case - Interrupt driven edge detection
 *
 * \section sam_pio_quickstart_use_case_2 Advanced Use Case 1
 * This section will present a more advanced use case for the PIO driver. This use case
 * will configure pin 23 on port A as output and pin 16 as an input with pullup,
 * and then toggle the output pin's value to match that of the input pin using the interrupt
 * controller within the device.
 *
 * \subsection sam_pio_quickstart_use_case_2_prereq Prerequisites
 *  - \ref group_pmc "Power Management Controller driver"
 *
 * \subsection sam_pio_quickstart_use_case_2_setup_steps Initialization code
 * Add to the application initialization code:
 * \code
	 pmc_enable_periph_clk(ID_PIOA);

	 pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE);
	 pio_set_input(PIOA, PIO_PA16, PIO_PULLUP);

	 pio_handler_set(PIOA, ID_PIOA, PIO_PA16, PIO_IT_EDGE, pin_edge_handler);
	 pio_enable_interrupt(PIOA, PIO_PA16);

	 NVIC_EnableIRQ(PIOA_IRQn);
\endcode
 *
 * \subsection sam_pio_quickstart_use_case_2_setup_steps_workflow Workflow
 * -# Enable the module clock to the PIOA peripheral:
 *    \code pmc_enable_periph_clk(ID_PIOA); \endcode
 * -# Set pin 23 direction on PIOA as output, default low level:
 *     \code pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE); \endcode
 * -# Set pin 16 direction on PIOA as input, with pullup:
 *     \code pio_set_input(PIOA, PIO_PA16, PIO_PULLUP); \endcode
 * -# Configure the input pin 16 interrupt mode and handler:
 *     \code pio_handler_set(PIOA, ID_PIOA, PIO_PA16, PIO_IT_EDGE, pin_edge_handler); \endcode
 * -# Enable the interrupt for the configured input pin:
 *     \code pio_enable_interrupt(PIOA, PIO_PA16); \endcode
 * -# Enable interrupt handling from the PIOA module:
 *     \code NVIC_EnableIRQ(PIOA_IRQn); \endcode
 *
 * \subsection sam_pio_quickstart_use_case_2_example_code Example code
 * Add the following function to your application:
 * \code
	void pin_edge_handler(const uint32_t id, const uint32_t index)
	{
		if ((id == ID_PIOA) && (index == PIO_PA16)){
			if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA16))
				pio_clear(PIOA, PIO_PA23);
			else
				pio_set(PIOA, PIO_PA23);
		}
	}
\endcode
 *
 * \subsection sam_pio_quickstart_use_case_2_example_workflow Workflow
 * -# We check the value of the pin:
 *     \code
	if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA16))
\endcode
 * -# Then we set the new output value based on the read pin value:
 *     \code
	    pio_clear(PIOA, PIO_PA23);
	else
	    pio_set(PIOA, PIO_PA23);
\endcode
 */

#ifdef __cplusplus
}
#endif

#endif /* PIO_H_INCLUDED */
