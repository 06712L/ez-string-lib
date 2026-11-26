#include "ez-string.h"
#include "errno-test.hpp"
#include "test-lib.hpp"
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <exception>
#include <gtest/gtest.h>
#include <vector>

TEST_F(ERRNO_TEST, memset_s_NULL) {
	EXPECT_EQ(ez_string::ez_memset(nullptr, 1, 10), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, memset_n_zero)
{
    std::vector<char> s;
    try {
        s.reserve(1);
	} catch (const std::exception &error) {
        (void)error;
		FAIL() << "Memory alloc fail\n";
	}
	EXPECT_EQ(ez_string::ez_memset(s.data(), 1, 0), s.data());
    EXPECT_EQ(errno, 0);
}

TEST(memset, normal)
{
    for(unsigned char uc = 0; uc < UINT8_MAX; uc++)
    {
        std::vector<char> ez_test;
        std::vector<char> std_test;
        try {
            ez_test.reserve(test_lib::max(uc, static_cast<unsigned char>(1)));
            std_test.reserve(test_lib::max(uc, static_cast<unsigned char>(1)));
        } catch (const std::exception &error) {
            FAIL() << "Memory alloc fail\n";
        }
        EXPECT_EQ(std::memcmp(ez_string::ez_memset(ez_test.data(), static_cast<char>(uc), uc), std::memset(std_test.data(), uc, uc), uc), 0)
        << "uc: " << uc << "\n";
    }
}