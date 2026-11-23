// SPDX-License-Identifier: MIT
#include "ez-string.h"

char ez_toupper(const char c) {
	if (ez_islower(c)) {
		const unsigned char uc = (const unsigned char)c;
		return (char)(uc - (unsigned char)('a' - 'A'));
	}
	return c;
}
