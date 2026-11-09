#include "ez-string.h"
#include "test-lib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct test_str
{
    const char *target_str;
    const char *replace_str;
    const int replace_mode;
    bool in_place;
    const char *answer;
};

struct test_results
{
    uint8_t i;
    const char *str;
    char *test_str;
    const struct test_str *test;
    bool error;
};

#define TEST_STR_END (const struct test_str) {NULL, NULL, 10, false, NULL}
#define TEST_RESULTS_MEM_ERROR (struct test_results){1, NULL, NULL, NULL, true}
#define TEST_RESULTS_PASS (struct test_results){0, NULL, NULL, NULL, false}

static const struct test_str test_strrplace_str[] =
{
    {"ab", "b", EZ_STRREPLACE_ALL, false,  "ab"},
    {"d", "oh oh oh OH OH! OH NO!", EZ_STRREPLACE_ALL, false,  NULL},
    {"a", "bc", EZ_STRREPLACE_FIRST, false, "bcaaaaaaaaaaabc"},
    {"哎", "喲", EZ_STRREPLACE_LAST, true,  "哎哎哎哎哎哎哎喲喲"},
    {" ", "-", EZ_STRREPLACE_ALL, false,  "Goo-Goo-Bird-Tool"},
    {" ", "\0", EZ_STRREPLACE_FIRST, false,  "meowmeow"},
    {"m", "ow", EZ_STRREPLACE_FIRST , true,  "oweow meow meow"},
    TEST_STR_END
};
static struct test_results test_strreplace()
{
    struct test_results results = {0, NULL, false};
    for(results.i = 0; test_strrplace_str[results.i].replace_mode != 10; results.i++)
    {
        // Set
        results.test = &test_strrplace_str[results.i];
        results.str = test_string[results.i];
        if(test_strrplace_str[results.i].in_place) results.test_str = ez_strcpy(NULL, results.str);
        else results.test_str = NULL;
        if(results.test == NULL) return TEST_RESULTS_MEM_ERROR;

        // Start testing
        {
            char *tmp_str = ez_strreplace((char*)((test_strrplace_str[results.i].in_place) ? results.test_str:results.str), results.test->target_str,\
            results.test->replace_str, results.test->replace_mode, results.test->in_place, true);
            if((results.test->answer != NULL) ? (tmp_str == NULL):(tmp_str != NULL) || (results.test->answer != NULL) ? ez_strcmp(tmp_str, results.test->answer):0)
            {
                if(results.test->answer == NULL || tmp_str != NULL) results.test_str = tmp_str;
                results.error = true;
                return results;
            }
            results.test_str = tmp_str;
        }
        free(results.test_str);
        results.test_str = NULL;
        results.test = NULL;
        results.str = NULL;
    }
    return TEST_RESULTS_PASS;
}

int main(void)
{
    const struct test_results results = test_strreplace();
    if(results.error)
    {
        puts("string-strreplace:");
        if(results.i == 1 && results.str == NULL && results.test == NULL) puts("MEM ERROR");
        else
            printf("fail code: %d\nstr: %s\ntest str: %s\ntarget str: %s\nreplace str: %s\nanswer: %s\n",\
            results.i, results.str, results.test_str, results.test->target_str, results.test->replace_str, results.test->answer);
    }
    if(results.error) free(results.test_str);
    return results.error;
}
