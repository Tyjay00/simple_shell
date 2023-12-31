#include "shell.h"

/**
 * replace_string - Replaces a string with a new one.
 * @old: Address of the old string to be replaced.
 * @new: New string to replace the old one.
 *
 * Return: 1 if the string is replaced successfully, 0 otherwise.
 *
 * Description: This function is used to replace a string with a new one.
 * It frees the memory occupied by the old string and assigns
 * the address of the new string to the pointer 'old'.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string with their values.
 * @info: Pointer to the parameter struct containing the tokens.
 *
 * Return: 1 if variables are replaced successfully, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * check_chain - Checks if we should continue chaining based on the last status
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer containing the command line.
 * @p: Address of the current position in 'buf'.
 * @i: Starting position in 'buf'.
 * @len: Length of 'buf'.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * is_chain - Tests if the current character in the buffer is a chain delimiter
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer containing the command line.
 * @p: Address of the current position in 'buf'.
 *
 * Return: 1 if the current character is a chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if the alias is replaced successfully, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
