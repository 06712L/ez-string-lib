// SPDX-License-Identifier: MIT
#include "ez-string.h"

char ez_toupper(const char c) {
	const unsigned char uc = (const unsigned char)c;
	if (uc >= 'a' && uc <= 'z') {
		return (char)(uc - (unsigned char)('a' - 'A'));
	}
	return c;
}
