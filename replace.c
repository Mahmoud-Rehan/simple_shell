#include "main.h"

/**
 * environ_check - Checks if the typed var is an env variable.
 * @h:Hhead of list.
 * @in: Input string.
 * @data: Data.
 */

void environ_check(r_var **h, char *in, data_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;

	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = string_len(_envr[row] + chr + 1);
				insert_varnode_at_end(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	insert_varnode_at_end(h, j, NULL, 0);
}

/**
 * vars_check - Check if the typed variable is $$ or $?
 * @h: head of the list.
 * @in: input string.
 * @st: Last status of the Shell.
 * @data: Data.
 * Return: Integer.
 */

int vars_check(r_var **h, char *in, char *st, data_shell *data)
{
	int i, lst, lpd;

	lst = string_len(st);
	lpd = string_len(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				insert_varnode_at_end(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				insert_varnode_at_end(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				insert_varnode_at_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				insert_varnode_at_end(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				insert_varnode_at_end(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				insert_varnode_at_end(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				insert_varnode_at_end(h, 0, NULL, 0);
			else
				environ_check(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replace_input - Replaces string into variables.
 * @head: Head of the list.
 * @input: Input string.
 * @new_input: New input string.
 * @nlen: New length.
 * Return: String.
 */

char *replace_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;

	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * replace_var - Calls functions to replace string into vars.
 * @input: Input string.
 * @datash: Data.
 * Return: String.
 */

char *replace_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = _itos(datash->status);
	head = NULL;
	olen = vars_check(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;
	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';
	new_input = replace_input(&head, input, new_input, nlen);
	free(input);
	free(status);
	free_var_list(&head);

	return (new_input);
}
