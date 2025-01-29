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
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef TC_H_INCLUDED
#define TC_H_INCLUDED

/**
 * \defgroup asfdoc_sam_drivers_tc_group SAM3/4S/4L/4E/4N/4CM/4C/G Timer Counter (TC) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers 
 * provides an interface for the configuration and management of the 
 * device's Timer Counter functionality.
 *
 * The Timer Counter (TC) includes several identical 16-bit or 32-bit
 * Timer Counter channels. Each channel can be independently programmed
 * to perform a wide range of functions that includes frequency
 * measurement, event counting, interval measurement, pulse generation,
 * delay timing, and pulse width modulation.
 *
 * Devices from the following series can use this module:
 * - Atmel | SMART SAM3
 * - Atmel | SMART SAM4S
 * - Atmel | SMART SAM4L
 * - Atmel | SMART SAM4E
 * - Atmel | SMART SAM4N
 * - Atmel | SMART SAM4CM
 * - Atmel | SMART SAM4C
 * - Atmel | SMART SAMG
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam_drivers_tc_prerequisites
 *  - \ref asfdoc_sam_drivers_tc_module_overview
 *  - \ref asfdoc_sam_drivers_tc_special_considerations
 *  - \ref asfdoc_sam_drivers_tc_extra_info
 *  - \ref asfdoc_sam_drivers_tc_examples
 *  - \ref asfdoc_sam_drivers_tc_api_overview
 *
 *
 * \section asfdoc_sam_drivers_tc_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam_drivers_tc_module_overview Module Overview
 * The Timer Counter (TC) includes several identical 16-bit or 32-bit Timer
 * Counter channels. The number of TC channels is device specific, refer
 * to the device-specific datasheet for more information.
 *
 * Each channel can be independently programmed to perform a wide range of
 * functions that includes frequency measurement, event counting, interval measurement,
 * pulse generation, delay timing, and pulse width modulation.
 *
 * Each channel has three external clock inputs, five internal clock inputs,
 * and two multi-purpose input/output signals which can be configured by the user.
 * Each channel drives an internal interrupt signal which can be programmed to
 * generate processor interrupts.
 *
 * The Timer Counter (TC) embeds a quadrature decoder logic connected in front of
 * the timers. When enabled, the quadrature decoder performs the input line
 * filtering, decoding of quadrature signals and connects to the timers/counters
 * in order to read the position and speed of the motor.
 *
 *
 * \section asfdoc_sam_drivers_tc_special_considerations Special Considerations
 * \subsection asfdoc_sam_drivers_tc_special_considerations_clock External Clock
 * In all cases, if an external clock is used, the duration of each of its levels
 * must be longer than the master clock (MCLK) period. The external clock frequency
 * must be at least 2.5 times lower than the master clock.
 *
 * \subsection asfdoc_sam_drivers_tc_special_considerations_trigger External Trigger
 * If an external trigger is used, the duration of its pulses must be longer than
 * the master clock (MCLK) period in order to be detected.
 *
 *
 * \section asfdoc_sam_drivers_tc_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam_drivers_tc_extra. This includes:
 *  - \ref asfdoc_sam_drivers_tc_extra_acronyms
 *  - \ref asfdoc_sam_drivers_tc_extra_dependencies
 *  - \ref asfdoc_sam_drivers_tc_extra_errata
 *  - \ref asfdoc_sam_drivers_tc_extra_history
 *
 * \section asfdoc_sam_drivers_tc_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam_drivers_tc_exqsg.
 *
 *
 * \section asfdoc_sam_drivers_tc_api_overview API Overview
 * @{
 */

#include <compiler.h>

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

void tc_init(Tc *p_tc, uint32_t ul_Channel, uint32_t ul_Mode);

/**
 * \brief Asserts a SYNC signal to generate a software trigger on
 * all channels.
 *
 * \param[out] p_tc Module hardware register base address pointer
 *
 */
 __always_inline static void tc_sync_trigger(Tc *p_tc)
{
	/* Validate inputs. */
	Assert(p_tc);
	
	p_tc->TC_BCR = TC_BCR_SYNC;
}

/**
 * \brief Configure the TC Block mode.
 *
 * \note The function tc_init() must be called prior to this one.
 *
 * \param[out] p_tc        Module hardware register base address pointer
 * \param[in] ul_blockmode Block mode register value to set
 *
 * \note For more information regarding <i>ul_blockmode</i> configuration refer to
 * the section  entitled "TC Block Mode Register" in the device-specific datasheet.
 */
 __always_inline static void tc_set_block_mode(Tc *p_tc, uint32_t ul_blockmode)
{
	/* Validate inputs. */
	Assert(p_tc);
	
	p_tc->TC_BMR = ul_blockmode;
}

#if (!SAM3U) || defined(__DOXYGEN__)
/**
 * \brief Configure TC for 2-bit Gray Counter for Stepper Motor.
 * \note The function tc_init() must be called prior to this one.
 *
 * \note This function is not available on SAM3U devices.
 *
 * \param[out] p_tc          Module hardware register base address pointer
 * \param[in] ul_channel     Channel to configure
 * \param[in] ul_steppermode Stepper motor mode register value to set
 *
 * \return 0 for OK.
 */
 __always_inline static uint32_t tc_init_2bit_gray(
		Tc *p_tc,
		uint32_t ul_channel,
		uint32_t ul_steppermode)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_SMMR = ul_steppermode;
	return 0;
}
#endif /* (!SAM3U) || defined(__DOXYGEN__) */

/**
 * \brief Start the TC clock on the specified channel.
 *
 * \param[out] p_tc      Module hardware register base address pointer
 * \param[in] ul_channel Channel to configure
 */
 __always_inline static void tc_start(Tc *p_tc, uint32_t ul_channel)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

/**
 * \brief Stop the TC clock on the specified channel.
 *
 * \param[out] p_tc      Module hardware register base address pointer
 * \param[in] ul_channel Channel to configure
 */
 __always_inline static void tc_stop(Tc *p_tc, uint32_t ul_channel)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_CCR = TC_CCR_CLKDIS;
}

/**
 * \brief Read the counter value on the specified channel.
 *
 * \param[in] p_tc       Module hardware register base address pointer
 * \param[in] ul_channel Channel to read
 *
 * \return The counter value.
 */
 __always_inline static uint32_t tc_read_cv(Tc *p_tc, uint32_t ul_channel)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	return p_tc->TC_CHANNEL[ul_channel].TC_CV;
}

/**
 * \brief Read TC Register A (RA) on the specified channel.
 *
 * \param[in] p_tc       Module hardware register base address pointer
 * \param[in] ul_channel Channel to read
 *
 * \return The TC Register A (RA) value.
 */
 __always_inline static uint32_t tc_read_ra(Tc *p_tc, uint32_t ul_channel)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	return p_tc->TC_CHANNEL[ul_channel].TC_RA;
}

/**
 * \brief Read TC Register B (RB) on the specified channel.
 *
 * \param[in] p_tc       Module hardware register base address pointer
 * \param[in] ul_channel Channel to read
 *
 * \return The TC Register B (RB) value.
 */
 __always_inline static uint32_t tc_read_rb(Tc *p_tc, uint32_t ul_channel)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	return p_tc->TC_CHANNEL[ul_channel].TC_RB;
}

/**
 * \brief Read TC Register C (RC) on the specified channel.
 *
 * \param[in] p_tc       Module hardware register base address pointer
 * \param[in] ul_channel Channel to read
 *
 * \return The Register C (RC) value.
 */
 __always_inline static uint32_t tc_read_rc(Tc *p_tc, uint32_t ul_channel)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	return p_tc->TC_CHANNEL[ul_channel].TC_RC;
}

/**
 * \brief Write to TC Register A (RA) on the specified channel.
 *
 * \param[out] p_tc      Module hardware register base address pointer
 * \param[in] ul_channel Channel to write
 * \param[in] ul_value   Value to write
 */
 __always_inline static void tc_write_ra(Tc *p_tc, uint32_t ul_channel,
		uint32_t ul_value)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_RA = ul_value;
}

/**
 * \brief Write to TC Register B (RB) on the specified channel.
 *
 * \param[out] p_tc      Module hardware register base address pointer
 * \param[in] ul_channel Channel to write
 * \param[in] ul_value   Value to write
 */
 __always_inline static void tc_write_rb(Tc *p_tc, uint32_t ul_channel,
		uint32_t ul_value)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_RB = ul_value;
}

/**
 * \brief Write to TC Register C (RC) on the selected channel.
 *
 * \param[out] p_tc      Module hardware register base address pointer
 * \param[in] ul_channel Channel to write
 * \param[in] ul_value   Value to write
 */
 __always_inline static void tc_write_rc(Tc *p_tc, uint32_t ul_channel,
		uint32_t ul_value)
{
	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));

	p_tc->TC_CHANNEL[ul_channel].TC_RC = ul_value;
}

uint32_t tc_find_mck_divisor(uint32_t ul_freq, uint32_t ul_mck,
		uint32_t *p_uldiv, uint32_t *ul_tcclks, uint32_t ul_boardmck);

/**
 * \brief Enable the TC interrupts on the specified channel.
 *
 * \param[in,out] p_tc   Module hardware register base address pointer
 * \param[in] ul_channel Channel to configure
 * \param[in] ul_sources Bitmask of interrupt sources
 *
 * Where the input parameter <i>ul_sources</i> can be one or more of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *     <tr><td>TC_IER_COVFS</td><td>Enables the Counter Overflow Interrupt</td></tr>
 *     <tr><td>TC_IER_LOVRS</td><td>Enables the Load Overrun Interrupt</td></tr>
 *     <tr><td>TC_IER_CPAS</td><td>Enables the RA Compare Interrupt</td></tr>
 *     <tr><td>TC_IER_CPBS</td><td>Enables the RB Compare Interrupt</td></tr>
 *     <tr><td>TC_IER_CPCS</td><td>Enables the RC Compare Interrupt</td></tr>
 *     <tr><td>TC_IER_LDRAS</td><td>Enables the RA Load Interrupt</td></tr>
 *     <tr><td>TC_IER_LDRBS</td><td>Enables the RB Load Interrupt</td></tr>
 *     <tr><td>TC_IER_ETRGS</td><td>Enables the External Trigger Interrupt</td></tr>
 * </table>
 */
 __always_inline static void tc_enable_interrupt(Tc *p_tc, uint32_t ul_channel,
		uint32_t ul_sources)
{
	TcChannel *tc_channel;

	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	tc_channel->TC_IER = ul_sources;
}

/**
 * \brief Disable TC interrupts on the specified channel.
 *
 * \param[in,out] p_tc   Module hardware register base address pointer
 * \param[in] ul_channel Channel to configure
 * \param[in] ul_sources A bitmask of Interrupt sources
 *
 * Where the input parameter <i>ul_sources</i> can be one or more of the following:
 * <table>
 * <tr>
 *    <th>Parameter Value</th>
 *    <th>Description</th>
 * </tr>
 *     <tr><td>TC_IDR_COVFS</td><td>Disables the Counter Overflow Interrupt</td></tr>
 *     <tr><td>TC_IDR_LOVRS</td><td>Disables the Load Overrun Interrupt</td></tr>
 *     <tr><td>TC_IDR_CPAS</td><td>Disables the RA Compare Interrupt</td></tr>
 *     <tr><td>TC_IDR_CPBS</td><td>Disables the RB Compare Interrupt</td></tr>
 *     <tr><td>TC_IDR_CPCS</td><td>Disables the RC Compare Interrupt</td></tr>
 *     <tr><td>TC_IDR_LDRAS</td><td>Disables the RA Load Interrupt</td></tr>
 *     <tr><td>TC_IDR_LDRBS</td><td>Disables the RB Load Interrupt</td></tr>
 *     <tr><td>TC_IDR_ETRGS</td><td>Disables the External Trigger Interrupt</td></tr>
 * </table>
 */
 __always_inline static void tc_disable_interrupt(Tc *p_tc, uint32_t ul_channel,
		uint32_t ul_sources)
{
	TcChannel *tc_channel;

	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	tc_channel->TC_IDR = ul_sources;
}

/**
 * \brief Read the TC interrupt mask for the specified channel.
 *
 * \param[in] p_tc       Module hardware register base address pointer
 * \param[in] ul_channel Channel to read
 *
 * \return The TC interrupt mask value.
 */
 __always_inline static uint32_t tc_get_interrupt_mask(Tc *p_tc, uint32_t ul_channel)
{
	TcChannel *tc_channel;

	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	return tc_channel->TC_IMR;
}

/**
 * \brief Get the current status for the specified TC channel.
 *
 * \param[in] p_tc       Module hardware register base address pointer
 * \param[in] ul_channel Channel number
 *
 * \return The current TC status.
 */
 __always_inline static uint32_t tc_get_status(Tc *p_tc, uint32_t ul_channel)
{
	TcChannel *tc_channel;

	/* Validate inputs. */
	Assert(p_tc);
	Assert(ul_channel <
			(sizeof(p_tc->TC_CHANNEL) / sizeof(p_tc->TC_CHANNEL[0])));
			
	tc_channel = p_tc->TC_CHANNEL + ul_channel;
	return tc_channel->TC_SR;
}

#if (!SAM4L && !SAMG) || defined(__DOXYGEN__)
void tc_enable_qdec_interrupt(Tc *p_tc, uint32_t ul_sources);
void tc_disable_qdec_interrupt(Tc *p_tc, uint32_t ul_sources);
uint32_t tc_get_qdec_interrupt_mask(Tc *p_tc);
uint32_t tc_get_qdec_interrupt_status(Tc *p_tc);
#endif /* (!SAM4L && !SAMG) || defined(__DOXYGEN__) */

#if (!SAM3U)
void tc_set_writeprotect(Tc *p_tc, uint32_t ul_enable);
#endif /* (!SAM3U) */

#if SAM4L || defined(__DOXYGEN__)
uint32_t tc_get_feature(Tc *p_tc);
uint32_t tc_get_version(Tc *p_tc);
#endif /* SAM4L || defined(__DOXYGEN__) */

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/** @} */

/**
 * \page asfdoc_sam_drivers_tc_extra Extra Information for Timer Counter Driver
 *
 * \section asfdoc_sam_drivers_tc_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>MCK</td>
 *      <td>Master Clock</td>
 * </tr>
 *  <tr>
 *      <td>PBA</td>
 *      <td>Peripheral Bus A clock</td>
 * </tr>
 *  <tr>
 *      <td>PHA</td>
 *      <td>Quadrature Decoder input signal Phase A</td>
 * </tr>
 *  <tr>
 *      <td>PHB</td>
 *      <td>Quadrature Decoder input signal Phase B</td>
 * </tr>
 *  <tr>
 *      <td>QDEC</td>
 *      <td>Quadrature Decoder</td>
 * </tr>
 *  <tr>
 *      <td>QSG</td>
 *      <td>Quick Start Guide</td>
 * </tr>
 *  <tr>
 *      <td>RA</td>
 *      <td>Register A</td>
 * </tr>
 *  <tr>
 *      <td>RB</td>
 *      <td>Register B</td>
 * </tr>
 *  <tr>
 *      <td>RC</td>
 *      <td>Register C</td>
 * </tr>
 *  <tr>
 *      <td>TIOB</td>
 *      <td>Timer Input Output B</td>
 * </tr>
 * </table>
 *
 *
 * \section asfdoc_sam_drivers_tc_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - \ref clk_group "System Clock Management (sysclock)"
 *  - \ref asfdoc_sam_drivers_gpio_group "General Purpose I/O (GPIO) driver"
 *  - \ref asfdoc_sam_drivers_pmc_group "Power Manager Controller (PMC) driver"
 *
 *
 * \section asfdoc_sam_drivers_tc_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam_drivers_tc_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */
 
/**
 * \page asfdoc_sam_drivers_tc_exqsg Examples for Timer Counter
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications for \ref asfdoc_sam_drivers_tc_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam_drivers_tc_qsg
 *  - \subpage asfdoc_sam_drivers_tc_example
 *
 * \page asfdoc_sam_drivers_tc_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42301B</td>
 *		<td>07/2015</td>
 *		<td>Updated title of application note and added list of supported devices</td>
 *	</tr>
 *	<tr>
 *		<td>42301A</td>
 *		<td>05/2014</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 *
 */
 
/**
 * \page asfdoc_sam_drivers_tc_qsg Quick Start Guide for the TC driver
 *
 * This is the quick start guide for the \ref asfdoc_sam_drivers_tc_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case. The code examples can be copied into the main 
 * application loop or any other function that will need to control the 
 * AST module.
 *
 * \section asfdoc_sam_drivers_tc_qsg_use_cases Use Cases
 * - \ref asfdoc_sam_drivers_tc_qsg_basic_capture
 * - \ref asfdoc_sam_drivers_tc_qsg_basic_waveform
 *
 * \section asfdoc_sam_drivers_tc_qsg_basic_capture TC Capture Mode Basic Usage
 *
 * This use case will demonstrate how to initialize the TC module to
 * operate in capture mode using interrupts. Note, that the macros
 * used to select the TC channel are device specific. Refer to the
 * appropriate device-specific datasheet for more information.
 *
 *
 * \section asfdoc_sam_drivers_tc_qsg_basic_capture_setup Setup Steps
 *
 * \subsection asfdoc_sam_tc_qsg_basic_capture_prereq Prerequisites
 *
 * This module requires the following services:
 * - \ref clk_group "System Clock Management (sysclock)"
 * - \ref asfdoc_sam_drivers_gpio_group "General Purpose I/O (GPIO) driver"
 *
 * \subsection asfdoc_sam_drivers_tc_qsg_basic_capture_setup_code Setup Code
 *
 * Add these macros to the top of your main application C-file:
 * \snippet conf_board.h tc_define_peripheral
 * \snippet conf_board.h tc_define_ch2
 * \snippet conf_board.h tc_define_irq_handler
 *
 * Add this macro and functions to your main application C-file:
 * \snippet tc_capture_waveform_example.c tc_capture_selection
 * \snippet tc_capture_waveform_example.c tc_capture_init
 * \snippet tc_capture_waveform_example.c tc_capture_irq_handler_start
 * \snippet tc_capture_waveform_example.c tc_capture_irq_handler_end
 *
 * \subsection asfdoc_sam_drivers_tc_qsg_basic_capture_setup_workflow Workflow
 *
 * -# Enable the TC module's capture pin:
 * \snippet tc_capture_waveform_example.c tc_capture_gpio
 * -# Initialize the capture channel to the following:
 *   - Load RA on the rising edge of TIOA
 *   - Load RB on the falling edge of TIOA
 *   - Set the external trigger to TIOA
 *   - Set the external trigger to falling edge
 * \snippet tc_capture_waveform_example.c tc_capture_init_call
 * -# Enable the TC interrupt using NVIC:
 * \snippet tc_capture_waveform_example.c tc_capture_init_irq
 * -# Enable the capture channel interrupt:
 * \snippet tc_capture_waveform_example.c tc_capture_init_module_irq
 * -# In the \ref TC_Handler_null "TC_Handler()" function, the load.
 * RB interrupt can be checked by:
 * \snippet tc_capture_waveform_example.c tc_capture_irq_handler_status
 * \code } \endcode
 * -# In the \ref TC_Handler_null "TC_Handler()" function, the RA value.
 * can be read by:
 * \code uint32_t gs_ul_captured_ra; \endcode
 * \snippet tc_capture_waveform_example.c tc_capture_irq_handler_read_ra
 * -# In the \ref TC_Handler_null "TC_Handler()" function, the RB value.
 * can be read by:
 * \code uint32_t gs_ul_captured_rb; \endcode
 * \snippet tc_capture_waveform_example.c tc_capture_irq_handler_read_rb
 *
 * \section asfdoc_sam_drivers_tc_qsg_basic_waveform TC Waveform Mode Basic Usage
 *
 * This use case will demonstrate how to initialize the TC module to
 * operate in waveform mode. Note, that the macros used to select
 * the TC channel are device specific. Refer to the appropriate
 * device-specific datasheet for more information.
 *
 *
 * \section asfdoc_sam_drivers_tc_qsg_basic_waveform_setup Setup Steps
 *
 * \subsection asfdoc_sam_tc_qsg_basic_waveform_prereq Prerequisites
 *
 * This module requires the following services:
 * - \ref clk_group "System Clock Management (sysclock)"
 * - \ref asfdoc_sam_drivers_gpio_group "General Purpose I/O (GPIO) driver"
 *
 * \subsection asfdoc_sam_drivers_tc_qsg_basic_waveform_setup_code Setup Code
 *
 * Add these macros to the top of your main application C-file:
 * \snippet conf_board.h tc_define_peripheral
 * \snippet conf_board.h tc_define_ch1
 *
 * Add these macros and function to your main application C-file:
 * \code #define TC_WAVEFORM_TIMER_SELECTION TC_CMR_TCCLKS_TIMER_CLOCK4 \endcode
 * \code #define TC_WAVEFORM_DIVISOR     128 \endcode
 * \code #define TC_WAVEFORM_FREQUENCY   178 \endcode
 * \code #define TC_WAVEFORM_DUTY_CYCLE  30 \endcode
 * \code
 * static void tc_waveform_initialize(void)
 * {
 *	uint32_t ra, rc;
 *
 *	// Configure the PMC to enable the TC module.
 *	sysclk_enable_peripheral_clock(ID_TC_WAVEFORM);
 *
 *	// Init TC to waveform mode.
 *	tc_init(TC, TC_CHANNEL_WAVEFORM,
 *			TC_WAVEFORM_TIMER_SELECTION // Waveform Clock Selection
 *			| TC_CMR_WAVE       // Waveform mode is enabled
 *			| TC_CMR_ACPA_SET   // RA Compare Effect: set
 *			| TC_CMR_ACPC_CLEAR // RC Compare Effect: clear
 *			| TC_CMR_CPCTRG     // UP mode with automatic trigger on RC Compare
 *	);
 *
 *	// Configure waveform frequency and duty cycle.
 *	rc = (sysclk_get_peripheral_bus_hz(TC) /
 *			TC_WAVEFORM_DIVISOR /
 *			TC_WAVEFORM_FREQUENCY;
 *	tc_write_rc(TC, TC_CHANNEL_WAVEFORM, rc);
 *	ra = (100 - TC_WAVEFORM_FREQUENCY_DUTY_CYCLE * rc / 100;
 *	tc_write_ra(TC, TC_CHANNEL_WAVEFORM, ra);
 *
 *	// Enable TC TC_CHANNEL_WAVEFORM.
 *	tc_start(TC, TC_CHANNEL_WAVEFORM);
 * } \endcode
 *
 * \subsection asfdoc_sam_drivers_tc_qsg_basic_waveform_setup_workflow Workflow
 *
 * -# Enable the TC module's waveform pin:
 * \snippet tc_capture_waveform_example.c tc_waveform_gpio
 * -# Initialize the waveform channel to the following:
 *   - Output frequency of 178Hz, with a duty-cycle of 30%
 *   - Use TC_CMR_TCCLKS_TIMER_CLOCK4, with a divisor of 128
 * \snippet tc_capture_waveform_example.c tc_waveform_init_call
 */
#endif /* TC_H_INCLUDED */
