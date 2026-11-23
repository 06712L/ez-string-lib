// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <stdbool.h>

bool ez_isupper(const char c) {
	const unsigned char uc = (const unsigned char)c;
    return uc >= 'A' && uc <= 'Z';
}