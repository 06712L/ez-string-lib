#include "test-lib.hpp"
#include <array>
#include <string>


const std::array<std::string, 24> test_lib::test_string =
{
    "aab",
    "ababc",
    "aaaaaaaaaaaabc",
    "哎哎哎哎哎哎哎哎喲",
    "Goo Goo Bird Tool",
    "meow meow",
    "meow meow meow",
    "OH MY LINUX!",
    "idiot-tic-tac-toe",
    "int main(int argc, char *argv[]);",
    "+-*/=",
    "snake_case",
    "哎喲！",
    "海水倒灌了！",
    "0123456789.",
    "test\rtest\n",
    "67%",
    "Don't give up!",
    "2^3=?",
    "test@test.test",
    "~/Download/test.mp4",
    "long long long long long long long long long long long long long long long long long long long long long long",
    "",
    "OH NO NO NO"
};

signed int test_lib::sign(signed int num)
{
    return (num > 0) - (num < 0);
}
