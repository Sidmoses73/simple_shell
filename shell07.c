#include "shell.h"

/**
 * copy_string - copies a string
 * @dst: the destination string to be copied to
 * @src: the source string
 * @max_len: the maximum amount of characters to be copied
 *
 * Return: the copied string
 */
char *copy_string(char *dst, char *src, int max_len)
{
int i, j;
char *s = dst;

i = 0;
while (src[i] != '\0' && i < max_len - 1)
{
dst[i] = src[i];
i++;
}
if (i < max_len)
{
j = i;
while (j < max_len)
{
dst[j] = '\0';
j++;
}
}
return (s);
}

/**
 * concatenate_string - concatenates two strings
 * @dst: the first string
 * @src: the second string
 * @max_len: the maximum amount of bytes to be used
 *
 * Return: the concatenated string
 */
char *concatenate_string(char *dst, char *src, int max_len)
{
int i, j;
char *s = dst;

i = 0;
j = 0;
while (dst[i] != '\0')
i++;
while (src[j] != '\0' && j < max_len)
{
dst[i] = src[j];
i++;
j++;
}
if (j < max_len)
dst[i] = '\0';
return (s);
}

/**
 * find_character - locates a character in a string
 * @str: the string to be searched
 * @c: the character to look for
 *
 * Return: a pointer to the memory area of the string
 */
char *find_character(char *str, char c)
{
do {
if (*str == c)
return (str);
} while (*str++ != '\0');

return (NULL);
}
