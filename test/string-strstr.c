#include "ez-string.h"
#include "test-lib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct test_results
{
    const char *string_head;
    const char *test1;
    const char *test2;
    uint8_t i;
    bool error;
};

struct test_results test_strstr(void)
{
    struct test_results results = {NULL, NULL, NULL, 0, false};
    const char *test_strstr[] =
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
        "2<3=?",
        NULL
    };
    for(results.i = 0; test_strstr[results.i] != NULL && test_string[results.i] != NULL; results.i++)
    {
        results.string_head = test_string[results.i];
        results.test1 = ez_strstr(test_string[results.i], test_strstr[results.i]);
        results.test2 = strstr(test_string[results.i], test_strstr[results.i]);
        if(results.test1 != results.test2)
        {
            results.error = true;
            return results;
        }
        results.string_head = NULL;
        results.test1 = NULL;
        results.test2 = NULL;
    }
    results.string_head = test_string[0];
    if((results.test1 = ez_strstr(test_string[0], NULL)) != results.string_head)
    {
        results.error = true;
        return results;
    }
    return (struct test_results){NULL, NULL, NULL, 0, false};
}

int main(void)
{
    struct test_results results = test_strstr();
    if(results.error)
    {
        puts("string-strstr:");
        printf("fail code: %d\nstring head: %p\ntest1 results: %p\ntest2 results: %p\n", results.i, results.string_head, results.test1, results.test2);
    }
    return results.error;
}
