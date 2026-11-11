#ifndef TEST_LIB_H
#define TEST_LIB_H

#include <string>
#include <array>

class test_lib
{
    public:
    enum class test_str_arr
    {
        SIZE = 24,
    };
    static const std::array<std::string, 24> test_string;

    static signed int sign(signed int num);
};

#endif
