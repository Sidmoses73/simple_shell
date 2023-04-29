#include "shell.h"

/**
 * print_command_history - displays the command history, one command per line,
 *                         preceded with line numbers, starting at 0.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0
 */
int print_command_history(shell_info_t *shell_info)
{
	print_list(shell_info->command_history);
	return (0);
}

/**
 * unset_command_alias - removes an alias from the command alias list.
 * @shell_info: Shell information struct.
 * @alias_str: The alias string to remove.
 * Return: Always 0 on success, 1 on error
 */
int unset_command_alias(shell_info_t *shell_info, char *alias_str)
{
	char *p, c;
	int ret;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(shell_info->command_aliases),
		get_node_index(shell_info->command_aliases, node_starts_with(shell_info->command_aliases, alias_str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_command_alias - adds or modifies a command alias.
 * @shell_info: Shell information struct.
 * @alias_str: The alias string.
 * Return: Always 0 on success, 1 on error
 */
int set_command_alias(shell_info_t *shell_info, char *alias_str)
{
	char *p;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_command_alias(shell_info, alias_str));

	unset_command_alias(shell_info, alias_str);
	return (add_node_end(&(shell_info->command_aliases), alias_str, 0) == NULL);
}

/**
 * print_command_alias - prints a command alias.
 * @alias_node: The command alias node.
 * Return: Always 0 on success, 1 on error
 */
int print_command_alias(list_t *alias_node)
{
	char *p = NULL, *alias = NULL;

	if (alias_node)
	{
		p = _strchr(alias_node->str, '=');
		for (alias = alias_node->str; alias <= p; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * handle_command_alias - adds or modifies a command alias, or displays
 *                        existing aliases.
 * @shell_info: Shell information struct.
 * Return: Always 0
 */
int handle_command_alias(shell_info_t *shell_info)
{
	int i = 0;
	char *p = NULL;
	list_t *alias_node = NULL;

	if (shell_info->argc == 1)
	{
		alias_node = shell_info->command_aliases;
		while (alias_node)
		{
			print_command_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; shell_info->argv[i]; i++)
	{
		p = _strchr(shell_info->argv[i], '=');
		if (p)
			set_command_alias(shell_info, shell_info->argv[i]);
		else
			print_command_alias(node_starts_with(shell_info->command_aliases, shell_info->argv[i], '='));
	}

	return (0);
}
