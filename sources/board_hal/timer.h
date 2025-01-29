/*
 *
 * Copyright (c) [2016] by InvenSense, Inc.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/** @defgroup Timer Timer
	@ingroup  Low_Level_Driver
	@{
*/
#ifndef _INV_TIMER_H_
#define _INV_TIMER_H_

#include <stdint.h>
#include "tc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* Timers available
*/
enum timer_num {
	INV_TIMER1 = 0,  // 64-bit, does not support registering a callback
	INV_TIMER2,      // 16-bit
	INV_TIMER3,      // 16-bit
	INV_TIMER4,      // 16-bit
	INV_TIMER5,      // 16-bit
	INV_TIMER_MAX
};


/** @brief Init the time base
 *  @param frequency Timer frequency to configure
 *  @return -1 if the parameters are not configurable, 0 otherwise
 */
int inv_timer_configure_timebase(uint32_t frequency);

/** @brief Enable timer so that it starts counting without any IRQ fired
 *  @param timer_num Timer peripheral number
 *  @return None
 */
void inv_timer_enable(unsigned timer_num);

/** @brief Get the counter value by reading the timer register
 *  @param	timer_num  Timer peripheral number
 *  @return timestamp  timestamp value in us on 64-bits for INV_TIMER1, 16-bits otherwise
 */
uint64_t inv_timer_get_counter(unsigned timer_num);

/** @brief Configure a timer which will trigger a callback at the end of its period
 *  @param[in]	timer_num  Timer peripheral number
 *  @param[in]	freq       Timer frequency in Hz
 *  @param[in]	context    Callback context parameter
 *  @param[in]	callback   Called at the end of the timer interrupt handler
 *  @return -1 if parameters are not configurable, the timer's channel on which the callback is registered on success
 */
int inv_timer_configure_callback(unsigned timer_num, uint32_t freq,
		void * context, void (*callback) (void *context));

/** @brief Stop the specified timer's channel
 *  @param[in]	timer_num  Timer peripheral number
 *  @param[in]	channel    Timer channel to turn off
 *  @return -1 if parameters are not configurable, 0 otherwise
*/
int inv_timer_channel_stop(unsigned timer_num, uint8_t channel);

/** @brief Disable the specified timer's channel without further re-initialisation
 *  @param[in]	timer_num  Timer peripheral number
 *  @param[in]	channel    Timer channel to be suspended
 *  @details
 *  This function is intended for use cases where the timer does not need to be 
 *  reconfigured (deadline, resolution, ..) but only have its channel put on hold.
 *  This function is not expected to cleanly reset timer resource (it is not a
 *  duplicate of \sa timer_channel_stop, which shall be called to release the resource).
 *  @note \sa timer_configure_callback should not be called directly after this function.
 */
int inv_timer_channel_suspend(unsigned timer_num, uint8_t channel);

/** @brief Updated the timer's channel frequency
 *  @param[in]	timer_num  Timer peripheral number
 *  @param[in]	channel    Timer channel to update
 *  @param[in]	new_freq   Timer new frequency in Hz
 *  @return -1 if parameters are not configurable, 0 otherwise
 */
int inv_timer_channel_reconfigure_freq(unsigned timer_num, uint8_t channel, uint32_t new_freq);

/** @brief Retrieve timer's low level characteristics
 *  @param[in]  timer_num      Timer peripheral number
 *  @param[out] timer_instance Timer peripheral memory
 *  @param[out] timer_channel  Timer channel to update
 *  @return -1 if timer properties can't be retrieved, 0 otherwise
 */
int inv_timer_get_hw_infos(const unsigned timer_num, Tc **const timer_instance, uint32_t *const timer_channel);

#ifdef __cplusplus
}
#endif

#endif /* _INV_TIMER_H_ */

/** @} */
