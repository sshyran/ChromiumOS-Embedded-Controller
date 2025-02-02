/* Copyright 2021 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#define DT_DRV_COMPAT cros_ec_pwm_leds

#include <string.h>
#include <zephyr/devicetree.h>

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

#include "charge_manager.h"
#include "common.h"
#include "ec_commands.h"
#include "hooks.h"
#include "led_common.h"
#include "led_pwm.h"
#include "util.h"

LOG_MODULE_REGISTER(pwm_led, LOG_LEVEL_ERR);

BUILD_ASSERT(DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) <= 1,
	     "Multiple CrOS EC PWM LED instances defined");
BUILD_ASSERT(DT_INST_PROP_LEN(0, leds) <= 2,
	     "Unsupported number of LEDs defined");

#define PWM_LED_PERIOD_NS (NSEC_PER_SEC/DT_INST_PROP(0, frequency))
#define PWM_SIDESEL_PERIOD_NS (PWM_LED_PERIOD_NS * 2)

#define PWM_LED_NAME(node_id) DT_STRING_UPPER_TOKEN(node_id, ec_led_name)
#define PWM_LED_NAME_WITH_COMMA(node_id) PWM_LED_NAME(node_id),

const enum ec_led_id supported_led_ids[] = {
	DT_INST_FOREACH_CHILD(0, PWM_LED_NAME_WITH_COMMA)
};
const int supported_led_ids_count = ARRAY_SIZE(supported_led_ids);

BUILD_ASSERT(ARRAY_SIZE(supported_led_ids) == DT_INST_PROP_LEN(0, leds),
	     "Mismatch count of LED device phandles and LED name map entries.");

static void pwm_led_set_duty(const struct pwm_led_dt_channel *ch, int percent)
{
	uint32_t pulse_ns;
	int rv;

	if (!device_is_ready(ch->dev)) {
		LOG_ERR("PWM device %s not ready", ch->dev->name);
		return;
	}

	pulse_ns = DIV_ROUND_NEAREST(ch->period_ns * percent, 100);

	LOG_DBG("LED PWM %s set percent (%d), pulse %d", ch->dev->name, percent,
		pulse_ns);

	rv = pwm_set(ch->dev, ch->channel, ch->period_ns, pulse_ns, ch->flags);
	if (rv) {
		LOG_ERR("pwm_set() failed %s (%d)", ch->dev->name, rv);
	}
}

#define PWM_CHANNEL_DT_BY_IDX_INIT(node_id, led_ch, _period_ns)             \
	{                                                                   \
		.dev = DEVICE_DT_GET(DT_PWMS_CTLR_BY_IDX(node_id, led_ch)), \
		.channel = DT_PWMS_CHANNEL_BY_IDX(node_id, led_ch),         \
		.flags = DT_PWMS_FLAGS_BY_IDX(node_id, led_ch),             \
		.period_ns = _period_ns, \
	}

#define PWM_CHANNEL_DT_BY_IDX(node_id, prop, idx, led_ch)                      \
	static const struct pwm_led_dt_channel _pwm_led_dt_##idx##_ch_##led_ch = \
		PWM_CHANNEL_DT_BY_IDX_INIT(                                    \
			DT_PHANDLE_BY_IDX(node_id, prop, idx), led_ch,         \
			PWM_LED_PERIOD_NS);

#define PWM_CHANNEL_DT_BY_IDX_COND(node_id, prop, idx, led_ch)        \
	IF_ENABLED(DT_PROP_HAS_IDX(                                   \
		DT_PHANDLE_BY_IDX(node_id, prop, idx), pwms, led_ch), \
		(PWM_CHANNEL_DT_BY_IDX(node_id, prop, idx, led_ch))   \
		)

#define PWM_LED_DT_INIT(node_id, prop, idx) \
	PWM_CHANNEL_DT_BY_IDX_COND(node_id, prop, idx, 0) \
	PWM_CHANNEL_DT_BY_IDX_COND(node_id, prop, idx, 1) \
	PWM_CHANNEL_DT_BY_IDX_COND(node_id, prop, idx, 2)

DT_INST_FOREACH_PROP_ELEM(0, leds, PWM_LED_DT_INIT)

#define PWM_CHANNEL_BY_IDX_COND(node_id, prop, idx, led_ch)           \
	COND_CODE_1(DT_PROP_HAS_IDX(                                  \
		DT_PHANDLE_BY_IDX(node_id, prop, idx), pwms, led_ch), \
		(&_pwm_led_dt_##idx##_ch_##led_ch), \
		(PWM_LED_NO_CHANNEL))

#define PWM_LED_INIT(node_id, prop, idx) \
	[PWM_LED##idx] = { \
		.ch0 = PWM_CHANNEL_BY_IDX_COND(node_id, prop, idx, 0), \
		.ch1 = PWM_CHANNEL_BY_IDX_COND(node_id, prop, idx, 1), \
		.ch2 = PWM_CHANNEL_BY_IDX_COND(node_id, prop, idx, 2), \
		.set_duty = &pwm_led_set_duty, \
	},

struct pwm_led pwm_leds[] = {
	DT_INST_FOREACH_PROP_ELEM(0, leds, PWM_LED_INIT)
};

#define EC_LED_COLOR_BLANK {0}

struct pwm_led_color_map led_color_map[EC_LED_COLOR_COUNT] = {
	[EC_LED_COLOR_RED]    = DT_INST_PROP_OR(0, color_map_red,
						EC_LED_COLOR_BLANK),
	[EC_LED_COLOR_GREEN]  = DT_INST_PROP_OR(0, color_map_green,
						EC_LED_COLOR_BLANK),
	[EC_LED_COLOR_BLUE]   = DT_INST_PROP_OR(0, color_map_blue,
						EC_LED_COLOR_BLANK),
	[EC_LED_COLOR_YELLOW] = DT_INST_PROP_OR(0, color_map_yellow,
						EC_LED_COLOR_BLANK),
	[EC_LED_COLOR_WHITE]  = DT_INST_PROP_OR(0, color_map_white,
						EC_LED_COLOR_BLANK),
	[EC_LED_COLOR_AMBER]  = DT_INST_PROP_OR(0, color_map_amber,
						EC_LED_COLOR_BLANK),
};

BUILD_ASSERT(DT_INST_PROP_LEN(0, brightness_range) == EC_LED_COLOR_COUNT,
	     "brightness_range must have exactly EC_LED_COLOR_COUNT values");

static const uint8_t dt_brigthness_range[EC_LED_COLOR_COUNT] = DT_INST_PROP(
		0, brightness_range);

void led_get_brightness_range(enum ec_led_id led_id, uint8_t *brightness_range)
{
	/* led_id is ignored, same ranges for all LEDs */
	memcpy(brightness_range, dt_brigthness_range,
	       sizeof(dt_brigthness_range));
}

#define PWM_NAME_TO_ID(node_id) \
	case PWM_LED_NAME(node_id): \
		pwm_id = DT_REG_ADDR(node_id); \
		break;

int led_set_brightness(enum ec_led_id led_id, const uint8_t *brightness)
{
	enum pwm_led_id pwm_id;

	switch (led_id) {
	DT_INST_FOREACH_CHILD(0, PWM_NAME_TO_ID)
	default:
		return EC_ERROR_UNKNOWN;
	}

	if (DT_INST_NODE_HAS_PROP(0, color_map_red) &&
	    brightness[EC_LED_COLOR_RED]) {
		set_pwm_led_color(pwm_id, EC_LED_COLOR_RED);
	} else if (DT_INST_NODE_HAS_PROP(0, color_map_green) &&
		 brightness[EC_LED_COLOR_GREEN]) {
		set_pwm_led_color(pwm_id, EC_LED_COLOR_GREEN);
	} else if (DT_INST_NODE_HAS_PROP(0, color_map_blue) &&
			brightness[EC_LED_COLOR_BLUE]) {
		set_pwm_led_color(pwm_id, EC_LED_COLOR_BLUE);
	} else if (DT_INST_NODE_HAS_PROP(0, color_map_yellow) &&
			brightness[EC_LED_COLOR_YELLOW]) {
		set_pwm_led_color(pwm_id, EC_LED_COLOR_YELLOW);
	} else if (DT_INST_NODE_HAS_PROP(0, color_map_white) &&
			brightness[EC_LED_COLOR_WHITE]) {
		set_pwm_led_color(pwm_id, EC_LED_COLOR_WHITE);
	} else if (DT_INST_NODE_HAS_PROP(0, color_map_amber) &&
			brightness[EC_LED_COLOR_AMBER]) {
		set_pwm_led_color(pwm_id, EC_LED_COLOR_AMBER);
	} else {
		/* Otherwise, the "color" is "off". */
		set_pwm_led_color(pwm_id, -1);
	}

	return EC_SUCCESS;
}

#if DT_INST_NODE_HAS_PROP(0, sidesel)

static const struct pwm_led_dt_channel _pwm_led_dt_sidesel =
	PWM_CHANNEL_DT_BY_IDX_INIT(DT_INST_PROP(0, sidesel), 0,
				   PWM_SIDESEL_PERIOD_NS);

/* Illuminates the LED on the side of the active charging port. If not charging,
 * illuminates both LEDs.
 */
static void led_set_charge_port_tick(void)
{
	int port;
	int side_select_duty;

	port = charge_manager_get_active_charge_port();
	switch (port) {
	case 0:
		side_select_duty = 100;
		break;
	case 1:
		side_select_duty = 0;
		break;
	default:
		side_select_duty = 50;
	}

	if (led_auto_control_is_enabled(EC_LED_ID_POWER_LED))
		pwm_led_set_duty(&_pwm_led_dt_sidesel, side_select_duty);
}
DECLARE_HOOK(HOOK_TICK, led_set_charge_port_tick, HOOK_PRIO_DEFAULT);

static void board_led_init(void)
{
	/* Illuminate motherboard and daughter board LEDs equally to start. */
	pwm_led_set_duty(&_pwm_led_dt_sidesel, 50);
}
DECLARE_HOOK(HOOK_INIT, board_led_init, HOOK_PRIO_DEFAULT);

#endif /* DT_INST_NODE_HAS_PROP(0, sidesel) */

#endif /* DT_HAS_COMPAT_STATUS_OKAY */
