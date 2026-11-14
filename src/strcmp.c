#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include "ez-string.h"

int ez_strcmp(const char *str1, const char *str2)
{
    if(str1 == NULL || str2 == NULL)
    {
        errno = EINVAL;
        return EZ_STRCMP_NULL;
    }
    int diff = 0;
    const unsigned char *ptr1 = (const unsigned char*)str1, *ptr2 = (const unsigned char*)str2;
    while(*ptr1 != '\0' && *ptr2 != '\0' && *ptr1 == *ptr2)
    {
        ptr1++, ptr2++;
    }
    diff = *ptr1 - *ptr2;
    return diff;
}
