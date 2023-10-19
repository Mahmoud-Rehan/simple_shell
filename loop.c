#include "main.h"

/**
 * delete_comment - Deletes comments from the input.
 * @input: Input string.
 * Return: Input without comments.
 */

char *delete_comment(char *input)
{
	int i, up_to;

	up_to = 0;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		input = reallocate(input, i, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
 * loop - Shell loop.
 * @data: Data.
 */

void loop(shell_data *data)
{
	int loop, i_eof;
	char *input;

	loop = 1;

	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = _readline(&i_eof);

		if (i_eof != -1)
		{
			input = delete_comment(input);

			if (input == NULL)
				continue;

			if (syntax_error_check(data, input) == 1)
			{
				data->stat = 2;
				free(input);
				continue;
			}

			input = replace_var(input, data);
			loop = separate_commands(data, input);
			data->count += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
