#include <array>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(string, strreplace)
{
    EXPECT_EQ(ez_strreplace(nullptr, nullptr, nullptr, 0, false, false), nullptr) \
        << "NULL arg test fail\n";

    struct test_str
    {
        const std::string target_str;
        const std::string replace_str;
        const int replace_mode;
        const std::string answer;
    };

    enum
    {
        TS_SIZE = 7,
    };
    const auto test_strreplace = std::to_array<struct test_str>(
    {
        {"ab", "b", EZ_STRREPLACE_ALL, "ab"},
        {"c", "linux", EZ_STRREPLACE_ALL, "abablinux"},
        {"a", "bc", EZ_STRREPLACE_FIRST,  "bcaaaaaaaaaaabc"},
        {"哎", "喲", EZ_STRREPLACE_LAST,   "哎哎哎哎哎哎哎喲喲"},
        {" ", "-", EZ_STRREPLACE_ALL,   "Goo-Goo-Bird-Tool"},
        {" ", "", EZ_STRREPLACE_FIRST,   "meowmeow"},
        {"m", "ow", EZ_STRREPLACE_FIRST ,   "oweow meow meow"},
    });

    {
        unsigned int index(0);
        for(const struct test_str &test : test_strreplace)
        {
            std::string ez_test;
            {
                std::string tmp_str(test_lib::test_string[index]);
                char *tmp(ez_strreplace(tmp_str.data(), test.target_str.c_str(), test.replace_str.c_str(), \
                    test.replace_mode, false, true));
                if(tmp == nullptr)
                {
                    FAIL() << "Memory alloc fail\n";
                }
                ez_test = tmp;
                std::free(tmp);
            }

            EXPECT_EQ(ez_test, test.answer) \
                << "str: " << test_lib::test_string[index] << '\n' \
                << "target str: " << test.target_str << '\n' \
                << "replace str: " << test.replace_str << '\n';
            index++;
        }
    }
}
