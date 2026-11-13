#include "ez-string.h"
#include <errno.h>
#include <stdlib.h>

char *ez_strdup(const char *str)
{
    if(str == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    char *tmp_str = malloc(ez_strlen(str) + 1); // str + '\0'
    if(tmp_str == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }

    return ez_strcpy(tmp_str, str);
}
