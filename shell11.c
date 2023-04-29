#include "shell.h"

/**
 * entry - Entry point of the shell program
 * @argument_count: Number of arguments passed to the program
 * @arguments: Array of argument strings passed to the program
 *
 * Return: 0 on success, 1 on error
 */
int entry(int argument_count, char **arguments)
{
	ShellInfo shell_info[] = { SHELL_INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_descriptor)
			: "r" (file_descriptor));

	if (argument_count == 2)
	{
		file_descriptor = open(arguments[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_print_shell_name(arguments[0]);
				_print_shell_name(": 0: Can't open ");
				_print_shell_name(arguments[1]);
				_put_character('\n');
				_put_character(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shell_info->read_file_descriptor = file_descriptor;
	}
	populate_environment_list(shell_info);
	read_shell_history(shell_info);
	launch_shell(shell_info, arguments);
	return (EXIT_SUCCESS);
}
