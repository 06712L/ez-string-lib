#include "ez-string.h"
#include "test-lib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct test_results
{
    char *string_head;
    char *test1;
    char *test2;
    uint8_t i;
    bool error;
};

struct test_results test_strrchr(void)
{
    struct test_results results = {NULL, NULL, NULL, 0, false};
    char* test_strrchr[] =
    {
        "a",
        "c",
        "a",
        "\0",
        "T",
        "o",
        " ",
        "!",
        "-",
        "*",
        NULL
    };
    for(results.i = 0; test_strrchr[results.i] != NULL && test_string[results.i]; results.i++)
    {
        results.string_head = (char*)test_string[results.i];
        results.test1 = ez_strrchr(test_string[results.i], test_strrchr[results.i][0]);
        results.test2 = strrchr(test_string[results.i], test_strrchr[results.i][0]);
        if(results.test1 != results.test2)
        {
            results.error = true;
            return results;
        }
        results.test1 = NULL;
        results.test2 = NULL;
    }
    if((results.test1 = ez_strrchr(NULL, '\0')) != NULL)
    {
        results.error = true;
        return results;
    }
    return (struct test_results){NULL, NULL, NULL, 0, false};
}

int main(void)
{
    struct test_results results = test_strrchr();
    if(results.error)
    {
        puts("string-strrchr:");
        printf("fail code: %d\nstring head: %p\ntest1 results: %p\ntest2 results: %p\n", results.i, results.string_head, results.test1, results.test2);
    }
    return results.error;
}
