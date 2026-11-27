// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <errno.h>
#include <stddef.h>

void *ez_memcpy(void *target, const void *src, const size_t n) {
	if (target == NULL || src == NULL) {
		errno = EINVAL;
		return NULL;
	}
	if (n == 0) {
		return target;
	}

	const unsigned char *src_ptr = (unsigned char *)src;
	unsigned char *target_ptr = (unsigned char *)target;
	for (size_t i = 0; i < n; i++, src_ptr++, target_ptr++) {
		*target_ptr = *src_ptr;
	}
	return target;
}
