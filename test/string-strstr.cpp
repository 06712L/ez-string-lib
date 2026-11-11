#include <array>
#include <cstdint>
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(string, strstr)
{
    EXPECT_EQ(ez_strstr(nullptr, nullptr), nullptr) << "ez_strchr: NULL haystack arg test fail\n";

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
    EXPECT_EQ(ez_strstr(test_strstr[0].c_str(), nullptr), test_strstr[0].c_str()) << "ez_strchr: NULL needle arg test fail\n";
    EXPECT_EQ(ez_strstr(test_strstr[0].c_str(), ""), test_strstr[0].c_str()) << "ez_strchr: empty string needle arg test fail\n";

    for(const std::string &haystack : test_lib::test_string)
    {
        for(const std::string &needle : test_strstr)
        {
            for(uint8_t i(0); i < 2; i++)
            {
                const char *ez_test(ez_strstr(haystack.c_str(), needle.c_str()));
                const char *std_test(std::strstr(haystack.c_str(), needle.c_str()));
                EXPECT_EQ(ez_test, std_test) \
                    << "haystack: " << haystack << '\n' \
                    << "needle: " << needle << '\n';
            }
        }
    }
}
