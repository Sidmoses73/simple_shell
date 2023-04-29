#include "my_shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status (0)
 * if info->argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = my_erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			my_eputs(info->argv[1]);
			my_eputchar('\n');
			return (1);
		}
		info->err_num = my_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_dir - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int change_dir(info_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = my_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = my_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (my_strcmp(info->argv[1], "-") == 0)
	{
		if (!my_getenv(info, "OLDPWD="))
		{
			my_puts(cwd);
			my_putchar('\n');
			return (1);
		}
		my_puts(my_getenv(info, "OLDPWD="));
		my_putchar('\n');
		chdir_ret = chdir((dir = my_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		my_eputs(info->argv[1]);
		my_eputchar('\n');
	}
	else
	{
		my_setenv(info, "OLDPWD", my_getenv(info, "PWD="));
		my_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_shell - displays help information
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int help_shell(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	my_puts("help call works. Function not yet implemented \n");
	if (0)
		my_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
