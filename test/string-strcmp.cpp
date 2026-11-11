#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(string, strcmp)
{
    EXPECT_EQ(ez_strcmp(NULL, NULL), 1) << "NULL arg test fail\n";

    for(const std::string &str1 : test_lib::test_string)
    {
        for(const std::string &str2 : test_lib::test_string)
        {
            const int ez_test(test_lib::sign(ez_strcmp(str1.c_str(), str2.c_str())));
            const int std_test(test_lib::sign(std::strcmp(str1.c_str(), str2.c_str())));
            EXPECT_EQ(ez_test, std_test) \
                << "str1: " << str1 << '\n' \
                << "str2: " << str2 << '\n' \
                << "ez_strcmp return value: " << ez_test << '\n' \
                << "std strcmp return value: " << std_test << '\n';
        }
    }
}
