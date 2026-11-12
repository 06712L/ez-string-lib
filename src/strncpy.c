#include <stddef.h>
#include <stdlib.h>
#include "ez-string.h"

char* ez_strncpy(char *target, const char *str, size_t n)
{
    if(n == 0) return target;
    if(str == NULL || target == NULL) return NULL;

    const char *str_ptr = str;
    char *target_ptr = target;
    for(; n > 0 && *str_ptr != '\0'; n--)
    {
        *target_ptr = *str_ptr;
        target_ptr++, str_ptr++;
    }
    *target_ptr = '\0';
    return target;
}
