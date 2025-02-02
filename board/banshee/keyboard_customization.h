/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Keyboard configuration */

#ifndef __KEYBOARD_CUSTOMIZATION_H
#define __KEYBOARD_CUSTOMIZATION_H

/*
 * KEYBOARD_COLS_MAX has the build time column size. It's used to allocate
 * exact spaces for arrays. Actual keyboard scanning is done using
 * keyboard_cols, which holds a runtime column size.
 */
#define KEYBOARD_COLS_MAX 16
#define KEYBOARD_ROWS 8

/*
 * WARNING: Do not directly modify it. You should call keyboard_raw_set_cols,
 * instead. It checks whether you're eligible or not.
 */
extern uint8_t keyboard_cols;

#define KEYBOARD_ROW_TO_MASK(r) (1 << (r))

/* Columns and masks for keys we particularly care about */
#define KEYBOARD_COL_DOWN	8
#define KEYBOARD_ROW_DOWN	1
#define KEYBOARD_MASK_DOWN	KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_DOWN)
#define KEYBOARD_COL_ESC	5
#define KEYBOARD_ROW_ESC	7
#define KEYBOARD_MASK_ESC	KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_ESC)
#define KEYBOARD_COL_KEY_H	7
#define KEYBOARD_ROW_KEY_H	2
#define KEYBOARD_MASK_KEY_H	KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_KEY_H)
#define KEYBOARD_COL_KEY_R	6
#define KEYBOARD_ROW_KEY_R	6
#define KEYBOARD_MASK_KEY_R	KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_KEY_R)
#define KEYBOARD_COL_LEFT_ALT	3
#define KEYBOARD_ROW_LEFT_ALT	1
#define KEYBOARD_MASK_LEFT_ALT	KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_LEFT_ALT)
#define KEYBOARD_COL_REFRESH	4
#define KEYBOARD_ROW_REFRESH	6
#define KEYBOARD_MASK_REFRESH	KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_REFRESH)
#define KEYBOARD_COL_RIGHT_ALT	3
#define KEYBOARD_ROW_RIGHT_ALT	0
#define KEYBOARD_MASK_RIGHT_ALT	KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_RIGHT_ALT)
#define KEYBOARD_DEFAULT_COL_VOL_UP	13
#define KEYBOARD_DEFAULT_ROW_VOL_UP	3
#define KEYBOARD_COL_LEFT_CTRL  12
#define KEYBOARD_ROW_LEFT_CTRL  1
#define KEYBOARD_MASK_LEFT_CTRL KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_LEFT_CTRL)
#define KEYBOARD_COL_RIGHT_CTRL 12
#define KEYBOARD_ROW_RIGHT_CTRL 0
#define KEYBOARD_MASK_RIGHT_CTRL KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_RIGHT_CTRL)
#define KEYBOARD_COL_SEARCH     4
#define KEYBOARD_ROW_SEARCH     4
#define KEYBOARD_MASK_SEARCH    KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_SEARCH)
#define KEYBOARD_COL_KEY_0      13
#define KEYBOARD_ROW_KEY_0      4
#define KEYBOARD_MASK_KEY_0     KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_KEY_0)
#define KEYBOARD_COL_KEY_1      2
#define KEYBOARD_ROW_KEY_1      5
#define KEYBOARD_MASK_KEY_1     KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_KEY_1)
#define KEYBOARD_COL_KEY_2      5
#define KEYBOARD_ROW_KEY_2      5
#define KEYBOARD_MASK_KEY_2     KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_KEY_2)
#define KEYBOARD_COL_LEFT_SHIFT 9
#define KEYBOARD_ROW_LEFT_SHIFT 1
#define KEYBOARD_MASK_LEFT_SHIFT KEYBOARD_ROW_TO_MASK(KEYBOARD_ROW_LEFT_SHIFT)

void board_id_keyboard_col_inverted(int board_id);


#endif /* __KEYBOARD_CUSTOMIZATION_H */
