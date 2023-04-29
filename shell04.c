#include "shell.h"

/**
 * print_env - prints the current environment variables
 * @shell_info: Structure containing potential arguments.
 * Return: Always 0
 */
int print_env(shell_info_t *shell_info)
{
	print_list_str(shell_info->env_vars);
	return (0);
}

/**
 * get_env - gets the value of an environment variable
 * @shell_info: Structure containing potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(shell_info_t *shell_info, const char *name)
{
	list_t *node = shell_info->env_vars;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Initialize a new environment variable,
 *           or modify an existing one
 * @shell_info: Structure containing potential arguments.
 * Return: Always 0
 */
int set_env(shell_info_t *shell_info)
{
	if (shell_info->arg_count != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(shell_info, shell_info->arguments[1], shell_info->arguments[2]))
		return (0);
	return (1);
}

/**
 * unset_env - Remove an environment variable
 * @shell_info: Structure containing potential arguments.
 * Return: Always 0
 */
int unset_env(shell_info_t *shell_info)
{
	int i;

	if (shell_info->arg_count == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= shell_info->arg_count; i++)
		_unsetenv(shell_info, shell_info->arguments[i]);

	return (0);
}

/**
 * populate_env_vars_list - populates env linked list
 * @shell_info: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_vars_list(shell_info_t *shell_info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	shell_info->env_vars = node;
	return (0);
}

