#include <gtest/gtest.h>
#include <cstring>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(string, strlen)
{
    EXPECT_EQ(ez_strlen(nullptr), 0) << "NULL arg test fail\n";

    for(const std::string &str : test_lib::test_string)
    {
        const std::size_t ez_test(ez_strlen(str.c_str()));
        const std::size_t std_test(std::strlen(str.c_str()));
        EXPECT_EQ(ez_test, std_test) \
            << "ez_strlen return value: " << ez_test << '\n' \
            << "std strlen return value: " << std_test << '\n';
    }
}
