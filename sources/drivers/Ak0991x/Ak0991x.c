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

#include "Ak0991x.h"
#include <string.h>

static void wait_us(uint32_t us)
{
	uint64_t tt1, tt2;

	tt1 = inv_ak0991x_get_time_us();
	while (1) {
		tt2 = inv_ak0991x_get_time_us();
		if (tt2 > (tt1 + us))
			break;
	}
}

void inv_ak0991x_reset_states(struct inv_ak0991x * s,
		const struct inv_ak0991x_serif * serif)
{
	memset(s, 0, sizeof(*s));
	s->serif = *serif;
}

int inv_ak0991x_poll_data(struct inv_ak0991x * s, int16_t * compass_data)
{
	int rc = 1;
	uint8_t mode, data[9] = {0};

	if(s->compass_en) {
		rc = inv_ak0991x_serif_read_reg(&s->serif, AK0991x_REG_ST1, data, 1);
		if(rc != 0)
			return rc;

		if((data[0] & AK0991x_DRDY) == 0) {
			/* not an error, but data is not ready yet */
			return 1;
		}

		/* data is ready, read relevant registers now. Reading data registers will reset
		 * DRDY bit in ST1 register
		 */
		rc = inv_ak0991x_serif_read_reg(&s->serif, AK0991x_REG_HXL, &data[1], 8);
		if(rc != 0) {
			/* for some reason we could not read data register but DRDY has already been fired.
			 * Thus it is safer to reset compass_en flag to avoid putting AKM driver in some
			 * undefined state.
			 */
			s->compass_en = 0;
			return rc;
		}

		/* get measurment values if drdy */
		compass_data[0] = (((int16_t)data[2]) << 8) | data[1];
		compass_data[1] = (((int16_t)data[4]) << 8) | data[3];
		compass_data[2] = (((int16_t)data[6]) << 8) | data[5];

		/* apply ASA if available */
		if (s->compass_sens[0] && s->compass_sens[1] && s->compass_sens[2]) {
			uint8_t shift = 8;
			if (INV_AK09911_ID == s->compass_id)
				shift = 7;
			compass_data[0] = ((compass_data[0] * (s->compass_sens[0] + 128)) >> shift);
			compass_data[1] = ((compass_data[1] * (s->compass_sens[1] + 128)) >> shift);
			compass_data[2] = ((compass_data[2] * (s->compass_sens[2] + 128)) >> shift);
		}

		if(s->compass_en == AK0991x_CNTL2_MODE_SINGLE) {
			/* set to power down mode */
			mode = AK0991x_CNTL2_MODE_POWER_DOWN;
			inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL2, &mode, 1);
			s->compass_en = AK0991x_CNTL2_MODE_POWER_DOWN;
		}
	}

	return rc;
}

int inv_ak0991x_run_selftest(struct inv_ak0991x * s)
{
	int result;
	uint8_t data[6], mode;
	uint8_t counter;
	int16_t x, y, z;
	int shift;

	/* set to power down mode */
	mode = AK0991x_CNTL2_MODE_POWER_DOWN;
	result = inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL2, &mode, 1);
	if (result)
		goto AKM_fail;

	/* set self test mode */
	mode = AK0991x_CNTL2_MODE_SELF_TEST;
	result = inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL2, &mode, 1);
	if (result)
		goto AKM_fail;

	counter = 10;

	while (counter > 0) {
		wait_us(15 * 1000);
		result = inv_ak0991x_serif_read_reg(&s->serif, AK0991x_REG_ST1, data, 1);
		if (result)
			goto AKM_fail;
		if ((data[0] & AK0991x_DRDY) == 0)
			counter--;
		else
			counter = 0;
	}
	if ((data[0] & AK0991x_DRDY) == 0) {
		result = -1;
		goto AKM_fail;
	}

	result = inv_ak0991x_serif_read_reg(&s->serif, AK0991x_REG_HXL, data, 6);
	if (result)
		goto AKM_fail;

	x = ((int16_t)data[1]) <<8 | data[0];
	y = ((int16_t)data[3]) <<8 | data[2];
	z = ((int16_t)data[5]) <<8 | data[4];

	/* apply ASA if available */
	if (s->compass_sens[0] && s->compass_sens[1] && s->compass_sens[2]) {
		if (INV_AK09911_ID == s->compass_id)
			shift = 7;
		else
			shift = 8;
		x = ((x * (s->compass_sens[0] + 128)) >> shift);
		y = ((y * (s->compass_sens[1] + 128)) >> shift);
		z = ((z * (s->compass_sens[2] + 128)) >> shift);
	}

	result = -1;
	if (INV_AK09911_ID == s->compass_id) {
		const short AK09911_ST_Lower[3] = {-30, -30, -400};
		const short AK09911_ST_Upper[3] = {30, 30, -50};
		if (x > AK09911_ST_Upper[0] || x <  AK09911_ST_Lower[0])
			goto AKM_fail;
		if (y >  AK09911_ST_Upper[1] || y < AK09911_ST_Lower[1])
			goto AKM_fail;
		if (z >  AK09911_ST_Upper[2] || z < AK09911_ST_Lower[2])
			goto AKM_fail;
	}else if(INV_AK09912_ID == s->compass_id) {
		const short AK09912_ST_Lower[3] = {-200, -200, -1600};
		const short AK09912_ST_Upper[3] = {200, 200, -400};
		if (x > AK09912_ST_Upper[0] || x <  AK09912_ST_Lower[0])
			goto AKM_fail;
		if (y >  AK09912_ST_Upper[1] || y < AK09912_ST_Lower[1])
			goto AKM_fail;
		if (z >  AK09912_ST_Upper[2] || z < AK09912_ST_Lower[2])
			goto AKM_fail;
	}else if(INV_AK09915_ID == s->compass_id) {
		const short AK09915_ST_Lower[3] = {-200, -200, -800};
		const short AK09915_ST_Upper[3] = {200, 200, -200};
		if (x > AK09915_ST_Upper[0] || x <  AK09915_ST_Lower[0])
			goto AKM_fail;
		if (y >  AK09915_ST_Upper[1] || y < AK09915_ST_Lower[1])
			goto AKM_fail;
		if (z >  AK09915_ST_Upper[2] || z < AK09915_ST_Lower[2])
			goto AKM_fail;
	}else if(INV_AK09918_ID == s->compass_id) {
		const short AK09918_ST_Lower[3] = {-200, -200, -1000};
		const short AK09918_ST_Upper[3] = {200, 200, -150};
		if (x > AK09918_ST_Upper[0] || x <  AK09918_ST_Lower[0])
			goto AKM_fail;
		if (y >  AK09918_ST_Upper[1] || y < AK09918_ST_Lower[1])
			goto AKM_fail;
		if (z >  AK09918_ST_Upper[2] || z < AK09918_ST_Lower[2])
			goto AKM_fail;
	}
	result = 0;

AKM_fail:
	/* set to power down mode */
	mode = AK0991x_CNTL2_MODE_POWER_DOWN;
	result |= inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL2, &mode, 1);

	return result;
}

int inv_ak0991x_get_whoami(struct inv_ak0991x * s, uint8_t * whoami)
{
	uint8_t whoami2 = 0xff;
	int rc = inv_ak0991x_serif_read_reg(&s->serif, AK0991x_REG_WIA2, &whoami2, 1);
	if(rc != 0)
		return rc;

	switch (whoami2) {
		case AK09911_WHOAMI:
			s->compass_id = INV_AK09911_ID;
			break;
		case AK09912_WHOAMI:
			s->compass_id = INV_AK09912_ID;
			break;
		case AK09915_WHOAMI:
			s->compass_id = INV_AK09915_ID;
			break;
		case AK09918_WHOAMI:
			s->compass_id = INV_AK09918_ID;
			break;
		default:
			break;
	}

	/* Set minimum delay according to chip type */
	switch (s->compass_id) {
		case INV_AK09911_ID:
			s->min_delay_us = AK09911_ODR_MIN_DELAY;
			break;
		case INV_AK09912_ID:
			s->min_delay_us = AK09912_ODR_MIN_DELAY;
			break;
		case INV_AK09915_ID:
			s->min_delay_us = AK09915_ODR_MIN_DELAY;
			break;
		case INV_AK09918_ID:
			s->min_delay_us = AK09918_ODR_MIN_DELAY;
			break;
		default:
			s->min_delay_us = AK09912_ODR_MIN_DELAY;
			break;
	}

	return inv_ak0991x_serif_read_reg(&s->serif, AK0991x_REG_WIA1, whoami, 1);
}

int inv_ak0991x_soft_reset(struct inv_ak0991x * s)
{
	uint8_t soft_reset = 1;
	s->compass_en = 0;
	return inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL3, &soft_reset, 1);
}

int inv_ak0991x_retrieve_asa_values(struct inv_ak0991x * s)
{
	int rc;
	uint8_t mode;

	/* No ASA in AK09918 */
	if (s->compass_id == INV_AK09918_ID) {
		s->compass_sens[0] = 0;
		s->compass_sens[1] = 0;
		s->compass_sens[2] = 0;
		rc = 0;
	} else {
		if (s->compass_id != INV_AK09915_ID) {
			/* No definition of Fuse ROM in AK09915 spec */
			mode = AK0991x_CNTL2_MODE_FUSE_ROM;
			rc = inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL2, &mode, 1);
			if (rc != 0)
				return rc;
		}
		rc = inv_ak0991x_serif_read_reg(&s->serif, AK0991x_REG_ASAX, &s->compass_sens[0], 3);
		if (rc != 0)
			return rc;
		mode = AK0991x_CNTL2_MODE_POWER_DOWN;
		rc = inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL2, &mode, 1);
	}
	return rc;
}

int inv_ak0991x_enable_sensor(struct inv_ak0991x * s, uint8_t en)
{
	int rc = 0;

	if(en) {
		if(s->compass_en) {
			/* already enabled, let it complete its acquisition */
			rc = INV_ERROR;
		} else {
			uint8_t mode = en;
			s->compass_en = mode;
			rc = inv_ak0991x_serif_write_reg(&s->serif, AK0991x_REG_CNTL2, &mode, 1);
		}
	}
	else {
		rc = inv_ak0991x_soft_reset(s);
	}

	return rc;
}
