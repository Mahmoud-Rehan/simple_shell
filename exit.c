#include "main.h"

/**
 * shell_exit - Exits the shell.
 * @data: Data.
 * Return: 0 on success.
 */

int shell_exit(shell_data *data)
{
	unsigned int ustatus;
	int digit;
	int str_len;
	int big_number;

	if (data->arguments[1] != NULL)
	{
		ustatus = _stoi(data->arguments[1]);
		digit = is_digit(data->arguments[1]);
		str_len = string_len(data->arguments[1]);
		big_number = ustatus > (unsigned int)INT_MAX;

		if (!digit || str_len > 10 || big_number)
		{
			_geterror(data, 2);
			data->stat = 2;
			return (1);
		}
		data->stat = (ustatus % 256);
	}

	return (0);
}
