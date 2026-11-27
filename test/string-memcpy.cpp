// SPDX-License-Identifier: MIT
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <string>
#include <exception>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

TEST_F(ERRNO_TEST, memcpy_target_null) {
	EXPECT_EQ(ez_string::ez_memcpy(nullptr, "test",  5), nullptr);
	EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, memcpy_src_null) {
	char target[2]{0};
	EXPECT_EQ(ez_string::ez_memcpy(target, nullptr, 2), nullptr);
	EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, memcpy_n_zero) {
	char target[2]{0};
	EXPECT_EQ(ez_string::ez_memcpy(target, "A", 0), target);
	EXPECT_EQ(errno, 0);
}

TEST(memcpy, copy_string) {
	for (const std::string &str : test_lib::test_string) {
		const std::size_t str_size = str.size() + 1;
		std::unique_ptr<char[]> ez_test;
		std::unique_ptr<char[]> std_test;
		try {
			ez_test = std::make_unique<char[]>(str_size);
			std_test = std::make_unique<char[]>(str_size);
		} catch (const std::exception &) {
			FAIL() << "Memory alloc fail\n";
		}

		EXPECT_EQ(std::memcmp(ez_string::ez_memcpy(ez_test.get(), str.c_str(), str_size), std::memcpy(std_test.get(), str.c_str(), str_size), str_size), 0)
		<< "str: [" << str << "]\n";
	}
}

TEST(memcpy, copy_uint16_array) {
	for (uint16_t i = 0; i <= 0x3ff; i++) { // use 0x3ff to reduce the test execution time
		const std::size_t arr_size = test_lib::min(test_lib::max(i, static_cast<uint16_t>(1)), static_cast<uint16_t>(255));
		const std::size_t arr_size_u16 = arr_size * sizeof(uint16_t);
		std::vector<uint16_t> test_arr(arr_size, i);
		std::unique_ptr<uint16_t[]> ez_test;
		std::unique_ptr<uint16_t[]> std_test;
		try {
			ez_test = std::make_unique<uint16_t[]>(arr_size);
			std_test = std::make_unique<uint16_t[]>(arr_size);
		} catch (const std::exception &) {
			FAIL() << "Memory alloc fail\n";
		}

		EXPECT_EQ(std::memcmp(ez_string::ez_memcpy(ez_test.get(), test_arr.data(), arr_size_u16), std::memcpy(std_test.get(), test_arr.data(), arr_size_u16), arr_size_u16), 0)
		<< "i: " << i << '\n';
	}
}