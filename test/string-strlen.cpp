// SPDX-License-Identifier: MIT
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"
#include <cstdint>
#include <cstring>
#include <gtest/gtest.h>

TEST_F(ERRNO_TEST, strlen_str_null) {
	EXPECT_EQ(ez_strlen(nullptr), SIZE_MAX - 1);
	EXPECT_EQ(errno, EINVAL);
}

TEST(strlen, normal) {
	for (const std::string &str : test_lib::test_string) {
		const std::size_t ez_test(ez_strlen(str.c_str()));
		const std::size_t std_test(std::strlen(str.c_str()));
		EXPECT_EQ(ez_test, std_test);
	}
}
