// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <errno.h>

int ez_memcmp(const void *mem1, const void *mem2, const size_t n) {
	if (n == 0) {
		return 0;
	}
	if (mem1 == NULL || mem2 == NULL) {
		errno = EINVAL;
		return EZ_MEMCMP_NULL;
	}
	const unsigned char *ptr1 = (const unsigned char *)mem1,
						*ptr2 = (const unsigned char *)mem2;
	for (size_t i = 1; i < n && *ptr1 == *ptr2;
		 i++) // Avoid advancing beyond the last byte
	{
		ptr1++, ptr2++;
	}
	return *ptr1 - *ptr2;
}
