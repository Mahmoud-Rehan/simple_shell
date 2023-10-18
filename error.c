#include "main.h"

/**
 * _geterror - Calls the error according the builtin.
 * @datash: Data.
 * @eval: Error value.
 * Return: Integer.
 */

int _geterror(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = environ_error(datash);
		break;
	case 126:
		error = path_error(datash);
		break;
	case 127:
		error = not_found_error(datash);
		break;
	case 2:
		if (string_cmp("exit", datash->args[0]) == 0)
			error = exit_error(datash);
		else if (string_cmp("cd", datash->args[0]) == 0)
			error = get_error_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, string_len(error));
		free(error);
	}
	datash->status = eval;

	return (eval);
}
