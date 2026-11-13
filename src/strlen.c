#include <errno.h>
#include <stddef.h>
#include "ez-string.h"

size_t ez_strlen(const char *str)
{
    if(str == NULL)
    {
        errno = EINVAL;
        return 0;
    }
    const char *str_ptr = str;
    size_t len = 0;
    while(*str_ptr != '\0')
    {
        len++, str_ptr++;
    }
    return len;
}
