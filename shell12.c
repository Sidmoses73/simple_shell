#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: the parameter & return info struct
 * @args: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **args)
{
	ssize_t read_input = 0;
	int builtin_status = 0;

	while (read_input != -1 && builtin_status != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			print_prompt();
		flush_output();
		read_input = get_input(info);
		if (read_input != -1)
		{
			set_info(info, args);
			builtin_status = find_builtin_command(info);
			if (builtin_status == -1)
				find_command(info);
		}
		else if (is_interactive(info))
			print_newline();
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_status == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_status);
}

/**
 * find_builtin_command - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin_command(info_t *info)
{
	int i, builtin_status = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin_status = builtintbl[i].func(info);
			break;
		}
	return (builtin_status);
}
/**
 * execute_cmd - finds and executes a command
 * @info: the input command & return info struct
 * This function is responsible for finding and executing a command using the
 * arguments stored in the info struct.
 * Return: void
*/
void execute_cmd(info_t *info)
{
char *cmd_path = NULL;
int arg_count = 0;

/* Set path to first argument */
info->path = info->argv[0];

/* Update line count if linecount_flag is set */
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}

/* Count number of arguments */
for (int i = 0; info->arg[i]; i++)
if (!is_delimiter(info->arg[i], " \t\n"))
arg_count++;

/* If no arguments, return */
if (!arg_count)
return;

/* Find command path */
cmd_path = find_command_path(info, _get_env(info, "PATH="), info->argv[0]);
if (cmd_path)
{
/ Set command path to info struct and fork process /
info->path = cmd_path;
run_command(info);
}
else
{
if ((interactive(info) || _get_env(info, "PATH=")
|| info->argv[0][0] == '/') && is_builtin_command(info, info->argv[0]))
run_command(info);
else if ((info->arg) != '\n')
{
info->status = 127;
print_error(info, "Command not found\n");
}
}
}

/**
 * run_command - forks a new process and execute the command
 * @info: the input command & return info struct
 * This function forks a new process and executes
 * the command specified in the
 * info struct using the path stored in info->path.
 * Return: void
*/
void run_command(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}

if (child_pid == 0)
{
/* Execute command in child process */
if (execve(info->path, info->argv, get_environment(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
/* Wait for child process to finish */
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
