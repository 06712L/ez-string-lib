#include <errno.h>
#include <stddef.h>
#include "ez-string.h"

char* ez_strrchr(const char *s, const char c)
{
    if(s == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    if(c == '\0') return (char*)s + ez_strlen(s);
    if(s[0] == '\0') return NULL;
    const unsigned char *us = (const unsigned char*)s + ez_strlen(s);
    const unsigned char uc = (const unsigned char)c;
    while(us >= (const unsigned char*)s)
    {
        if(*us == uc) return (char*)us;
        us--;
    }
    return NULL;
}
