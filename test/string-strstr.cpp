#include <array>
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(strstr, all_null)
{
    EXPECT_EQ(ez_strstr(nullptr, nullptr), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strstr, null_haystack)
{
    EXPECT_EQ(ez_strstr(nullptr, "test"), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(ststr, null_needle)
{
    const std::string test = "test";
    EXPECT_EQ(ez_strstr(test.c_str(), nullptr), nullptr);
    EXPECT_EQ(errno, EINVAL);
}

TEST(strstr, empty_string_needle)
{
    const std::string test = "test";
    EXPECT_EQ(ez_strstr(test.c_str(), ""), test.c_str());
}

TEST(strstr, normal)
{
    const auto test_strstr = std::to_array<std::string>(
    {
        "ab",
        "abc",
        "abc",
        "哎喲",
        "Tool",
        " meow",
        "喵",
        "OH",
        "-",
        ";",
        "OH MY DISK!!!!!!!!!!!!",
        "\0",
        "！喲",
        "倒灌",
        ".",
        "\n",
        "%",
        "Give up!",
        "2<3=?"
    });

    for(const std::string &haystack : test_lib::test_string)
    {
        for(const std::string &needle : test_strstr)
        {
            const char *ez_test(ez_strstr(haystack.c_str(), needle.c_str()));
            const char *std_test(std::strstr(haystack.c_str(), needle.c_str()));
            EXPECT_EQ(ez_test, std_test)
                << "haystack: " << haystack << '\n'
                << "needle: " << needle << '\n';
        }
    }
}
