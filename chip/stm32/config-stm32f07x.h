/* Copyright 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Memory mapping */
#define CONFIG_FLASH_SIZE_BYTES (128 * 1024)
#define CONFIG_FLASH_BANK_SIZE  0x1000
#define CONFIG_FLASH_ERASE_SIZE 0x0800  /* erase bank size */
#define CONFIG_FLASH_WRITE_SIZE 0x0002  /* minimum write size */

/* No page mode on STM32F, so no benefit to larger write sizes */
#define CONFIG_FLASH_WRITE_IDEAL_SIZE 0x0002

#define CONFIG_RAM_BASE         0x20000000
#define CONFIG_RAM_SIZE         0x00004000

/* Number of IRQ vectors on the NVIC */
#define CONFIG_IRQ_COUNT 32

/* Reduced history because of limited RAM */
#undef CONFIG_CONSOLE_HISTORY
#define CONFIG_CONSOLE_HISTORY 3

/* USB packet ram config */
#define CONFIG_USB_RAM_BASE        0x40006000
#define CONFIG_USB_RAM_SIZE        1024
#define CONFIG_USB_RAM_ACCESS_TYPE uint16_t
#define CONFIG_USB_RAM_ACCESS_SIZE 2

/* DFU Address */
#define STM32_DFU_BASE              0x1fffC800
