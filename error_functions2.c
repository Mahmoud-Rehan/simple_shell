#include "main.h"

/**
 * string_cat_cd - Concatenates the message for cd error.
 * @datash: Data.
 * @msg: The printed message.
 * @error: Error message
 * @ver_str: Lines counter.
 * Return: String
 */

char *string_cat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	string_cpy(error, datash->av[0]);
	string_cat(error, ": ");
	string_cat(error, ver_str);
	string_cat(error, ": ");
	string_cat(error, datash->args[0]);
	string_cat(error, msg);

	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		string_cat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		string_cat(error, datash->args[1]);
	}

	string_cat(error, "\n");
	string_cat(error, "\0");

	return (error);
}

/**
 * get_error_cd - Error message for cd command.
 * @datash: Data.
 * Return: String
 */

char *get_error_cd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = _itos(datash->counter);

	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = string_len(datash->args[1]);
	}

	length = string_len(datash->av[0]) + string_len(datash->args[0]);
	length += string_len(ver_str) + string_len(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = string_cat_cd(datash, msg, error, ver_str);
	free(ver_str);

	return (error);
}

/**
 * not_found_error - Error message for command not found.
 * @datash: Data.
 * Return: String.
 */

char *not_found_error(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = _itos(datash->counter);
	length = string_len(datash->av[0]) + string_len(ver_str);
	length += string_len(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	string_cpy(error, datash->av[0]);
	string_cat(error, ": ");
	string_cat(error, ver_str);
	string_cat(error, ": ");
	string_cat(error, datash->args[0]);
	string_cat(error, ": not found\n");
	string_cat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * exit_error - Error message for exit.
 * @datash: Data.
 * Return: String.
 */

char *exit_error(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = _itos(datash->counter);
	length = string_len(datash->av[0]) + string_len(ver_str);
	length += string_len(datash->args[0]) + string_len(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	string_cpy(error, datash->av[0]);
	string_cat(error, ": ");
	string_cat(error, ver_str);
	string_cat(error, ": ");
	string_cat(error, datash->args[0]);
	string_cat(error, ": Illegal number: ");
	string_cat(error, datash->args[1]);
	string_cat(error, "\n\0");
	free(ver_str);

	return (error);
}
