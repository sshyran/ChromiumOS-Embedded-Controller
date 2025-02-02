# Copyright 2021 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Define zmake projects for it8xxx2_evb."""

register_raw_project(
    project_name="it8xxx2_evb",
    zephyr_board="it8xxx2",
    dts_overlays=[
        "adc.dts",
        "fan.dts",
        "gpio.dts",
        "i2c.dts",
        "interrupts.dts",
        "pwm.dts",
    ],
)
