#include <stddef.h>
#include <stdlib.h>
#include "ez-string.h"

char* ez_strncpy(char *target, const char *str, size_t n)
{
    if(n == 0) return NULL;
    const char *str_ptr = str;
    char *target_ptr = target;
    if(str == NULL) return NULL;
    else if(target == NULL)
    {
        size_t target_size = ez_strlen(str);
        if(target_size > n) target_size = n;
        target_ptr = malloc(target_size + 1);
        if(target_ptr == NULL) return NULL;
        target = target_ptr;
    }

    for(; n > 0 && *str_ptr != '\0'; n--)
    {
        *target_ptr = *str_ptr;
        target_ptr++, str_ptr++;
    }
    *target_ptr = '\0';
    return target;
}
