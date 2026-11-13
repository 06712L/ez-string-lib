#include "ez-string.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

char *ez_strndup(const char *str, size_t n)
{
    if(str == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    const size_t str_len = ez_strlen(str);
    const size_t size = (str_len > n) ? n:str_len;
    char *tmp_str = malloc(size + 1); // str + '\0'
    if(tmp_str == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }

    if(n == 0)
    {
        tmp_str[0] = '\0';
        return tmp_str;
    }
    return ez_strncpy(tmp_str, str, n);
}
