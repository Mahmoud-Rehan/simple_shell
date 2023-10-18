#include "main.h"

/**
 * char_repeated - Counts the repetitions of a char.
 * @input: Input string.
 * @i: Index
 * Return: Integer.
 */

int char_repeated(char *input, int i)
{
	if (*(input - 1) == *input)
	{
		return (char_repeated(input - 1, i + 1));
	}

	return (i);
}

/**
 * sep_error - Finds syntax errors.
 * @input: Input string.
 * @i: Index.
 * @last: Last char read.
 * Return: Integer.
 */

int sep_error(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (sep_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = char_repeated(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = char_repeated(input, 0);

			if (count == 0 || count > 1)
				return (i);
		}
	}
	return (sep_error(input + 1, i + 1, *input));
}

/**
 * first_char_indx - Finds index of the first char.
 * @input: Input string.
 * @i: Index.
 * Return: 1 or 0.
 */

int first_char_indx(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * syntax_error_print - Prints when a syntax error.
 * @datash: Data.
 * @input: Input string.
 * @i: Index.
 * @bool: Control message error.
 */

void syntax_error_print(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itos(datash->counter);
	length = string_len(datash->av[0]) + string_len(counter);
	length += string_len(msg) + string_len(msg2) + string_len(msg3) + 2;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(counter);
		return;
	}

	string_cpy(error, datash->av[0]);
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
 * @datash: Data.
 * @input: Input string.
 * Return: 1 or 0.
 */

int syntax_error_check(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char_indx(input, &begin);

	if (f_char == -1)
	{
		syntax_error_print(datash, input, begin, 0);
		return (1);
	}

	i = sep_error(input + begin, 0, *(input + begin));

	if (i != 0)
	{
		syntax_error_print(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
