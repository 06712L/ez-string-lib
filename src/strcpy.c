#include <stddef.h>
#include "ez-string.h"

char* ez_strcpy(char *target, const char *str)
{
    if(str == NULL || target == NULL) return NULL;

    const char *str_ptr = str;
    char *target_ptr = target;
    while(*str_ptr != '\0')
    {
        *target_ptr = *str_ptr;
        target_ptr++, str_ptr++;
    }
    *target_ptr = '\0';
    return target;
}
