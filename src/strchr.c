// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <errno.h>
#include <stddef.h>

char *ez_strchr(const char *s, const char c) {
	if (s == NULL) {
		errno = EINVAL;
		return NULL;
	}
	if (c == '\0')
		return (char *)s + ez_strlen(s);
	if (s[0] == '\0')
		return NULL;
	const unsigned char *us = (const unsigned char *)s;
	const unsigned char uc = (const unsigned char)c;
	while (*us != '\0') {
		if (*us == uc)
			return (char *)us;
		us++;
	}
	return NULL;
}
