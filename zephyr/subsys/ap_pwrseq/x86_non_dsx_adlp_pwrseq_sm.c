/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <x86_non_dsx_common_pwrseq_sm_handler.h>

LOG_MODULE_DECLARE(ap_pwrseq, CONFIG_AP_PWRSEQ_LOG_LEVEL);

static void ap_off(void)
{
	power_signal_set(PWR_VCCST_PWRGD, 0);
	power_signal_set(PWR_PCH_PWROK, 0);
	power_signal_set(PWR_EC_PCH_SYS_PWROK, 0);
}

static int check_pch_out_of_suspend(void)
{
	int ret;
	/*
	 * Wait for SLP_SUS deasserted.
	 */
	ret = power_wait_mask_signals_timeout(IN_PCH_SLP_SUS,
					      0,
					      IN_PCH_SLP_SUS_WAIT_TIME_MS);
	if (ret == 0) {
		LOG_DBG("SLP_SUS now %d", power_signal_get(PWR_SLP_SUS));
		return 1;
	}
	LOG_ERR("wait SLP_SUS deassertion timeout");
	return 0; /* timeout */
}

/* Handle ALL_SYS_PWRGD signal
 * This will be overridden if the custom signal handler is needed
 */
int all_sys_pwrgd_handler(void)
{
	int retry = 0;

	/* TODO: Add condition for no power sequencer */
	k_msleep(AP_PWRSEQ_DT_VALUE(all_sys_pwrgd_timeout));

	if (power_signal_get(PWR_DSW_PWROK) == 0) {
	/* Todo: Remove workaround for the retry
	 * without this change the system hits G3 as it detects
	 * ALL_SYS_PWRGD as 0 and then 1 as a glitch
	 */
		while (power_signal_get(PWR_ALL_SYS_PWRGD) == 0) {
			if (++retry > 2) {
				LOG_ERR("PG_EC_ALL_SYS_PWRGD not ok");
				ap_off();
				return -1;
			}
			k_msleep(10);
		}
	}

	/* PG_EC_ALL_SYS_PWRGD is asserted, enable VCCST_PWRGD_OD. */

	if (power_signal_get(PWR_VCCST_PWRGD) == 0) {
		k_msleep(AP_PWRSEQ_DT_VALUE(vccst_pwrgd_delay));
		power_signal_set(PWR_VCCST_PWRGD, 1);
	}
	return 0;
}

/* Generate SYS_PWROK->SOC if needed by system */
void generate_sys_pwrok_handler(void)
{
	/* Enable PCH_SYS_PWROK. */
	if (power_signal_get(PWR_EC_PCH_SYS_PWROK) == 0) {
		k_msleep(AP_PWRSEQ_DT_VALUE(sys_pwrok_delay));
		/* Check if we lost power while waiting. */
		if (power_signal_get(PWR_ALL_SYS_PWRGD) == 0) {
			LOG_DBG("PG_EC_ALL_SYS_PWRGD deasserted, "
				"shutting AP off!");
			ap_off();
			return;
		}
		LOG_INF("Turning on PWR_EC_PCH_SYS_PWROK");
		power_signal_set(PWR_EC_PCH_SYS_PWROK, 1);
		/* PCH will now release PLT_RST */
	}
}

/* Chipset specific power state machine handler */

/* TODO: Separate with and without power sequencer logic here */

void s0_action_handler(void)
{
	int ret;

	/* Handle DSW_PWROK passthrough */
	/* This is not needed for alderlake silego, guarded by CONFIG? */

	/* Check ALL_SYS_PWRGD and take action */
	ret = all_sys_pwrgd_handler();
	if (ret) {
		LOG_DBG("ALL_SYS_PWRGD handling failed err= %d", ret);
		return;
	}

	/* Send PCH_PWROK->SoC if conditions met */
	/* TODO: There is possibility of EC not needing to generate
	 * this as power sequencer may do it
	 */
	ret = board_ap_power_assert_pch_power_ok();
	if (ret) {
		LOG_DBG("PCH_PWROK handling failed err=%d", ret);
		return;
	}

	/* SYS_PWROK may be optional and the delay must be
	 * configurable as it is variable with platform
	 */
	/* Send SYS_PWROK->SoC if conditions met */
	generate_sys_pwrok_handler();
}

void s3s0_action_handler(void)
{
}

void s0s3_action_handler(void)
{
	ap_off();
}

enum power_states_ndsx g3s5_action_handler(void)
{
	/*
	 * Now wait for SLP_SUS_L to go high based on tPCH32. If this
	 * signal doesn't go high within 250 msec then go back to G3.
	 */
	if (check_pch_out_of_suspend()) {
		ap_power_ev_send_callbacks(AP_POWER_PRE_INIT);
		return SYS_POWER_STATE_G3S5;
	}
	return SYS_POWER_STATE_S5G3;
}

enum power_states_ndsx chipset_pwr_sm_run(enum power_states_ndsx curr_state)
{
	/* Add chipset specific state handling if any */
	switch (curr_state) {
	case SYS_POWER_STATE_G3S5:
		board_ap_power_action_g3_s5();
		curr_state = g3s5_action_handler();
		break;
	case SYS_POWER_STATE_S5:
		break;
	case SYS_POWER_STATE_S3S0:
		board_ap_power_action_s3_s0();
		s3s0_action_handler();
		break;
	case SYS_POWER_STATE_S0S3:
		board_ap_power_action_s0_s3();
		s0s3_action_handler();
		break;
	case SYS_POWER_STATE_S0:
		board_ap_power_action_s0();
		s0_action_handler();
		break;
	default:
		break;
	}
	return curr_state;
}
