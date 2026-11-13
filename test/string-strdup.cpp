#include <cstdlib>
#include <gtest/gtest.h>
#include <string.h>
#include <memory>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(strdup, null_str)
{
    EXPECT_EQ(ez_strdup(nullptr), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strdup, copy)
{
    for(const std::string &str : test_lib::test_string)
    {
        std::unique_ptr<char[], decltype(&free)> ez_test(ez_strdup(str.c_str()), &free);
        std::unique_ptr<char[], decltype(&free)> std_test(strdup(str.c_str()), &free);
        if(ez_test == nullptr || std_test == nullptr)
        {
            FAIL() << "Memory alloc fail\n";
        }
        EXPECT_STREQ(ez_test.get(), std_test.get());
    }
}
