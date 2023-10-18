#include "main.h"

/**
 * environ_error - Error message for env.
 * @datash: Data.
 * Return: String.
 */

char *environ_error(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = _itos(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = string_len(datash->av[0]) + string_len(ver_str);
	length += string_len(datash->args[0]) + string_len(msg) + 4;
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
	string_cat(error, msg);
	string_cat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * path_error - Error message for path and failure denied permission.
 * @datash: Data.
 * Return: String.
 */

char *path_error(data_shell *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = _itos(datash->counter);
	length = string_len(datash->av[0]) + string_len(ver_str);
	length += string_len(datash->args[0]) + 24;
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
	string_cat(error, ": Permission denied\n");
	string_cat(error, "\0");
	free(ver_str);

	return (error);
}
