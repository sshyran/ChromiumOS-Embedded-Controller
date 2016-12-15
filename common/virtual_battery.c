/* Copyright 2016 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Virtual battery cross-platform code for Chrome EC */

#include "battery.h"
#include "charge_state.h"
#include "ec_commands.h"
#include "host_command.h"
#include "i2c.h"
#include "system.h"
#include "util.h"
#include "virtual_battery.h"

/* Console output macros */
#define CPUTS(outstr) cputs(CC_I2C, outstr)
#define CPRINTS(format, args...) cprints(CC_I2C, format, ## args)

/*
 * The state machine used to parse smart battery command
 * to support virtual battery.
 */
enum batt_cmd_parse_state {
	IDLE = 0, /* initial state */
	START = 1, /* received the register address (command code) */
	WRITE_VB, /* writing data bytes to the slave */
	READ_VB, /* reading data bytes to the slave */
};

static enum batt_cmd_parse_state sb_cmd_state;
static uint8_t cache_hit;
static const uint8_t *batt_cmd_head;
static int acc_write_len;

int virtual_battery_handler(struct ec_response_i2c_passthru *resp,
				   int in_len, int *err_code, int xferflags,
				   int read_len, int write_len,
				   const uint8_t *out)
{

#if defined(CONFIG_BATTERY_PRESENT_GPIO) || \
	defined(CONFIG_BATTERY_PRESENT_CUSTOM)
	/*
	 * If the battery isn't present, return a NAK (which we
	 * would have gotten anyways had we attempted to talk to
	 * the battery.)
	 */
	if (battery_is_present() != BP_YES) {
		resp->i2c_status = EC_I2C_STATUS_NAK;
		return EC_ERROR_INVAL;
	}
#endif
	switch (sb_cmd_state) {
	case IDLE:
		/*
		 * A legal battery command must start
		 * with a i2c write for reg index.
		 */
		if (write_len == 0) {
			resp->i2c_status = EC_I2C_STATUS_NAK;
			return EC_ERROR_INVAL;
		}
		/* Record the head of battery command. */
		batt_cmd_head = out;
		sb_cmd_state = START;
		*err_code = 0;
		break;
	case START:
		if (write_len > 0) {
			sb_cmd_state = WRITE_VB;
			*err_code = 0;
		} else {
			sb_cmd_state = READ_VB;
			/* Test if the reg is cached. */
			*err_code = virtual_battery_operation(batt_cmd_head,
						NULL, 0, 0);
			/*
			 * If the reg is not cached in the virtual memory,
			 * we need to physically write the reg index to
			 * the battery.
			 */
			if (*err_code) {
				*err_code = i2c_xfer(
					I2C_PORT_VIRTUAL_BATTERY,
					VIRTUAL_BATTERY_ADDR,
					batt_cmd_head,
					1,
					NULL,
					0,
					I2C_XFER_START);
				/* sent a stop bit here */
				if (*err_code) {
					if (*err_code == EC_ERROR_TIMEOUT) {
						resp->i2c_status =
						EC_I2C_STATUS_TIMEOUT;
					} else {
						resp->i2c_status =
						EC_I2C_STATUS_NAK;
					}
					reset_parse_state();
					return EC_ERROR_INVAL;
				}
				*err_code = 1;
			} else
				cache_hit = 1;
		}
		break;
	case WRITE_VB:
		if (write_len == 0) {
			resp->i2c_status = EC_I2C_STATUS_NAK;
			reset_parse_state();
			return EC_ERROR_INVAL;
		}
		*err_code = 0;
		break;
	case READ_VB:
		if (read_len == 0) {
			resp->i2c_status = EC_I2C_STATUS_NAK;
			reset_parse_state();
			return EC_ERROR_INVAL;
		}
		/*
		 * Do not send the command to battery
		 * if the reg is cached.
		 */
		if (cache_hit)
			*err_code = 0;
		break;
	default:
		reset_parse_state();
		return EC_ERROR_INVAL;
	}

	acc_write_len += write_len;

	/* the last message */
	if (xferflags & I2C_XFER_STOP) {
		switch (sb_cmd_state) {
		/* write to virtual battery */
		case START:
		case WRITE_VB:
			virtual_battery_operation(batt_cmd_head,
						&resp->data[in_len],
						0,
						acc_write_len);
			break;
		/* read from virtual battery */
		case READ_VB:
			if (cache_hit) {
				virtual_battery_operation(batt_cmd_head,
							&resp->data[0],
							in_len + read_len,
							0);
			}
			break;
		default:
			reset_parse_state();
			return EC_ERROR_INVAL;

		}
		/* Reset the state in the end of messages */
		reset_parse_state();
	}
	return EC_RES_SUCCESS;
}

void reset_parse_state(void)
{
	sb_cmd_state = IDLE;
	cache_hit = 0;
	acc_write_len = 0;
}

int virtual_battery_operation(const uint8_t *batt_cmd_head,
			      uint8_t *dest,
			      int read_len,
			      int write_len)
{
	int val;
	/*
	 * We cache battery operational mode locally for both read and write
	 * commands. If MODE_CAPACITY bit is set, battery capacity will be
	 * reported in 10mW/10mWh, instead of the default unit, mA/mAh.
	 * Note that we don't update the cached capacity: We do a real-time
	 * conversion and return the converted values.
	 */
	static uint16_t batt_mode_cache;
	const struct batt_params *curr_batt;

	curr_batt = charger_current_battery_params();
	switch (*batt_cmd_head) {
	case SB_BATTERY_MODE:
		if (write_len == 3) {
			batt_mode_cache = batt_cmd_head[1] |
					  (batt_cmd_head[2] << 8);
		} else if (read_len > 0) {
			if (batt_mode_cache == 0) {
				/*
				 * Read the battery operational mode from
				 * the battery to initialize batt_mode_cache.
				 */
				i2c_xfer(I2C_PORT_VIRTUAL_BATTERY,
					VIRTUAL_BATTERY_ADDR,
					batt_cmd_head,
					1,
					(uint8_t *)&batt_mode_cache,
					2,
					I2C_XFER_SINGLE);
			}
			memcpy(dest, &batt_mode_cache, read_len);
		}
		break;
	case SB_SERIAL_NUMBER:
		val = strtoi(host_get_memmap(EC_MEMMAP_BATT_SERIAL), NULL, 16);
		memcpy(dest, &val, read_len);
		break;
	case SB_VOLTAGE:
		memcpy(dest, &(curr_batt->voltage), read_len);
		break;
	case SB_RELATIVE_STATE_OF_CHARGE:
		memcpy(dest, &(curr_batt->state_of_charge), read_len);
		break;
	case SB_TEMPERATURE:
		memcpy(dest, &(curr_batt->temperature), read_len);
		break;
	case SB_CURRENT:
		memcpy(dest, &(curr_batt->current), read_len);
		break;
	case SB_FULL_CHARGE_CAPACITY:
		val = curr_batt->full_capacity;
		if (batt_mode_cache & MODE_CAPACITY)
			val = val * curr_batt->voltage / 10;
		memcpy(dest, &val, read_len);
		break;
	case SB_BATTERY_STATUS:
		memcpy(dest, &(curr_batt->status), read_len);
		break;
	case SB_CYCLE_COUNT:
		memcpy(dest, (int *)host_get_memmap(EC_MEMMAP_BATT_CCNT),
			read_len);
		break;
	case SB_DESIGN_CAPACITY:
		val = *(int *)host_get_memmap(EC_MEMMAP_BATT_DCAP);
		if (batt_mode_cache & MODE_CAPACITY)
			val = val * curr_batt->voltage / 10;
		memcpy(dest, &val, read_len);
		break;
	case SB_DESIGN_VOLTAGE:
		memcpy(dest, (int *)host_get_memmap(EC_MEMMAP_BATT_DVLT),
		       read_len);
		break;
	case SB_REMAINING_CAPACITY:
		val = curr_batt->remaining_capacity;
		if (batt_mode_cache & MODE_CAPACITY)
			val = val * curr_batt->voltage / 10;
		memcpy(dest, &val, read_len);
		break;
	default:
		return EC_ERROR_INVAL;
	}
	return EC_SUCCESS;
}
