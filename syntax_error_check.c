#include "main.h"

/**
 * char_repeated - Counts the repetitions of a char.
 * @input_str: Input string.
 * @n: Index
 * Return: Integer.
 */

int char_repeated(char *input_str, int n)
{
	if (*(input_str - 1) == *input_str)
	{
		return (char_repeated(input_str - 1, n + 1));
	}

	return (n);
}

/**
 * sep_error - Finds syntax errors.
 * @input_str: Input string.
 * @n: Index.
 * @c: Last char read.
 * Return: Integer.
 */

int sep_error(char *input_str, int n, char c)
{
	int count;

	count = 0;
	if (*input_str == '\0')
		return (0);

	if (*input_str == ' ' || *input_str == '\t')
		return (sep_error(input_str + 1, n + 1, c));

	if (*input_str == ';')
		if (c == '|' || c == '&' || c == ';')
			return (n);

	if (*input_str == '|')
	{
		if (c == ';' || c == '&')
			return (n);

		if (c == '|')
		{
			count = char_repeated(input_str, 0);
			if (count == 0 || count > 1)
				return (n);
		}
	}

	if (*input_str == '&')
	{
		if (c == ';' || c == '|')
			return (n);

		if (c == '&')
		{
			count = char_repeated(input_str, 0);

			if (count == 0 || count > 1)
				return (n);
		}
	}
	return (sep_error(input_str + 1, n + 1, *input_str));
}

/**
 * first_char_indx - Finds index of the first char.
 * @input_str: Input string.
 * @n: Index.
 * Return: 1 or 0.
 */

int first_char_indx(char *input_str, int *n)
{

	for (*n = 0; input_str[*n]; *n += 1)
	{
		if (input_str[*n] == ' ' || input_str[*n] == '\t')
			continue;

		if (input_str[*n] == ';' || input_str[*n] == '|' || input_str[*n] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * syntax_error_print - Prints when a syntax error.
 * @data: Data.
 * @input_str: Input string.
 * @n: Index.
 * @bool: Control message error.
 */

void syntax_error_print(shell_data *data, char *input_str, int n, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input_str[n] == ';')
	{
		if (bool == 0)
			msg = (input_str[n + 1] == ';' ? ";;" : ";");
		else
			msg = (input_str[n - 1] == ';' ? ";;" : ";");
	}

	if (input_str[n] == '|')
		msg = (input_str[n + 1] == '|' ? "||" : "|");

	if (input_str[n] == '&')
		msg = (input_str[n + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itos(data->count);
	length = string_len(data->argv[0]) + string_len(counter);
	length += string_len(msg) + string_len(msg2) + string_len(msg3) + 2;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(counter);
		return;
	}

	string_cpy(error, data->argv[0]);
	string_cat(error, ": ");
	string_cat(error, counter);
	string_cat(error, msg2);
	string_cat(error, msg);
	string_cat(error, msg3);
	string_cat(error, "\0");
	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * syntax_error_check - Find and print a syntax error.
 * @data: Data.
 * @input_str: Input string.
 * Return: 1 or 0.
 */

int syntax_error_check(shell_data *data, char *input_str)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char_indx(input_str, &begin);

	if (f_char == -1)
	{
		syntax_error_print(data, input_str, begin, 0);
		return (1);
	}

	i = sep_error(input_str + begin, 0, *(input_str + begin));

	if (i != 0)
	{
		syntax_error_print(data, input_str, begin + i, 1);
		return (1);
	}

	return (0);
}
