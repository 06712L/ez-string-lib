#include <cstdlib>
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(string, strcpy)
{
    EXPECT_EQ(ez_strcpy(nullptr, nullptr), nullptr) << "NULL arg test fail\n";

    for(const std::string &str : test_lib::test_string)
    {
        std::string ez_test;
        std::string std_test;
        {
            // For ez_test
            char *tmp1 = ez_strcpy(nullptr, str.c_str());
            if(tmp1 == nullptr)
            {
                FAIL() << "Memory alloc fail\n";
            }

            // For std_test
            char *tmp2 = static_cast<char*>(std::malloc(str.size() + 1));
            if(tmp2 == nullptr)
            {
                std::free(tmp1);
                FAIL() << "Memory alloc fail\n";
            }
            tmp2 = std::strcpy(tmp2, str.c_str());

            ez_test = tmp1;
            std_test = tmp2;

            std::free(tmp1);
            std::free(tmp2);
        }
        EXPECT_EQ(ez_test, std_test) \
            << "ez_strcpy return string: " << ez_test << '\n' \
            << "std strcpy return string: " << std_test << '\n';
    }
}
