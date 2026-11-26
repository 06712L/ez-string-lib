// SPDX-License-Identifier: MIT
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <memory>
#include <string.h>

TEST_F(ERRNO_TEST, strdup_str_null) {
	EXPECT_EQ(ez_string::ez_strdup(nullptr), nullptr);
	EXPECT_EQ(errno, EINVAL);
}

TEST(strdup, copy) {
	for (const std::string &str : test_lib::test_string) {
		std::unique_ptr<char[], decltype(&free)> ez_test(ez_string::ez_strdup(str.c_str()),
														 &free);
		std::unique_ptr<char[], decltype(&free)> std_test(strdup(str.c_str()),
														  &free);
		if (ez_test == nullptr || std_test == nullptr) {
			FAIL() << "Memory alloc fail\n";
		}
		EXPECT_STREQ(ez_test.get(), std_test.get());
	}
}
