#include "my_shell.h"

/**
 * str_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int str_to_int(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make the program return 255? */
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_msg - prints an error message
 * @info: the parameter & return info structure
 * @error_msg: string containing specified error type
 * Return: None
 */
void print_error_msg(info_t *info, char *error_msg)
{
	my_puts(info->file_name);
	my_puts(": ");
	my_put_nbr(info->line_count, STDERR_FILENO);
	my_puts(": ");
	my_puts(info->arguments[0]);
	my_puts(": ");
	my_puts(error_msg);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @number: the number to be printed
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int number, int fd)
{
	int (*my_putchar_ptr)(char) = my_putchar;
	int index, count = 0;
	unsigned int absolute_num, current_num;

	if (fd == STDERR_FILENO)
		my_putchar_ptr = my_eputchar;
	if (number < 0)
	{
		absolute_num = -number;
		my_putchar_ptr('-');
		count++;
	}
	else
		absolute_num = number;
	current_num = absolute_num;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absolute_num / index)
		{
			my_putchar_ptr('0' + current_num / index);
			count++;
		}
		current_num %= index;
	}
	my_putchar_ptr('0' + current_num);
	count++;

	return (count);
}

/**
 * num_to_str - function converts a number to a string
 * @num: number to be converted
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *num_to_str(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long converted_num = num;

	if (!(flags & UNSIGNED_CONVERSION) && num < 0)
	{
		converted_num = -num;
		sign = '-';
	}
	array = flags & LOWERCASE_CONVERSION ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[converted_num % base];
		converted_num /= base;
	} while (converted_num != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - function replaces the first instance of '#' with '\0'
 * @str: the string to modify
 * Return: Always void;
*/
void remove_first_comment(char *str)
{
int i;

for (i = 0; str[i] != '\0'; i++)
{
if (str[i] == '#' && (!i || str[i - 1] == ' '))
{
str[i] = '\0';
break;
}
}
}

