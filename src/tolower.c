// SPDX-License-Identifier: MIT
#include "ez-string.h"

char ez_tolower(const char c) {
	const unsigned char uc = (const unsigned char)c;
	if (uc >= 'A' && uc <= 'Z') {
		return (char)(uc + (unsigned char)('a' - 'A'));
	}
	return c;
}
