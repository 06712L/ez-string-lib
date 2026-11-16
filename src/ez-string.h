/**
 * @file ez-string.h
 * @author bananah2odev@gmail.com
 * @brief ez-string-lib header
 * @version 0.0.1
 * @date 2026-11-15
 * 
 * @copyright Copyright (c) 2026 Xie
 */

#ifndef EZ_STRING_H
#define EZ_STRING_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief get string length
 * 
 * @param str string to measure
 * @return size_t string length
 * @retval 0 str is NULL; also set errno to EINVAL
 *
 * @note an empty string also returns 0, without setting errno
 */
size_t ez_strlen(const char *str);

enum ez_strcmp_error_code
{
    EZ_STRCMP_NULL = 256,
};
/**
 * @brief compare two strings
 * 
 * @param str1 first string
 * @param str2 second string
 * @return int the difference between the strings
 * @retval 0 the strings are equal
 * @retval 256 (EZ_STRCMP_NULL) either string is NULL; also set errno to EINVAL
 *
 * @see EZ_STRCMP_NULL
 */
int ez_strcmp(const char *str1, const char *str2);

/**
 * @brief copy a string to the target
 * 
 * @param target destination buffer
 * @param str source string
 * @return char* the memory address of the target
 * @retval NULL either argument is NULL; also set errno to EINVAL
 */
char* ez_strcpy(char *target, const char *str);

/**
 * @brief copy a limited number of characters from a string to the target
 * 
 * @param target destination buffer
 * @param str source string
 * @param n maximum number of characters to copy
 * @return char* the memory address of the target
 * @retval NULL target or str is NULL; also set errno to EINVAL
 *
 * @note if n is 0, do nothing and return the memory address of the target
 */
char* ez_strncpy(char *target, const char *str, const size_t n);

/**
 * @brief locate a substring
 * 
 * @param haystack string to search
 * @param needle the target string
 * @return char* the memory address of the substring in haystack
 * @retval NULL not found the substring; errno is unchanged
 * @retval NULL either argument is NULL; also set errno to EINVAL
 *
 * @note if needle is an empty string, return the memory address of haystack
 */
char* ez_strstr(const char *haystack, const char *needle);

/**
 * @brief locate a character in a string
 * 
 * @param s string to search
 * @param c the target character
 * @return char* the memory address of the first occurrence of the character in the string
 * @retval NULL character not found; errno is unchanged
 * @retval NULL s is NULL; set errno to EINVAL
 *
 * @note if c is the null character, return the memory address of the end of the string
 */
char* ez_strchr(const char *s, const char c);

/**
 * @brief locate a character in a string
 * 
 * @param s string to search
 * @param c the target character
 * @return char* the memory address of the last occurrence of the character in the string
 * @retval NULL character not found; errno is unchanged
 * @retval NULL s is NULL; set errno to EINVAL
 *
 * @note if c is the null character, return the memory address of the end of the string
 */
char* ez_strrchr(const char *s, const char c);

/**
 * @brief duplicate a string
 * 
 * @param str source string
 * @return char* the memory address of the allocated string
 * @retval NULL str is NULL; also set errno to EINVAL
 * @retval NULL allocation failure; also set errno to ENOMEM
 *
 * @see ez_strcpy()
 */
char* ez_strdup(const char *str);

/**
 * @brief duplicate a limited number of characters from a string
 * 
 * @param str source string
 * @param n maximum number of characters to copy
 * @return char* the memory address of the allocated string
 * @retval NULL str is NULL; also set errno to EINVAL
 * @retval NULL allocation failure; also set errno to ENOMEM
 *
 * @see ez_strncpy()
 */
char* ez_strndup(const char *str, size_t n);

typedef enum ez_strreplace_replace_mode
{
    EZ_STRREPLACE_FIRST = 0,
    EZ_STRREPLACE_LAST = 1,
    EZ_STRREPLACE_ALL = 2,
}ez_strreplace_replace_mode;
/**
 * @brief replace a target string with a replacement string in a string
 * 
 * @param str source string
 * @param target_str the target string
 * @param replace_str the replacement string
 * @param replace_mode choose which occurrence to replace
 * @param in_place whether to modify the original string or create a new string
 * @param auto_realloc whether to automatically reallocate memory
 * @return char* the resulting string
 * @retval NULL the target string was not found; errno is unchanged
 * @retval NULL an argument is invalid; also set errno to EINVAL
 * @retval NULL memory allocation failed; also set errno to ENOMEM
 *
 * @note if in_place is false, auto_realloc is ignored
 * @note the function always allocates memory, so the caller must always handle allocation failure
 * @note if in_place is true, the function copies the resulting string to the source string and then frees the resulting string
 * @note if str is an empty string and all other arguments are valid, the results is considered not found rather than invalid argument
 * @warning if in_place is false, the returned string must be freed by the caller
 * @warning if in_place is true and auto_realloc is false, the caller must ensure that str has enough capacity
 * @warning if in_place is true and auto_realloc is true, the function does not update the caller's pointer; the caller must use the returned pointer
 *
 * @see EZ_STRREPLACE_FIRST
 * @see EZ_STRREPLACE_LAST
 * @see EZ_STRREPLACE_ALL
 */
char* ez_strreplace(char *str, const char *target_str, const char *replace_str, enum ez_strreplace_replace_mode replace_mode, bool in_place, bool auto_realloc);

#ifdef __cplusplus
}
#endif

#endif
