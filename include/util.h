/* Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Various utility functions and macros */

#ifndef __CROS_EC_UTIL_H
#define __CROS_EC_UTIL_H

#include "common.h"
#include "compile_time_macros.h"
#include "panic.h"

#include "builtin/assert.h"         /* For ASSERT(). */
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Standard macros / definitions */
#ifndef MAX
#define MAX(a, b)					\
	({						\
		__typeof__(a) temp_a = (a);		\
		__typeof__(b) temp_b = (b);		\
							\
		temp_a > temp_b ? temp_a : temp_b;	\
	})
#endif
#ifndef MIN
#define MIN(a, b)					\
	({						\
		__typeof__(a) temp_a = (a);		\
		__typeof__(b) temp_b = (b);		\
							\
		temp_a < temp_b ? temp_a : temp_b;	\
	})
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * Convert a pointer to a base struct into a pointer to the struct that
 * contains the base struct.  This requires knowing where in the contained
 * struct the base struct resides, this is the member parameter to downcast.
 */
#define DOWNCAST(pointer, type, member)					\
	((type *)(((uint8_t *) pointer) - offsetof(type, member)))

/* True of x is a power of two */
#define POWER_OF_TWO(x) (x && !(x & (x - 1)))

/* find the most significant bit. Not defined in n == 0. */
#define __fls(n) (31 - __builtin_clz(n))

/*
 * macros for integer division with various rounding variants
 * default integer division rounds down.
 */
#define DIV_ROUND_UP(x, y) (((x) + ((y) - 1)) / (y))
#define DIV_ROUND_NEAREST(x, y) (((x) + ((y) / 2)) / (y))

#ifndef HIDE_EC_STDLIB
/* Standard library functions */
__stdlib_compat int atoi(const char *nptr);
__stdlib_compat int isdigit(int c);
__stdlib_compat int isspace(int c);
__stdlib_compat int isalpha(int c);
__stdlib_compat int isprint(int c);
__stdlib_compat int memcmp(const void *s1, const void *s2, size_t len);
__stdlib_compat void *memcpy(void *dest, const void *src, size_t len);
__stdlib_compat __visible void *memset(void *dest, int c, size_t len);
__stdlib_compat void *memmove(void *dest, const void *src, size_t len);
__stdlib_compat void *memchr(const void *buffer, int c, size_t n);
__stdlib_compat int strcasecmp(const char *s1, const char *s2);
__stdlib_compat int strncasecmp(const char *s1, const char *s2, size_t size);
__stdlib_compat size_t strlen(const char *s);
__stdlib_compat size_t strnlen(const char *s, size_t maxlen);
__stdlib_compat char *strncpy(char *dest, const char *src, size_t n);
__stdlib_compat int strncmp(const char *s1, const char *s2, size_t n);

/* Like strtol(), but for integers. */
__stdlib_compat int strtoi(const char *nptr, char **endptr, int base);
__stdlib_compat uint64_t strtoul(const char *nptr, char **endptr, int base);

/* Like strncpy(), but guarantees null termination. */
__stdlib_compat char *strzcpy(char *dest, const char *src, int len);

/**
 * Parses a boolean option from a string.
 *
 * Strings that set *dest=0 and return 1 (all case-insensitive):
 *   "off"
 *   "dis*"
 *   "n*"
 *   "f*"
 *
 * Strings that set *dest=1 and return 1 (all case-insensitive):
 *   "on"
 *   "ena*"
 *   "y*"
 *   "t*"
 *
 * Other strings return 0 and leave *dest unchanged.
 */
__stdlib_compat int parse_bool(const char *s, int *dest);

__stdlib_compat int tolower(int c);
#endif  /* !HIDE_EC_STDLIB */

/**
 * Constant time implementation of memcmp to avoid timing side channels.
 */
int safe_memcmp(const void *s1, const void *s2, size_t len);

/* 64-bit divide-and-modulo.  Does the equivalent of:
 *
 *   r = *n % d;
 *   *n /= d;
 *   return r;
 */
int uint64divmod(uint64_t *v, int by);

/**
 * Get-and-clear next bit from mask.
 *
 * Starts with most significant bit.
 *
 * @param mask Bitmask to extract next bit from. Must NOT be zero.
 * @return bit position (0..31)
 */
int get_next_bit(uint32_t *mask);

/**
 * Check if |buffer| is full of 0x00 or 0xff.
 *
 * This function runs in constant execution time and is not vulnerable to
 * timing attacks.
 *
 * @param buffer the buffer to check.
 * @param size the number of bytes to check.
 * @return true if |buffer| is full of 0x00 or 0xff, false otherwise.
 */
bool bytes_are_trivial(const uint8_t *buffer, size_t size);

/**
 * Reverse's the byte-order of the provided buffer.
 */
void reverse(void *dest, size_t len);


/****************************************************************************/
/* Conditional stuff.
 *
 * We often need to watch for transitions between one state and another, so
 * that we can issue warnings or take action ONCE. This abstracts that "have I
 * already reacted to this" stuff into a single set of functions.
 *
 * For example:
 *
 *     cond_t c;
 *
 *     cond_init_false(&c);
 *
 *     while(1) {
 *         int val = read_some_gpio();
 *         cond_set(&c, val);
 *
 *         if (cond_went_true(&c))
 *             host_event(SOMETHING_HAPPENED);
 *     }
 *
 */
typedef uint8_t cond_t;

/* Initialize a conditional to a specific state. Do this first. */
void cond_init(cond_t *c, int boolean);
static inline void cond_init_false(cond_t *c) { cond_init(c, 0); }
static inline void cond_init_true(cond_t *c) { cond_init(c, 1); }

/* Set the current state. Do this as often as you like. */
void cond_set(cond_t *c, int boolean);
static inline void cond_set_false(cond_t *c) { cond_set(c, 0); }
static inline void cond_set_true(cond_t *c) { cond_set(c, 1); }

/* Get the current state. Do this as often as you like. */
int cond_is(cond_t *c, int boolean);
static inline int cond_is_false(cond_t *c) { return cond_is(c, 0); }
static inline int cond_is_true(cond_t *c) { return cond_is(c, 1); }

/* See if the state has transitioned. If it has, the corresponding function
 * will return true ONCE only, until it's changed back.
 */
int cond_went(cond_t *c, int boolean);
static inline int cond_went_false(cond_t *c) { return cond_went(c, 0); }
static inline int cond_went_true(cond_t *c) { return cond_went(c, 1); }

/****************************************************************************/
/* Console command parsing */

/* Parse command-line arguments given integer shift value to obtain
 * offset and size.
 */
int parse_offset_size(int argc, char **argv, int shift,
			     int *offset, int *size);

#ifdef __cplusplus
}
#endif

#endif  /* __CROS_EC_UTIL_H */
