#include "shell.h"

/**
 * get_environment - Returns a copy of the string
 * array of our environment variables
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: String array copy of our environment variables
 */
char **get_environment(info_t *info)
{
	if (!info->environment || info->env_changed)
	{
		info->environment = list_to_string_array(info->env_list);
		info->env_changed = 0;
	}

	return (info->environment);
}

/**
 * remove_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * @var_name: The name of the environment variable to remove
 * Return: 1 on successful removal, 0 otherwise
 */
int remove_environment_variable(info_t *info, char *var_name)
{
	list_t *node = info->env_list;
	size_t i = 0;
	char *p;

	if (!node || !var_name)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var_name);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env_list), i);
			i = 0;
			node = info->env_list;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_environment_variable - Initialize a new environment
 * variable or modify an existing one
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * @var_name: The name of the environment variable to set or modify
 * @value: The value to assign to the environment variable
 * Return: 0 on successful set or modify, 1 otherwise
 */
int set_environment_variable(info_t *info, char *var_name, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var_name || !value)
		return (1);

	buf = malloc(_strlen(var_name) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var_name);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env_list;
	while (node)
	{
		p = starts_with(node->str, var_name);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_list), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
