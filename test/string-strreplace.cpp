#include <array>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(streplace, all_null_str)
{
    EXPECT_EQ(ez_strreplace(nullptr, nullptr, nullptr, 0, false, false), nullptr);
}

TEST(strreplace, nonexistent_mode)
{
    std::string test_str = "ah";
    EXPECT_EQ(ez_strreplace(test_str.data(), "a", "h", 67, false, false), nullptr);
}

struct test_str
{
    const std::string target_str;
    const std::string replace_str;
    const int replace_mode;
    const std::string answer;
};

static const auto test_strreplace = std::to_array<struct test_str>(
{
    {"ab", "b", EZ_STRREPLACE_ALL, "ab"},
    {"c", "linux", EZ_STRREPLACE_ALL, "abablinux"},
    {"a", "bc", EZ_STRREPLACE_FIRST,  "bcaaaaaaaaaaabc"},
    {"哎", "喲", EZ_STRREPLACE_LAST,   "哎哎哎哎哎哎哎喲喲"},
    {" ", "-", EZ_STRREPLACE_ALL,   "Goo-Goo-Bird-Tool"},
    {" ", "", EZ_STRREPLACE_FIRST,   "meowmeow"},
    {"m", "ow", EZ_STRREPLACE_FIRST ,   "oweow meow meow"},
});

TEST(strreplace, disable_in_plaec_enable_auto_realloc)
{
    unsigned int index(0);
    for(const struct test_str &test : test_strreplace)
    {
        std::string tmp_str(test_lib::test_string[index]);
        std::unique_ptr<char[], decltype(&free)> ez_test(ez_strreplace(tmp_str.data(), test.target_str.c_str(), test.replace_str.c_str(), \
            test.replace_mode, false, true), &free);
        if(ez_test == nullptr)
        {
            FAIL() << "Memory alloc fail\n";
        }

        EXPECT_STREQ(ez_test.get(), test.answer.c_str())
            << "str: [" << test_lib::test_string[index] << "]\n"
            << "target str: [" << test.target_str << "]\n"
            << "replace str: [" << test.replace_str << "]\n";
        index++;
    }
}

TEST(strreplace, enable_in_plaec_disable_auto_realloc)
{
    unsigned int index(0);
    for(const struct test_str &test : test_strreplace)
    {
        std::string ez_test;
        {
            std::string tmp_str(test_lib::test_string[index]);
            if(ez_strreplace(tmp_str.data(), test.target_str.c_str(), test.replace_str.c_str(), \
                test.replace_mode, true, false) == nullptr)
            {
                FAIL() << "Memory alloc fail\n";
            }
            ez_test = tmp_str.c_str();
        }

        EXPECT_EQ(ez_test, test.answer)
            << "str: [" << test_lib::test_string[index] << "]\n"
            << "target str: [" << test.target_str << "]\n"
            << "replace str: [" << test.replace_str << "]\n";
        index++;
    }
}
