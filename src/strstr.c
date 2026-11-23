// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static inline bool check_size(const char *str, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (str[i] == '\0')
			return false;
	}
	return true;
}

static inline char *strstr_2c(const unsigned char *uhaystack,
							  const unsigned char *uneedle) {
	const uint32_t needle =
		((uint32_t)uneedle[0] << 16U) | (uint32_t)uneedle[1];
	uint32_t haystack =
		((uint32_t)uhaystack[0] << 16U) | (uint32_t)uhaystack[1];
	uhaystack += 2; // check unfilled character
	for (uint8_t c = *uhaystack; c != '\0' && needle != haystack;
		 c = *++uhaystack) {
		haystack = ((uint32_t)haystack << 16U) | c;
	}
	if (needle == haystack)
		return (char *)uhaystack - 2;
	return NULL;
}

static inline char *strstr_3c(const unsigned char *uhaystack,
							  const unsigned char *uneedle) {
	const uint32_t needle = ((uint32_t)uneedle[0] << 16U) |
							((uint32_t)uneedle[1] << 8U) | (uint32_t)uneedle[2];
	uint32_t haystack = ((uint32_t)uhaystack[0] << 16U) |
						((uint32_t)uhaystack[1] << 8U) | (uint32_t)uhaystack[2];
	uhaystack += 3; // check unfilled character
	for (uint8_t c = *uhaystack; c != '\0' && needle != haystack;
		 c = *++uhaystack) {
		haystack = ((uint32_t)uhaystack[-2] << 16U) |
				   ((uint32_t)uhaystack[-1] << 8U) | c;
	}
	if (needle == haystack)
		return (char *)uhaystack - 3;
	return NULL;
}

static inline void maximal_suffix(const unsigned char *uneedle,
								  const size_t needle_len,
								  const unsigned char **split, size_t *p) {
	struct ms {
		size_t ms;
		size_t p;
	};
	struct ms results[2]; // [0] = lo, [1] = rlo
	for (uint8_t i = 0; i < 2; i++) {
		size_t tmp_ms = 0, j = 1;
		size_t tmp_p = 0;
		for (size_t k = 0; j + k < needle_len;) {
			const unsigned char c1 = uneedle[j + k], c2 = uneedle[tmp_ms + k];
			if ((i == 0) ? (c1 < c2) : (c1 > c2)) {
				j += k + 1;
				k = 0;
				tmp_p = j - tmp_ms - 1;
			} else if (c1 == c2) {
				if (k != tmp_p) {
					k++;
				} else {
					j += tmp_p + 1;
					k = 0;
				}
			} else {
				tmp_ms = j;
				j++;
				k = 0;
				tmp_p = 0;
			}
		}
		results[i].ms = tmp_ms;
		results[i].p = tmp_p + 1;
	}

	// Return results
	const bool use_rlo = results[0].ms <= results[1].ms;
	*split = uneedle + results[use_rlo].ms;
	*p = results[use_rlo].p;
}

char *ez_strstr(const char *haystack, const char *needle) {
	if (haystack == NULL || needle == NULL) {
		errno = EINVAL;
		return NULL;
	}
	if (needle[0] == '\0' || haystack == needle)
		return (char *)haystack;
	const unsigned char *uhaystack = (const unsigned char *)haystack,
						*uneedle = (const unsigned char *)needle;

	uhaystack = (const unsigned char *)ez_strchr((const char *)uhaystack,
												 (char)uneedle[0]);

	// Handle short str
	if (uhaystack == NULL)
		return NULL;
	if (uneedle[1] == '\0')
		return (char *)uhaystack;
	else if (uneedle[2] == '\0') {
		if (!check_size((const char *)uhaystack, 2))
			return NULL;
		return strstr_2c(uhaystack, uneedle);
	} else if (uneedle[3] == '\0') {
		if (!check_size((const char *)uhaystack, 3))
			return NULL;
		return strstr_3c(uhaystack, uneedle);
	}

	// Get maximal suffix
	const size_t needle_len = ez_strlen(needle);
	const unsigned char *split;
	size_t p;
	maximal_suffix(uneedle, needle_len, &split, &p);
	const size_t right_needle_len = needle_len - (size_t)(split - uneedle);
	const size_t left_needle_len = needle_len - right_needle_len;

	// Decide move mode
	size_t move_dist = (left_needle_len > right_needle_len) ? left_needle_len
															: right_needle_len;
	if (left_needle_len <= right_needle_len) {
		if (ez_memcmp(uneedle, split, left_needle_len)) {
			move_dist = (left_needle_len > right_needle_len);
		}
	}

	// Start search
	const unsigned char *uh_ptr = uhaystack;
	while (1) {
		size_t i = 0;
		while (i < right_needle_len) {
			if (uh_ptr[i] == '\0') {
				return NULL;
			}
			if (split[i] != uh_ptr[i]) {
				break;
			}
			i++;
		}
		if (i == right_needle_len) {
			const unsigned char *left_ptr = uh_ptr - left_needle_len;
			if (ez_memcmp(split - left_needle_len, left_ptr, left_needle_len) ==
				0) {
				return (char *)left_ptr;
			} else {
				uh_ptr += move_dist;
			}
		} else {
			uh_ptr += i + 1;
			continue;
		}
	}
}
