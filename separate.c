#include "main.h"

/**
 * _swapchar - swaps | and & for non-printed chars.
 * @input_str: Input string.
 * @bool: Type of swap.
 * Return: String.
 */

char *_swapchar(char *input_str, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input_str[i]; i++)
		{
			if (input_str[i] == '|')
			{
				if (input_str[i + 1] != '|')
					input_str[i] = 16;
				else
					i++;
			}

			if (input_str[i] == '&')
			{
				if (input_str[i + 1] != '&')
					input_str[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input_str[i]; i++)
		{
			input_str[i] = (input_str[i] == 16 ? '|' : input_str[i]);
			input_str[i] = (input_str[i] == 12 ? '&' : input_str[i]);
		}
	}

	return (input_str);
}

/**
 * insert_nodes - insert separators and commands in the lists.
 * @sep_head: Head of separator list.
 * @cmd_head: Head of command lines list.
 * @input_str: Input string.
 */

void insert_nodes(sep_t **sep_head, cmdline_t **cmd_head, char *input_str)
{
	int i;
	char *line;

	input_str = _swapchar(input_str, 0);

	for (i = 0; input_str[i]; i++)
	{
		if (input_str[i] == ';')
			insert_sepnode_at_end(sep_head, input_str[i]);

		if (input_str[i] == '|' || input_str[i] == '&')
		{
			insert_sepnode_at_end(sep_head, input_str[i]);
			i++;
		}
	}

	line = string_tok(input_str, ";|&");

	do {
		line = _swapchar(line, 1);
		insert_cmdnode_at_end(cmd_head, line);
		line = string_tok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * _next - Go to the next command line stored.
 * @sep_list: Separator list.
 * @cmd_list: Command list.
 * @data: Data.
 */

void _next(sep_t **sep_list, cmdline_t **cmd_list, shell_data *data)
{
	int loop_sep;
	sep_t *ls_s;
	cmdline_t *ls_l;

	loop_sep = 1;
	ls_s = *sep_list;
	ls_l = *cmd_list;

	while (ls_s != NULL && loop_sep)
	{
		if (data->stat == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*sep_list = ls_s;
	*cmd_list = ls_l;
}

/**
 * separate_commands - Splits command lines.
 * @data: Data.
 * @input_str: Input string.
 * Return: 0 or 1.
 */

int separate_commands(shell_data *data, char *input_str)
{

	sep_t *head_s, *list_s;
	cmdline_t *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;
	insert_nodes(&head_s, &head_l, input_str);
	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		data->input = list_l->cmd;
		data->arguments = separate_input(data->input);
		loop = execute_line(data);
		free(data->arguments);

		if (loop == 0)
			break;

		_next(&list_s, &list_l, data);

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
 * @input_str: Input string.
 * Return: String.
 */

char **separate_input(char *input_str)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOKEN_BUFFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));

	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = string_tok(input_str, DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKEN_BUFFSIZE;
			tokens = realloc_dptr(tokens, i, sizeof(char *) * bsize);

			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = string_tok(NULL, DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
