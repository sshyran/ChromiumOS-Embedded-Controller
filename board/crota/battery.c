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
 * Battery info for all Brya battery types. Note that the fields
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
	/* ATL GB-S40-496570-010H Battery Information */
	[BATTERY_ATL] = {
		.fuel_gauge = {
			.manuf_name = "ATL-ATL3.66",
			.device_name = "DELL CFD72",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17600,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 60,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= 0,
			.discharging_max_c	= 60,
		},
	},
	/* BYD 13076993-009 Battery Information */
	[BATTERY_BYD] = {
		.fuel_gauge = {
			.manuf_name = "BYD",
			.device_name = "DELL WV3K8",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17400,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 60,
			.charging_min_c		= 0,
			.charging_max_c		= 60,
			.discharging_min_c	= 0,
			.discharging_max_c	= 70,
		},
	},
	/* CosMX B00C496570D0002 Battery Information */
	[BATTERY_COM] = {
		.fuel_gauge = {
			.manuf_name = "COM",
			.device_name = "DELL MVK11",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17600,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= -17,
			.discharging_max_c	= 70,
		},
	},
	/* LGES MPPDELWM4C1N Battery Information */
	[BATTERY_LGC] = {
		.fuel_gauge = {
			.manuf_name = "LGC-LGC3.600",
			.device_name = "DELL XPHX8",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17600,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= 0,
			.discharging_max_c	= 70,
		},
	},
	/* SMP 999QA455H Battery Information */
	[BATTERY_SMP_ATL3] = {
		.fuel_gauge = {
			.manuf_name = "SMP-ATL3.66",
			.device_name = "DELL XDY9K",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17600,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= -14,
			.discharging_max_c	= 70,
		},
	},
	/* SMP 999QA454H Battery Information */
	[BATTERY_SMP_COS3] = {
		.fuel_gauge = {
			.manuf_name = "SMP-COS3.66",
			.device_name = "DELL XDY9K",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17600,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= -14,
			.discharging_max_c	= 70,
		},
	},
	/* SWD 1002000008482 Battery Information */
	[BATTERY_SWD_ATL3] = {
		.fuel_gauge = {
			.manuf_name = "SWD-ATL3.661",
			.device_name = "DELL VKYJX",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17600,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= 0,
			.discharging_max_c	= 70,
		},
	},
	/* SWD 1002000008492 Battery Information */
	[BATTERY_SWD_COS3] = {
		.fuel_gauge = {
			.manuf_name = "SWD-COS3.661",
			.device_name = "DELL VKYJX",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17600,  /* mV */
			.voltage_normal		= 15000,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= 0,
			.discharging_max_c	= 70,
		},
	},
	/* SMP 999QA485H Battery Information */
	[BATTERY_SMP_ATL4] = {
		.fuel_gauge = {
			.manuf_name = "SMP-ATL4.24",
			.device_name = "DELL N9XX1",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17800,  /* mV */
			.voltage_normal		= 15200,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= -14,
			.discharging_max_c	= 70,
		},
	},
	/* SMP 999QA486H Battery Information */
	[BATTERY_SMP_COS4] = {
		.fuel_gauge = {
			.manuf_name = "SMP-COS4.26",
			.device_name = "DELL N9XX1",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17800,  /* mV */
			.voltage_normal		= 15200,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= -14,
			.discharging_max_c	= 70,
		},
	},
	/* Sunwoda 1002000009262 Battery Information */
	[BATTERY_SWD_ATL4] = {
		.fuel_gauge = {
			.manuf_name = "SWD-ATL4.242",
			.device_name = "DELL 3RR09",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17800,  /* mV */
			.voltage_normal		= 15200,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= 0,
			.discharging_max_c	= 70,
		},
	},
	/* Sunwoda 1002000009272 Battery Information */
	[BATTERY_SWD_COS4] = {
		.fuel_gauge = {
			.manuf_name = "SWD-COS4.264",
			.device_name = "DELL 3RR09",
			.ship_mode = {
				.reg_addr = 0x00,
				.reg_data = { 0x0010, 0x0010 },
			},
			.fet = {
				.mfgacc_support = 0,
				.reg_addr = 0x00,
				.reg_mask = 0x2000,
				.disconnect_val = 0x2000,
			}
		},
		.batt_info = {
			.voltage_max		= 17800,  /* mV */
			.voltage_normal		= 15200,  /* mV */
			.voltage_min		= 12000,  /* mV */
			.precharge_current	= 256,	  /* mA */
			.start_charging_min_c	= 0,
			.start_charging_max_c	= 50,
			.charging_min_c		= 0,
			.charging_max_c		= 50,
			.discharging_min_c	= 0,
			.discharging_max_c	= 70,
		},
	},
};
BUILD_ASSERT(ARRAY_SIZE(board_battery_info) == BATTERY_TYPE_COUNT);

const enum battery_type DEFAULT_BATTERY_TYPE = BATTERY_ATL;

enum battery_present battery_hw_present(void)
{
	enum gpio_signal batt_pres;

	batt_pres = GPIO_EC_BATT_PRES_ODL;

	/* The GPIO is low when the battery is physically present */
	return gpio_get_level(batt_pres) ? BP_NO : BP_YES;
}
