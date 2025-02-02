/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef __X86_COMMON_PWRSEQ_H__
#define __X86_COMMON_PWRSEQ_H__

#include <zephyr/logging/log.h>
#include <ap_power/ap_power_interface.h>
#include <ap_power_override_functions.h>
#include <power_signals.h>
#include <x86_power_signals.h>

/* This encapsulates the attributes of the state machine */
struct pwrseq_context {
	/* On power-on start boot up sequence */
	enum power_states_ndsx power_state;
	/* Indicate should exit G3 power state or not */
	bool want_g3_exit;
	/* Indicate to exit G3 state or not with delay in ms*/
	uint32_t reboot_ap_at_g3_delay_ms;

};

#endif /* __X86_COMMON_PWRSEQ_H__ */
