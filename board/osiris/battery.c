/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Battery pack vendor provided charging profile
 */

#include "battery_fuel_gauge.h"
#include "cbi.h"
#include "common.h"
#include "compile_time_macros.h"
#include "gpio.h"
/*
 * Battery info for all Osiris battery types. Note that the fields
 * start_charging_min/max and charging_min/max are not used for the charger.
 * The effective temperature limits are given by discharging_min/max_c.
 *
 * Fuel Gauge (FG) parameters which are used for determining if the battery
 * is connected, the appropriate ship mode (battery cutoff) command, and the
 * charge/discharge FETs status.
 *
 * Ship mode (battery cutoff) requires 2 writes to the appropriate smart battery
 * register. For some batteries, the charge/discharge FET bits are set when
 * charging/discharging is active, in other types, these bits set mean that
 * charging/discharging is disabled. Therefore, in addition to the mask for
 * these bits, a disconnect value must be specified. Note that for TI fuel
 * gauge, the charge/discharge FET status is found in Operation Status (0x54),
 * but a read of Manufacturer Access (0x00) will return the lower 16 bits of
 * Operation status which contains the FET status bits.
 *
 * The assumption for battery types supported is that the charge/discharge FET
 * status can be read with a sb_read() command and therefore, only the register
 * address, mask, and disconnect value need to be provided.
 */
const struct board_batt_params board_battery_info[] = {
	/*
	 * TODO(b:229947325): Copy kano battery AP19B8M for early support,
	 * It should remove before FSI.
	 */
	/* LGC AP19B8M Battery Information */
	[BATTERY_AP19B8M] = {
		.fuel_gauge = {
			.manuf_name = "LGC KT0030G024",
			.ship_mode = {
				.reg_addr = 0x3A,
				.reg_data = { 0xC574, 0xC574 },
			},
			.fet = {
				.reg_addr = 0x43,
				.reg_mask = 0x0001,
				.disconnect_val = 0x0,
				.cfet_mask = 0x0002,
				.cfet_off_val = 0x0000,
			}
		},
		.batt_info = {
			.voltage_max          = 13350,
			.voltage_normal       = 11610,
			.voltage_min          = 9000,
			.precharge_current    = 256,
			.start_charging_min_c = 0,
			.start_charging_max_c = 50,
			.charging_min_c       = 0,
			.charging_max_c       = 60,
			.discharging_min_c    = -20,
			.discharging_max_c    = 75,
		},
	},
	/* COSMX AP22ABN Battery Information */
	[BATTERY_COSMX_AP22ABN] = {
		.fuel_gauge = {
			.manuf_name = "COSMX KT0030B003",
			.device_name = "AP22ABN",
			.ship_mode = {
				.reg_addr = 0x3A,
				.reg_data = { 0xC574, 0xC574 },
			},
			.fet = {
				.mfgacc_support = 1,
				.reg_addr = 0x0,
				.reg_mask = 0x8000,
				.disconnect_val = 0x8000,
				.cfet_mask = 0x4000,
				.cfet_off_val = 0x4000,
			},
		},
		.batt_info = {
			.voltage_max            = 13440,
			.voltage_normal         = 11670,
			.voltage_min            = 9000,
			.precharge_current      = 567,
			.start_charging_min_c   = 0,
			.start_charging_max_c   = 50,
			.charging_min_c         = 0,
			.charging_max_c         = 60,
			.discharging_min_c      = -20,
			.discharging_max_c      = 75,
		},
	},
};
BUILD_ASSERT(ARRAY_SIZE(board_battery_info) == BATTERY_TYPE_COUNT);

const enum battery_type DEFAULT_BATTERY_TYPE = BATTERY_COSMX_AP22ABN;

enum battery_present battery_hw_present(void)
{
	/* The GPIO is low when the battery is physically present */
	return gpio_get_level(GPIO_EC_BATT_PRES_ODL) ? BP_NO : BP_YES;
}
