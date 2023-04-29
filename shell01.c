#include "my_shell.h"

/**
 * is_shell_interactive - Checks whether the shell is in interactive mode
 * @shell_info: Address of the shell information structure
 *
 * Return: 1 if shell is in interactive mode, 0 otherwise
 */
int is_shell_interactive(shell_info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->read_fd <= 2);
}

/**
 * is_character_delimiter - Checks whether a character is a delimiter
 * @c: The character to check
 * @delimiters: The string of delimiters
 *
 * Return: 1 if c is a delimiter, 0 otherwise
 */
int is_character_delimiter(char c, char *delimiters)
{
	while (*delimiters)
	{
		if (*delimiters++ == c)
			return (1);
	}
	return (0);
}

/**
 * is_character_alpha - Checks whether a character is an alphabetic character
 * @c: The character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_character_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_string_to_integer - Converts a string to an integer
 * @s: The string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convert_string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
