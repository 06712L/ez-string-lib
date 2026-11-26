#include "ez-string.h"
#include <errno.h>
#include <stddef.h>

void *ez_memset(void *s, const char c, const size_t n)
{
    if(s == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    if(n == 0)
    {
        return s;
    }

    unsigned char *ptr = (unsigned char*)s;
    for(size_t i = 0; i < n; i++, ptr++)
    {
        *ptr = (unsigned char)c;
    }
    return s;
}