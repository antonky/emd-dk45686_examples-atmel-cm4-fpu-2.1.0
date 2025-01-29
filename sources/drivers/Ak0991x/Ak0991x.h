/*
 *
 * Copyright (c) [2015] by InvenSense, Inc.
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

/** @defgroup DriverAk0991x Ak0991x driver
 *  @brief    Low-level driver for Ak0991x devices
 *  @ingroup  Drivers
 *  @{
 */

#ifndef _INV_AK0991X_H_
#define _INV_AK0991X_H_

#include "Ak0991xSerif.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AK0991x_COMPANY_ID  0x48

#define AK09911_WHOAMI      0x05
#define AK09912_WHOAMI      0x04
#define AK09915_WHOAMI      0x10
#define AK09918_WHOAMI      0x0C

/* Register definitions */
#define AK0991x_REG_WIA1					0x00		/* Company ID */
#define AK0991x_REG_WIA2					0x01		/* Device ID */

#define AK0991x_REG_INFO1					0x02		/* Information */
#define AK0991x_REG_INFO2					0x03		/* Information */

#define AK0991x_REG_ST1						0x10		/* Status 1 */
#define AK0991x_REG_HXL						0x11		/* Measurement data : X-axis data */
#define AK0991x_REG_HXH						0x12		/* Measurement data : X-axis data */
#define AK0991x_REG_HYL						0x13		/* Measurement data : Y-axis data */
#define AK0991x_REG_HYH						0x14		/* Measurement data : Y-axis data */
#define AK0991x_REG_HZL						0x15		/* Measurement data : Z-axis data */
#define AK0991x_REG_HZH						0x16		/* Measurement data : Z-axis data */
#define AK0991x_REG_TMPS					0x17		/*  */
#define AK0991x_REG_ST2						0x18		/* Status 2 : Data status */

#define AK0991x_REG_CNTL1					0x30		/* Control 1 : Function Control */
#define AK0991x_REG_CNTL2					0x31		/* Control 2 : Function Control */
#define AK0991x_REG_CNTL3					0x32		/* Control 3 : Function Control */

#define AK0991x_REG_TS1						0x33		/* Test 1 : DO NOT ACCESS,  */

#define AK0991x_REG_ASAX					0x60		/* X-axis sensitivity adjustment value */
#define AK0991x_REG_ASAY					0x61		/* Y-axis sensitivity adjustment value */
#define AK0991x_REG_ASAZ					0x62		/* Z-axis sensitivity adjustment value */

/* Register helper values */
#define AK0991x_CNTL2_MODE_POWER_DOWN   	0x00		/* Power-down mode */
#define AK0991x_CNTL2_MODE_SINGLE       	0x01		/* Single measurement mode */
#define AK0991x_CNTL2_MODE_CONTINUOUS1  	0x02 		/* Continuous measurement mode 1 10Hz */
#define AK0991x_CNTL2_MODE_CONTINUOUS2  	0x04		/* Continuous measurement mode 2 20Hz */
#define AK0991x_CNTL2_MODE_CONTINUOUS3     	0x06		/* Continuous measurement mode 3 50Hz */
#define AK0991x_CNTL2_MODE_CONTINUOUS4     	0x08		/* Continuous measurement mode 4 100Hz */
#define AK0991x_CNTL2_MODE_CONTINUOUS5     	0x0A		/* Continuous measurement mode 5 200Hz */
#define AK0991x_CNTL2_MODE_CONTINUOUS6     	0x0C		/* Continuous measurement mode 6 1HZ */

#define AK0991x_CNTL2_MODE_SELF_TEST	   	0x10		/* Self-test mode */
#define AK0991x_CNTL2_MODE_FUSE_ROM     	0x1F		/* Fuse ROM access mode */

#define AK0991x_DRDY						0x01

#define AK09911_ODR_MIN_DELAY              10000		/* minimum delay of AK09911 (us) */
#define AK09912_ODR_MIN_DELAY              10000		/* minimum delay of AK09912 (us) */
#define AK09915_ODR_MIN_DELAY               5000		/* minimum delay of AK09915 (us) */
#define AK09918_ODR_MIN_DELAY              10000		/* minimum delay of AK09918 (us) */

/** @brief Supported auxiliary compass identifier
 */
enum inv_ak0991x_id {
	INV_AK09911_ID,  /**< AKM AK09911 */
	INV_AK09912_ID,  /**< AKM AK09912 */
	INV_AK09915_ID,  /**< AKM AK09915 */
	INV_AK09918_ID,  /**< AKM AK09918 */
};

/** @brief AK0991x driver states definition
 */
typedef struct inv_ak0991x {
	struct inv_ak0991x_serif serif;
	uint8_t compass_en;
	uint8_t compass_sens[3];
	enum inv_ak0991x_id compass_id;
	uint32_t min_delay_us;
} inv_ak0991x_t;

/** @brief Hook for low-level system time() function to be implemented by upper layer
 *  @return monotonic timestamp in us
 *  @details
 *  When running self-tests, this function is used to measure a duration.
 *  It can also be used as a way of getting the current time.
 */
extern uint64_t inv_ak0991x_get_time_us(void);

/** @brief Hook used for accurate timestamping, called by low-level driver after acquisition is complete
 *  @return timestamp to be reported with the last data
 *  @details
 *  The @see inv_ak0991x_get_time_us function is used to obtain the current time, this
 *  function has the slightly different purpose of marking the end of the sampling very
 *  accurately (relying on timers to achieve this). Host implementation will do the same
 *  as @see inv_ak0991x_get_time_us.
 */
extern uint64_t inv_ak0991x_get_dataready_interrupt_time_us(void);

/** @brief Hook called when magnetometer is started, implemented by upper layer which knows about timers
 *  @param[in] period sensor period in micro-second
 *  @return 0 on success, -1 on failure
 */
extern int inv_ak0991x_start_timer_us(uint32_t period);

/** @brief Hook called when magnetometer is stopped, implemented by upper layer which knows about timers
 *  @return 0 on success, -1 on failure
 */
extern int inv_ak0991x_stop_timer(void);

/** @brief Hook called when magnetometer odr is updated, implemented by upper layer which knows about timers
 *  @param[in] period sensor period in micro-second
 *  @return 0 on success, -1 on failure
 */
extern int inv_ak0991x_reconfigure_timer_us(uint32_t period);

/** @brief Reset and initialize driver states
 *  @param[in] s handle to driver states structure
 *  @param[in] serif handle to SERIF object for underlying register access
 */
void inv_ak0991x_reset_states(struct inv_ak0991x * s,
		const struct inv_ak0991x_serif * serif);

/** @brief Check and retrieve for new data
 *  @param[out] compass_data raw compass data
 *  @return     0 on success, negative value on error
 */
int inv_ak0991x_poll_data(struct inv_ak0991x * s, int16_t * compass_data);

/**
*  @brief      Perform hardware self-test for compass.
*  @return     0 on success, negative value on error
*/
int inv_ak0991x_run_selftest(struct inv_ak0991x * s);

/** @brief return WHOAMI value
 *  @param[out] whoami WHOAMI for device
 *  @return     0 on success, negative value on error
 */
int inv_ak0991x_get_whoami(struct inv_ak0991x * s, uint8_t * whoami);

/** @brief retrieve ASA register values
 *  @return     0 on success, negative value on error
 */
int inv_ak0991x_retrieve_asa_values(struct inv_ak0991x * s);

/** @brief Perform a soft reset of the device
 *  @return 0 on success, negative value on error.
 */
int inv_ak0991x_soft_reset(struct inv_ak0991x * s);

/** @brief Enables / disables the compass sensor
 * @param[in] enable			0=off, 1=on
 * @return 0 in case of success, negative value on error
 */
int inv_ak0991x_enable_sensor(struct inv_ak0991x * s, uint8_t en);

#endif /* _INV_AK0991X_H_ */

/** @} */
