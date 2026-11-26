// SPDX-License-Identifier: MIT
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST_F(ERRNO_TEST, memcmp_all_null) {
	EXPECT_EQ(ez_string::ez_memcmp(nullptr, nullptr, 27), ez_string::EZ_MEMCMP_NULL);
	EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, memcmp_mem1_null) {
	EXPECT_EQ(ez_string::ez_memcmp(nullptr, "We didn't start the kernel", 27),
			  ez_string::EZ_MEMCMP_NULL);
	EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, memcmp_mem2_null) {
	EXPECT_EQ(ez_string::ez_memcmp("We didn't start the kernel", nullptr, 27),
			  ez_string::EZ_MEMCMP_NULL);
	EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, memcmp_n_zero_all_null) {
	EXPECT_EQ(ez_string::ez_memcmp(nullptr, nullptr, 0), 0);
	EXPECT_EQ(errno, 0);
}

TEST(memcmp, n_zero) {
	EXPECT_EQ(ez_string::ez_memcmp("We didn't start the kernel",
						"We didn't start the kernel", 0),
			  0);
}

TEST(memcmp, int16_unequal) {
	for (int16_t i(INT16_MIN); i < INT16_MAX; i++) {
		int16_t j(i + 1);
		EXPECT_EQ(test_lib::sign(ez_string::ez_memcmp(&i, &j, sizeof(int16_t))),
				  test_lib::sign(std::memcmp(&i, &j, sizeof(int16_t))))
			<< "i dec: [" << i << "]\ni hex: [" << std::hex << i << "]\n"
			<< "j dec: [" << j << "]\nj hex: [" << std::hex << j << "]\n";
	}
}

TEST(memcmp, uint16_unequal) {
	for (uint16_t i(0); i < UINT16_MAX; i++) {
		uint16_t j(i + 1);
		EXPECT_EQ(test_lib::sign(ez_string::ez_memcmp(&i, &j, sizeof(uint16_t))),
				  test_lib::sign(std::memcmp(&i, &j, sizeof(uint16_t))))
			<< "i dec: [" << i << "]\ni hex: [" << std::hex << i << "]\n"
			<< "j dec: [" << j << "]\nj hex: [" << std::hex << j << "]\n";
	}
}

TEST(memcmp, uint16_array_unequal) {
	enum { n = 15 };
	const std::size_t size(sizeof(uint16_t) * n);
	std::vector<uint16_t> arr1(n);
	std::vector<uint16_t> arr2(n);
	for (uint16_t i(0); i < n; i++) {
		arr1[i] = i;
		arr2[i] = i;
	}
	arr2[n - 1]--;
	EXPECT_EQ(test_lib::sign(ez_string::ez_memcmp(arr1.data(), arr2.data(), size)),
			  test_lib::sign(std::memcmp(arr1.data(), arr2.data(), size)));
}

TEST(memcmp, str) {
	for (std::size_t i = 1; i < test_lib::test_string.size(); i++) {
		const std::string &str1(test_lib::test_string[i - 1]);
		const std::string &str2(test_lib::test_string[i]);
		const std::size_t n(test_lib::min(str1.size(), str2.size()));
		EXPECT_EQ(test_lib::sign(ez_string::ez_memcmp(str1.c_str(), str2.c_str(), n)),
				  test_lib::sign(std::memcmp(str1.c_str(), str2.c_str(), n)))
			<< "str1: [" << str1 << "]\n"
			<< "str2: [" << str2 << "]\n"
			<< "n: [" << n << "]\n";
	}
}
