#include <cstdint>
#include <gtest/gtest.h>
#include <cstring>
#include <ios>
#include <string>
#include <string_view>
#include "ez-string.h"
#include "test-lib.hpp"

TEST(string, strchr_strrchr)
{
    EXPECT_EQ(ez_strchr(nullptr, '\0'), nullptr) << "ez_strchr: NULL arg test fail\n";
    EXPECT_EQ(ez_strrchr(nullptr, '\0'), nullptr) << "ez_strrchr: NULL arg test fail\n";

    const auto test_strchr_strchr =  std::to_array<char>(
    {
        'a',
        'c',
        'a',
        '\0',
        'T',
        'o',
        ' ',
        '!',
        '-',
        '*',
        '0',
        'q',
        'm',
    });
    for(const std::string &s : test_lib::test_string)
    {
        for(const char c : test_strchr_strchr)
        {
            for(uint8_t i(0); i < 2; i++)
            {
                const std::string_view title((i) ? "strchr":"strrchr");
                const char *ez_test((i) ? ez_strchr(s.c_str(), c):ez_strrchr(s.c_str(), c));
                const char *std_test((i) ? std::strchr(s.c_str(), c):std::strrchr(s.c_str(), c));
                EXPECT_EQ(ez_test, std_test) \
                    << "s: " << s << '\n' \
                    << "c: " << c << '\n' \
                    << "ez_" << title << " return value: " << std::hex << ez_test << '\n' \
                    << "std "<< title << " return value: " << std::hex << std_test << '\n';
            }
        }
    }
}
