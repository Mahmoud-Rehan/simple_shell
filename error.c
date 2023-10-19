#include "main.h"

/**
 * _geterror - Calls the error according the builtin.
 * @data: Data.
 * @error_val: Error value.
 * Return: Integer.
 */

int _geterror(shell_data *data, int error_val)
{
	char *error;

	switch (error_val)
	{
	case -1:
		error = environ_error(data);
		break;
	case 126:
		error = path_error(data);
		break;
	case 127:
		error = not_found_error(data);
		break;
	case 2:
		if (string_cmp("exit", data->arguments[0]) == 0)
			error = exit_error(data);
		else if (string_cmp("cd", data->arguments[0]) == 0)
			error = get_error_cd(data);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, string_len(error));
		free(error);
	}
	data->stat = error_val;

	return (error_val);
}
