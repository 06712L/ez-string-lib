#include <gtest/gtest.h>
#include <cstring>
#include <memory>
#include <stdexcept>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(strcpy, null_target)
{
    EXPECT_EQ(ez_strcpy(nullptr, "test"), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strcpy, null_str)
{
    std::unique_ptr<char[]> target = std::make_unique<char[]>(4);
    EXPECT_EQ(ez_strcpy(target.get(), nullptr), nullptr);
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
