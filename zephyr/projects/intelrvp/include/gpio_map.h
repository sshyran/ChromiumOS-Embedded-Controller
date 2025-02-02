/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef __ZEPHYR_GPIO_MAP_H
#define __ZEPHYR_GPIO_MAP_H

#define GPIO_EN_PP5000                  GPIO_UNIMPLEMENTED
#define GPIO_TEMP_SENSOR_POWER          GPIO_EN_PP3300_A

/* TODO: Implement GPIO_ENTERING_RW in IOEX */
#ifdef CONFIG_BOARD_MTLRVP_NPCX
#define GPIO_ENTERING_RW		GPIO_UNIMPLEMENTED
#endif /* CONFIG_BOARD_MTLRVP_NPCK */

#endif /* __ZEPHYR_GPIO_MAP_H */
