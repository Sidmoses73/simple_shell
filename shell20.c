#include “shell.h”
/**
* longest_word_length - finds the length of the longest word in a string
* @str: the input string
* Return: the length of the longest word, or 0 on failure
*/
int longest_word_length(char *str)
{
int i, len = 0, max_len = 0;
if (str == NULL || str[0] == 0)
return (0);
for (i = 0; str[i] != '\0'; i++)
{
if (isspace(str[i]))
{
if (len > max_len)
max_len = len;
len = 0;
}
else
{
len++;
}
}
if (len > max_len)
max_len = len;
return (max_len);
}

