#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include "ez-string.h"

typedef struct replace_flag
{
    const char *flag;
    struct replace_flag *next;
}replace_flag;

static replace_flag* add_replace_flag(const char *flag, replace_flag *node_tail)
{
    replace_flag *ptr = malloc(sizeof(replace_flag));
    if(ptr == NULL) return NULL;
    ptr->flag = flag;
    ptr->next = NULL;
    if(node_tail != NULL) node_tail->next = ptr;
    return ptr;
}

static void free_all_replace_flag(replace_flag *node_head)
{
    if(node_head == NULL) return;
    replace_flag *next;
    for(; node_head != NULL; node_head = next)
    {
        next = node_head->next;
        free(node_head);
    }
}

char* ez_strreplace(char *str, const char *target_str, const char *replace_str, int replace_mode, bool in_place, bool auto_realloc)
{
    // Check arg
    if(str == NULL || target_str == NULL || replace_str == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    if(str[0] == '\0')
    {
        return NULL;
    }
    if(target_str[0] == '\0')
    {
        errno = EINVAL;
        return NULL;
    }
    if(replace_mode < EZ_STRREPLACE_FIRST || replace_mode > EZ_STRREPLACE_ALL)
    {
        errno = EINVAL;
        return NULL;
    }

    // Set size
    const size_t target_str_len = ez_strlen(target_str);
    const size_t replace_str_len = ez_strlen(replace_str);
    const ssize_t rt_diff = (ssize_t)replace_str_len - (ssize_t)target_str_len;
    size_t after_replace_size = ez_strlen(str) + 1; // str_size + '\0'
    replace_flag *node_head = NULL;
    replace_flag *node_tail = NULL;
    {
        bool change_size = true;
        for(const char *ptr = str; ptr != NULL; ptr += target_str_len)
        {
            ptr = ez_strstr(ptr, target_str);
            if(ptr == NULL)
            {
                if(node_head == NULL) return NULL;
                break;
            }
                node_tail = add_replace_flag(ptr, node_tail);
                if(node_tail == NULL)
                {
                    free_all_replace_flag(node_head);
                    return NULL;
                }
                if(node_head == NULL) node_head = node_tail;
            if(change_size)
            {
                after_replace_size += rt_diff;
                if(replace_mode == EZ_STRREPLACE_LAST) change_size = false;
            }
            if(replace_mode == EZ_STRREPLACE_FIRST) break;
        }
    }

    // Start replacing
    char *tmp_str = malloc(after_replace_size);
    if(tmp_str == NULL)
    {
        free_all_replace_flag(node_head);
        return NULL;
    }

    // Handle EZ_STRREPLACE_ALL
    if(replace_mode == EZ_STRREPLACE_ALL)
    {
        replace_flag *node = node_head;
        char *tmp_str_ptr = tmp_str;
        const char *str_ptr = str;
        size_t diff = (size_t)(node->flag - str);
        while(*str_ptr != '\0')
        {
            if(str_ptr == node->flag)
            {
                (void)ez_strcpy(tmp_str_ptr, replace_str);
                tmp_str_ptr += replace_str_len;
                str_ptr += target_str_len;
                if(node->next == NULL)
                {
                    (void)ez_strcpy(tmp_str_ptr, str_ptr);
                    break;
                }
                node = node->next;
                diff = (size_t)(node->flag - str_ptr);
            }
            else
            {
                (void)ez_strncpy(tmp_str_ptr, str_ptr, diff);
                tmp_str_ptr += diff;
                str_ptr += diff;
            }
        }
    }

    // Handle EZ_STRREPLACE_FIRST and EZ_STRREPLACE_LAST
    else
    {
        replace_flag *node = (replace_mode == EZ_STRREPLACE_FIRST) ? node_head:node_tail;
        const char *str_ptr = str;
        char *tmp_str_ptr = tmp_str;
        size_t diff = (size_t)(node->flag - str);

        // Head
        (void)ez_strncpy(tmp_str_ptr, str_ptr, diff);
        tmp_str_ptr += diff;
        str_ptr += diff;

        // Replace
        (void)ez_strcpy(tmp_str_ptr, replace_str);
        tmp_str_ptr += replace_str_len;
        str_ptr += target_str_len;

        // Tail
        (void)ez_strcpy(tmp_str_ptr, str_ptr);
    }
    free_all_replace_flag(node_head);

    // Return results
    if(in_place)
    {
        if(auto_realloc)
        {
            char *tmp_ptr = realloc(str, after_replace_size);
            if(tmp_ptr == NULL)
            {
                free(tmp_str);
                return NULL;
            }
            str = tmp_ptr;
        }
        (void)ez_strcpy(str, tmp_str);
        free(tmp_str);
        return str;
    }
    else return tmp_str;
}
