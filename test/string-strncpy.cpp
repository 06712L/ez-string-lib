#include <gtest/gtest.h>
#include <cstring>
#include <memory>
#include "errno-test.hpp"
#include "ez-string.h"
#include "test-lib.hpp"

TEST_F(ERRNO_TEST, strncpy_null_target)
{
    EXPECT_EQ(ez_strncpy(nullptr, "test", 4), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, strncpy_null_str)
{
    char target[3] = {0};
    EXPECT_EQ(ez_strncpy(target, nullptr, 2), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strncpy, zero_n)
{
    char target[3] = {0};
    EXPECT_EQ(ez_strncpy(target, "zn", 0), target);
}

TEST(strncpy, copy_first_to_len_m1)
{
    for(const std::string &str : test_lib::test_string)
    {
        if(str.size() < 2)
        {
            continue;
        }
        const std::size_t n = str.size() - 1;
        std::unique_ptr<char[]> ez_test;
        std::unique_ptr<char[]> std_test;
        try
        {
            ez_test = std::make_unique<char[]>(str.size());
            std_test = std::make_unique<char[]>(str.size());
        }
        catch (const std::runtime_error &e)
        {
            FAIL() << "Memory alloc fail\n";
        }

        EXPECT_STREQ(ez_strncpy(ez_test.get(), str.c_str(), n), std::strncpy(std_test.get(), str.c_str(), n));
    }
}

TEST(strncpy, copy_first_to_second)
{
    enum
    {
        N = 2,
        SIZE = 3,
    };

    for(const std::string &str : test_lib::test_string)
    {
        if(str.size() < 2)
        {
            continue;
        }
        std::unique_ptr<char[]> ez_test;
        std::unique_ptr<char[]> std_test;
        try
        {
            ez_test = std::make_unique<char[]>(SIZE);
            std_test = std::make_unique<char[]>(SIZE);
        }
        catch (const std::runtime_error &e)
        {
            FAIL() << "Memory alloc fail\n";
        }

        EXPECT_STREQ(ez_strncpy(ez_test.get(), str.c_str(), N), std::strncpy(std_test.get(), str.c_str(), N));
    }
}
