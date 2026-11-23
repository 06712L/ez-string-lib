// SPDX-License-Identifier: MIT
#include "ez-string.h"

char ez_tolower(const char c) {
	if (ez_isupper(c)) {
		const unsigned char uc = (const unsigned char)c;
		return (char)(uc + (unsigned char)('a' - 'A'));
	}
	return c;
}
