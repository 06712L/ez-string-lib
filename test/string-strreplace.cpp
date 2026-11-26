// SPDX-License-Identifier: MIT
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"
#include <array>
#include <cerrno>
#include <gtest/gtest.h>
#include <memory>
#include <string>

TEST_F(ERRNO_TEST, strreplace_all_null_str) {
	EXPECT_EQ(ez_string::ez_strreplace(nullptr, nullptr, nullptr,
									   ez_string::EZ_STRREPLACE_ALL, false,
									   false),
			  nullptr);
	EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, strreplace_invalid_mode) {
	std::string test_str = "ah";
	EXPECT_EQ(ez_string::ez_strreplace(
				  test_str.data(), "a", "h",
				  static_cast<ez_string::ez_strreplace_replace_mode>(
					  ez_string::EZ_STRREPLACE_ALL + 1),
				  false, false),
			  nullptr);
	EXPECT_EQ(errno, EINVAL);
}

struct test_str {
	const std::string target_str;
	const std::string replace_str;
	const enum ez_string::ez_strreplace_replace_mode replace_mode;
	const std::string answer;
};

static const auto test_strreplace = std::to_array<struct test_str>({
	{"ab", "b", ez_string::EZ_STRREPLACE_ALL, "ab"},
	{"c", "linux", ez_string::EZ_STRREPLACE_ALL, "abablinux"},
	{"a", "bc", ez_string::EZ_STRREPLACE_FIRST, "bcaaaaaaaaaaabc"},
	{"哎", "喲", ez_string::EZ_STRREPLACE_LAST, "哎哎哎哎哎哎哎喲喲"},
	{" ", "-", ez_string::EZ_STRREPLACE_ALL, "Goo-Goo-Bird-Tool"},
	{" ", "", ez_string::EZ_STRREPLACE_FIRST, "meowmeow"},
	{"m", "ow", ez_string::EZ_STRREPLACE_FIRST, "oweow meow meow"},
});

TEST(strreplace, disable_in_place_enable_auto_realloc) {
	unsigned int index(0);
	for (const struct test_str &test : test_strreplace) {
		errno = 0;
		std::string tmp_str(test_lib::test_string[index]);
		std::unique_ptr<char[], decltype(&free)> ez_test(
			ez_string::ez_strreplace(tmp_str.data(), test.target_str.c_str(),
									 test.replace_str.c_str(),
									 test.replace_mode, false, true),
			&free);
		if (ez_test == nullptr && errno == ENOMEM) {
			FAIL() << "Memory alloc fail\n";
		}

		EXPECT_STREQ(ez_test.get(), test.answer.c_str())
			<< "str: [" << test_lib::test_string[index] << "]\n"
			<< "target str: [" << test.target_str << "]\n"
			<< "replace str: [" << test.replace_str << "]\n";
		index++;
	}
}

TEST(strreplace, enable_in_place_disable_auto_realloc) {
	unsigned int index(0);
	for (const struct test_str &test : test_strreplace) {
		errno = 0;
		std::string ez_test;
		{
			std::string tmp_str(test_lib::test_string[index]);
			if (ez_string::ez_strreplace(
					tmp_str.data(), test.target_str.c_str(),
					test.replace_str.c_str(), test.replace_mode, true,
					false) == nullptr &&
				errno == ENOMEM) {
				FAIL() << "Memory alloc fail\n";
			}
			ez_test = tmp_str.c_str();
		}

		EXPECT_EQ(ez_test, test.answer)
			<< "str: [" << test_lib::test_string[index] << "]\n"
			<< "target str: [" << test.target_str << "]\n"
			<< "replace str: [" << test.replace_str << "]\n";
		index++;
	}
}
