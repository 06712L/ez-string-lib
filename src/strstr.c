#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "ez-string.h"

static inline bool check_size(const char *str, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        if(str[i] == '\0') return false;
    }
    return true;
}

static inline char* strstr_2c(const unsigned char *uhaystack, const unsigned char *uneedle)
{
    const uint32_t needle = ((uint32_t)uneedle[0] << 16U) | (uint32_t)uneedle[1];
    uint32_t haystack = ((uint32_t)uhaystack[0] << 16U) | (uint32_t)uhaystack[1];
    uhaystack += 2; // check unfilled character
    for(uint8_t c = *uhaystack; c != '\0' && needle != haystack; c = *++uhaystack)
    {
        haystack = ((uint32_t)haystack << 16U) | c;
    }
    if(needle == haystack) return (char*)uhaystack - 2;
    return NULL;
}

static inline char* strstr_3c(const unsigned char *uhaystack, const unsigned char *uneedle)
{
    const uint32_t needle = ((uint32_t)uneedle[0] << 16U) | ((uint32_t)uneedle[1] << 8U) | (uint32_t)uneedle[2];
    uint32_t haystack = ((uint32_t)uhaystack[0] << 16U) | ((uint32_t)uhaystack[1] << 8U) | (uint32_t)uhaystack[2];
    uhaystack += 3; // check unfilled character
    for(uint8_t c = *uhaystack; c != '\0' && needle != haystack; c = *++uhaystack)
    {
        haystack = ((uint32_t)uhaystack[-2] << 16U) | ((uint32_t)uhaystack[-1] << 8U) | c;
    }
    if(needle == haystack) return (char*)uhaystack - 3;
    return NULL;
}

char* ez_strstr(const char *haystack, const char *needle)
{
    if(haystack == NULL || needle == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    if(needle[0] == '\0') return (char*)haystack;
    const unsigned char *uhaystack = (const unsigned char*)haystack, *uneedle = (const unsigned char*)needle;

    uhaystack = (const unsigned char*)ez_strchr((const char*)uhaystack, uneedle[0]);

    // Handle short str
    if(uhaystack == NULL) return NULL;
    if(uneedle[1] == '\0') return (char*)uhaystack;
    else if(uneedle[2] == '\0')
    {
        if(!check_size((const char*)uhaystack, 2)) return NULL;
        return strstr_2c(uhaystack, uneedle);
    }
    else if(uneedle[3] == '\0')
    {
        if(!check_size((const char*)uhaystack, 3)) return NULL;
        return strstr_3c(uhaystack, uneedle);
    }

    // Start searching
    const unsigned char *flag = NULL;
    const size_t needle_len = ez_strlen(needle);
    if(needle_len > ez_strlen((char*)uhaystack)) return NULL;
    for(size_t i = 0; flag == NULL && uhaystack[i] != '\0'; uhaystack++)
    {
        flag = uhaystack;
        for(i = 0; i < needle_len; i++)
        {
            if(uhaystack[i] != uneedle[i])
            {
                flag = NULL;
                break;
            }
        }
    }
    return (char*)flag;
}
