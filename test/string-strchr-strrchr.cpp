// SPDX-License-Identifier: MIT
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"
#include <cerrno>
#include <cstring>
#include <gtest/gtest.h>

TEST_F(ERRNO_TEST, strchr_s_null) {
	EXPECT_EQ(ez_string::ez_strchr(nullptr, 'a'), nullptr);
	EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, strrchr_s_null) {
	EXPECT_EQ(ez_string::ez_strrchr(nullptr, 'a'), nullptr);
	EXPECT_EQ(errno, EINVAL);
}

static const auto test_strchr_strrchr = std::to_array<char>({
	'a',
	'c',
	'a',
	'\0',
	'T',
	'o',
	' ',
	'!',
	'-',
	'*',
	'0',
	'q',
	'm',
});

TEST(strchr, find) {
	for (const std::string &s : test_lib::test_string) {
		for (const char c : test_strchr_strrchr) {
			const char *ez_test(ez_string::ez_strchr(s.c_str(), c));
			const char *std_test(std::strchr(s.c_str(), c));
			EXPECT_EQ(ez_test, std_test) << "s: [" << s << "]\n"
										 << "c: [" << c << "]\n";
		}
	}
}

TEST(strrchr, find) {
	for (const std::string &s : test_lib::test_string) {
		for (const char c : test_strchr_strrchr) {
			const char *ez_test(ez_string::ez_strrchr(s.c_str(), c));
			const char *std_test(std::strrchr(s.c_str(), c));
			EXPECT_EQ(ez_test, std_test) << "s: [" << s << "]\n"
										 << "c: [" << c << "]\n";
		}
	}
}
