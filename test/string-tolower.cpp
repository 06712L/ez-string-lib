// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <cctype>
#include <gtest/gtest.h>

TEST(tolower, normal) {
	for (unsigned char c = '\0'; c <= '\x7f';
		 c++) // NUL(\0) is first ASCII, DEL(\x7f) is last ASCII
	{
		EXPECT_EQ(ez_tolower(static_cast<char>(c)), std::tolower(c))
			<< "test character: [" << c << "]\n";
	}
}
