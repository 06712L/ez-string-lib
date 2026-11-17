// SPDX-License-Identifier: MIT
#include <stdint.h>
#include <errno.h>
#include <stddef.h>
#include "ez-string.h"

size_t ez_strlen(const char *str)
{
    if(str == NULL)
    {
        errno = EINVAL;
        return SIZE_MAX - 1;
    }
    const char *str_ptr = str;
    size_t len = 0;
    while(*str_ptr != '\0')
    {
        len++, str_ptr++;
    }
    return len;
}
