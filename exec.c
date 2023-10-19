#include "main.h"

/**
 * execute_line - Finds builtins and commands.
 * @data: Data.
 * Return: 1 on success.
 */

int execute_line(shell_data *data)
{
	int (*builtin)(shell_data *data);

	if (data->arguments[0] == NULL)
		return (1);

	builtin = _getbuiltin(data->arguments[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (execute_command(data));
}
