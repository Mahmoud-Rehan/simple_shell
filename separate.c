#include "main.h"

/**
 * _swapchar - swaps | and & for non-printed chars.
 * @input: Input string.
 * @bool: Type of swap.
 * Return: String.
 */

char *_swapchar(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}

	return (input);
}

/**
 * insert_nodes - insert separators and commands in the lists.
 * @head_s: Head of separator list
 * @head_l: Head of command lines list
 * @input: Input string
 */

void insert_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = _swapchar(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			insert_sepnode_at_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			insert_sepnode_at_end(head_s, input[i]);
			i++;
		}
	}

	line = string_tok(input, ";|&");

	do {
		line = _swapchar(line, 1);
		insert_cmdnode_at_end(head_l, line);
		line = string_tok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * _next - Go to the next command line stored.
 * @list_s: Separator list.
 * @list_l: Command list.
 * @datash: Data structure.
 */

void _next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * separate_commands - Splits command lines.
 * @datash: Data.
 * @input: Input string.
 * Return: 0 or 1.
 */

int separate_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;
	insert_nodes(&head_s, &head_l, input);
	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = separate_input(datash->input);
		loop = execute_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_cmdline_list(&head_l);

	if (loop == 0)
		return (0);

	return (1);
}

/**
 * separate_input - Tokenize the input string.
 * @input: Input string.
 * Return: String.
 */

char **separate_input(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));

	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = string_tok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = realloc_dptr(tokens, i, sizeof(char *) * bsize);

			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = string_tok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
