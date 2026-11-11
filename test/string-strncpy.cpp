#include <cstdlib>
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(string, strncpy)
{
    EXPECT_EQ(ez_strncpy(nullptr, nullptr, 0), nullptr) << "NULL arg test fail\n";

    for(const std::string &str : test_lib::test_string)
    {
        if(str.size() < 2)
        {
            continue;
        }
        std::string ez_test;
        std::string std_test;
        {
            // For ez_test
            char *tmp1 = ez_strncpy(nullptr, str.c_str(), str.size() - 1);
            if(tmp1 == nullptr)
            {
                FAIL() << "Memory alloc fail\n";
            }

            // For std_test
            char *tmp2 = static_cast<char*>(std::malloc(str.size()));
            if(tmp2 == nullptr)
            {
                std::free(tmp1);
                FAIL() << "Memory alloc fail\n";
            }
            tmp2 = std::strncpy(tmp2, str.c_str(), str.size() - 1);
            tmp2[str.size() - 1] = '\0';

            ez_test = tmp1;
            std_test = tmp2;

            std::free(tmp1);
            std::free(tmp2);
        }
        EXPECT_EQ(ez_test, std_test) \
            << "str: " << str << '\n' \
            << "n: " << str.size() - 1 << '\n';
    }
}
