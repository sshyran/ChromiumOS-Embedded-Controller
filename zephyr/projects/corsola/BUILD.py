# Copyright 2021 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Define zmake projects for corsola."""

# Default chip is it8xxx2, some variants will use NPCX9X.


def register_corsola_project(
    project_name,
    chip="it8xxx2",
    extra_dts_overlays=(),
    extra_kconfig_files=(),
):
    """Register a variant of corsola."""
    register_func = register_binman_project
    if chip.startswith("npcx"):
        register_func = register_npcx_project

    register_func(
        project_name=project_name,
        zephyr_board=chip,
        dts_overlays=[
            here / "common.dts",
            here / "power_signal.dts",
            here / "usba.dts",
            *extra_dts_overlays,
        ],
        kconfig_files=[here / "prj.conf", *extra_kconfig_files],
    )


register_corsola_project(
    "krabby",
    extra_dts_overlays=[
        here / "adc_krabby.dts",
        here / "battery_krabby.dts",
        here / "gpio_krabby.dts",
        here / "i2c_krabby.dts",
        here / "interrupts_krabby.dts",
        here / "cbi_eeprom.dts",
        here / "led_krabby.dts",
        here / "motionsense_krabby.dts",
        here / "usbc_krabby.dts",
    ],
    extra_kconfig_files=[here / "prj_krabby.conf"],
)

register_corsola_project(
    project_name="kingler",
    chip="npcx9m3f",
    extra_dts_overlays=[
        here / "adc_kingler.dts",
        here / "battery_kingler.dts",
        here / "host_interface_npcx.dts",
        here / "i2c_kingler.dts",
        here / "interrupts_kingler.dts",
        here / "cbi_eeprom.dts",
        here / "gpio_kingler.dts",
        here / "led_kingler.dts",
        here / "motionsense_kingler.dts",
        here / "usbc_kingler.dts",
        here / "default_gpio_pinctrl_kingler.dts",
    ],
    extra_kconfig_files=[here / "prj_kingler.conf"],
)

register_corsola_project(
    project_name="steelix",
    chip="npcx9m3f",
    extra_dts_overlays=[
        here / "adc_kingler.dts",
        here / "battery_steelix.dts",
        here / "host_interface_npcx.dts",
        here / "i2c_kingler.dts",
        here / "interrupts_kingler.dts",
        here / "cbi_eeprom.dts",
        here / "gpio_steelix.dts",
        here / "led_steelix.dts",
        here / "motionsense_kingler.dts",
        here / "usba_steelix.dts",
        here / "usbc_kingler.dts",
        here / "default_gpio_pinctrl_kingler.dts",
    ],
    extra_kconfig_files=[
        here / "prj_kingler.conf",
        here / "prj_steelix.conf",
    ],
)
