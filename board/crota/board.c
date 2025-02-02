/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "battery.h"
#include "button.h"
#include "charge_ramp.h"
#include "charger.h"
#include "common.h"
#include "compile_time_macros.h"
#include "console.h"
#include "extpower.h"
#include "gpio.h"
#include "gpio_signal.h"
#include "hooks.h"
#include "driver/accel_lis2dw12.h"
#include "driver/accelgyro_lsm6dso.h"
#include "driver/als_tcs3400.h"
#include "fw_config.h"
#include "hooks.h"
#include "lid_switch.h"
#include "power_button.h"
#include "power.h"
#include "registers.h"
#include "switch.h"
#include "tablet_mode.h"
#include "throttle_ap.h"
#include "usbc_config.h"

#include "gpio_list.h" /* Must come after other header files. */

/* Console output macros */
#define CPRINTF(format, args...) cprintf(CC_CHARGER, format, ## args)
#define CPRINTS(format, args...) cprints(CC_CHARGER, format, ## args)

__override void board_cbi_init(void)
{
	config_usb_db_type();
}

/* Called on AP S3 -> S0 transition */
static void board_chipset_resume(void)
{
	/* Allow keyboard backlight to be enabled */

	gpio_set_level(GPIO_EC_KB_BL_EN_L, 0);
}
DECLARE_HOOK(HOOK_CHIPSET_RESUME, board_chipset_resume, HOOK_PRIO_DEFAULT);

/* Called on AP S0 -> S3 transition */
static void board_chipset_suspend(void)
{
	/* Turn off the keyboard backlight if it's on. */

	gpio_set_level(GPIO_EC_KB_BL_EN_L, 1);
}
DECLARE_HOOK(HOOK_CHIPSET_SUSPEND, board_chipset_suspend, HOOK_PRIO_DEFAULT);

#ifdef CONFIG_USB_PORT_POWER_DUMB_CUSTOM_HOOK
static void usb_port_startup(void)
{
	gpio_set_level(GPIO_EN_PP5000_USBA_R, 1);
}
DECLARE_HOOK(HOOK_CHIPSET_STARTUP, usb_port_startup, HOOK_PRIO_DEFAULT);

static void usba_power(void)
{
	if (chipset_in_state(CHIPSET_STATE_ANY_OFF)) {
		if (extpower_is_present())
			gpio_set_level(GPIO_EN_PP5000_USBA_R, 1);
		else
			gpio_set_level(GPIO_EN_PP5000_USBA_R, 0);
	}
}
DECLARE_HOOK(HOOK_CHIPSET_SHUTDOWN, usba_power, HOOK_PRIO_DEFAULT);
DECLARE_HOOK(HOOK_AC_CHANGE, usba_power, HOOK_PRIO_DEFAULT);
#endif  /* CONFIG_USB_PORT_POWER_DUMB_CUSTOM_HOOK */
