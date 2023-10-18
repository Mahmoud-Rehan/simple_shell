#include "main.h"

/**
 * delete_comment - Deletes comments from the input.
 * @in: Input string.
 * Return: Input without comments.
 */

char *delete_comment(char *in)
{
	int i, up_to;

	up_to = 0;

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = reallocate(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * loop - Shell loop.
 * @datash: Data.
 */

void loop(data_shell *datash)
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

			if (syntax_error_check(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}

			input = replace_var(input, datash);
			loop = separate_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
