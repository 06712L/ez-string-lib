// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <stdbool.h>

bool ez_islower(const char c) {
	const unsigned char uc = (const unsigned char)c;
	return uc >= 'a' && uc <= 'z';
}
