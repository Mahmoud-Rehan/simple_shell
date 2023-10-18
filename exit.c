#include "main.h"

/**
 * shell_exit - Exits the shell.
 * @datash: Data.
 * Return: 0 on success.
 */

int shell_exit(data_shell *datash)
{
	unsigned int ustatus;
	int digit;
	int str_len;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = _stoi(datash->args[1]);
		digit = is_digit(datash->args[1]);
		str_len = string_len(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;

		if (!digit || str_len > 10 || big_number)
		{
			_geterror(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}

	return (0);
}
