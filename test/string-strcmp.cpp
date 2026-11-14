#include <cerrno>
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"
#include "errno-test.hpp"

TEST_F(ERRNO_TEST, strcmp_all_null)
{
    EXPECT_EQ(ez_strcmp(nullptr, nullptr), EZ_STRCMP_NULL);
    EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, strcmp_null_str1)
{
    EXPECT_EQ(ez_strcmp(nullptr, "test"), EZ_STRCMP_NULL);
    EXPECT_EQ(errno, EINVAL);
}

TEST_F(ERRNO_TEST, strcmp_null_str2)
{
    EXPECT_EQ(ez_strcmp("test", nullptr), EZ_STRCMP_NULL);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strcmp, normal)
{
    for(const std::string &str1 : test_lib::test_string)
    {
        for(const std::string &str2 : test_lib::test_string)
        {
            const int ez_test(test_lib::sign(ez_strcmp(str1.c_str(), str2.c_str())));
            const int std_test(test_lib::sign(std::strcmp(str1.c_str(), str2.c_str())));
            EXPECT_EQ(ez_test, std_test)
                << "str1: [" << str1 << "]\n"
                << "str2: [" << str2 << "]\n";
        }
    }
}
