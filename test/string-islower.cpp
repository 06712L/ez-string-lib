// SPDX-License-Identifier: MIT
#include "ez-string.h"
#include <cctype>
#include <gtest/gtest.h>

TEST(islower, normal) {
	for (unsigned char c = '\0'; c <= '\x7f';
		 c++) // NUL(\0) is first ASCII, DEL(\x7f) is last ASCII
	{
		EXPECT_EQ(ez_string::ez_islower(static_cast<char>(c)), std::islower(c) != 0)
			<< "test character: [" << c << "]\n";
	}
}
