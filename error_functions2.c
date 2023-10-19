#include "main.h"

/**
 * string_cat_cd - Concatenates the message for cd error.
 * @data: Data.
 * @message: The printed message.
 * @output: Error message
 * @lines_count: Lines counter.
 * Return: String
 */

char *string_cat_cd(shell_data *data, char *message, char *output,
		char *lines_count)
{
	char *illegal_flag;

	string_cpy(output, data->argv[0]);
	string_cat(output, ": ");
	string_cat(output, lines_count);
	string_cat(output, ": ");
	string_cat(output, data->arguments[0]);
	string_cat(output, message);

	if (data->arguments[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = data->arguments[1][1];
		illegal_flag[2] = '\0';
		string_cat(output, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		string_cat(output, data->arguments[1]);
	}

	string_cat(output, "\n");
	string_cat(output, "\0");

	return (output);
}

/**
 * get_error_cd - Error message for cd command.
 * @data: Data.
 * Return: String
 */

char *get_error_cd(shell_data *data)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = _itos(data->count);

	if (data->arguments[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = string_len(data->arguments[1]);
	}

	length = string_len(data->argv[0]) + string_len(data->arguments[0]);
	length += string_len(ver_str) + string_len(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = string_cat_cd(data, msg, error, ver_str);
	free(ver_str);

	return (error);
}

/**
 * not_found_error - Error message for command not found.
 * @data: Data.
 * Return: String.
 */

char *not_found_error(shell_data *data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = _itos(data->count);
	length = string_len(data->argv[0]) + string_len(ver_str);
	length += string_len(data->arguments[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	string_cpy(error, data->argv[0]);
	string_cat(error, ": ");
	string_cat(error, ver_str);
	string_cat(error, ": ");
	string_cat(error, data->arguments[0]);
	string_cat(error, ": not found\n");
	string_cat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * exit_error - Error message for exit.
 * @data: Data.
 * Return: String.
 */

char *exit_error(shell_data *data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = _itos(data->count);
	length = string_len(data->argv[0]) + string_len(ver_str);
	length += string_len(data->arguments[0]) +
		string_len(data->arguments[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	string_cpy(error, data->argv[0]);
	string_cat(error, ": ");
	string_cat(error, ver_str);
	string_cat(error, ": ");
	string_cat(error, data->arguments[0]);
	string_cat(error, ": Illegal number: ");
	string_cat(error, data->arguments[1]);
	string_cat(error, "\n\0");
	free(ver_str);

	return (error);
}
