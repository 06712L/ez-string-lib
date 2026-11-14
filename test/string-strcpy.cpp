#include <cerrno>
#include <gtest/gtest.h>
#include <cstring>
#include <memory>
#include <stdexcept>
#include "ez-string.h"
#include "test-lib.hpp"
#include "errno-test.hpp"

TEST_F(ERRNO_TEST, strcpy_null_target)
{
    EXPECT_EQ(ez_strcpy(nullptr, "test"), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, strcpy_null_str)
{
    char target[2]{0};
    EXPECT_EQ(ez_strcpy(target, nullptr), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strcpy, copy)
{
    for(const std::string &str : test_lib::test_string)
    {
        const std::size_t str_size = str.size() + 1;
        std::unique_ptr<char[]> ez_test;
        std::unique_ptr<char[]> std_test;
        try
        {
            ez_test = std::make_unique<char[]>(str_size);
            std_test = std::make_unique<char[]>(str_size);
        }
        catch (const std::runtime_error &e)
        {
            FAIL() << "Memory alloc fail\n";
        }

        EXPECT_STREQ(ez_strcpy(ez_test.get(), str.c_str()), std::strcpy(std_test.get(), str.c_str()));
    }
}
