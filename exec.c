#include "main.h"

/**
 * execute_line - Finds builtins and commands.
 * @datash: Data.
 * Return: 1 on success.
 */

int execute_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = _getbuiltin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (execute_command(datash));
}
