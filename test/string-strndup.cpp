#include <cstdlib>
#include <gtest/gtest.h>
#include <string.h>
#include <memory>
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"

TEST_F(ERRNO_TEST, strndup_null_str)
{
    EXPECT_EQ(ez_strndup(nullptr, 1), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strndup, zero_n)
{
    std::unique_ptr<char[], decltype(&free)> test(ez_strndup("test", 0), &free);
    EXPECT_STREQ(test.get(), "");
}

TEST(strndup, copy_first_to_len_m1)
{
    for(const std::string &str : test_lib::test_string)
    {
        if(str.size() < 2)
        {
            continue;
        }
        const std::size_t n = str.size() - 1;
        std::unique_ptr<char[], decltype(&free)> ez_test(ez_strndup(str.c_str(), n), &free);
        std::unique_ptr<char[], decltype(&free)> std_test(strndup(str.c_str(), n), &free);
        if(ez_test == nullptr || std_test == nullptr)
        {
            FAIL() << "Memory alloc fail\n";
        }

        EXPECT_STREQ(ez_test.get(), std_test.get());
    }
}

TEST(strndup, copy_first_to_second)
{
    enum
    {
        N = 2,
    };

    for(const std::string &str : test_lib::test_string)
    {
        if(str.size() < 2)
        {
            continue;
        }
        std::unique_ptr<char[], decltype(&free)> ez_test(ez_strndup(str.c_str(), N), &free);
        std::unique_ptr<char[], decltype(&free)> std_test(strndup(str.c_str(), N), &free);
        if(ez_test == nullptr || std_test == nullptr)
        {
            FAIL() << "Memory alloc fail\n";
        }

        EXPECT_STREQ(ez_test.get(), std_test.get());
    }
}
