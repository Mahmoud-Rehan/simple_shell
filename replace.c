#include "main.h"

/**
 * environ_check - Checks if the typed var is an env variable.
 * @head: Head of list.
 * @input: Input string.
 * @data: Data.
 */

void environ_check(var_t **head, char *input, shell_data *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->env;

	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = string_len(_envr[row] + chr + 1);
				insert_varnode_at_end(head, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (input[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t' ||
				input[j] == ';' || input[j] == '\n')
			break;
	}

	insert_varnode_at_end(head, j, NULL, 0);
}

/**
 * vars_check - Check if the typed variable is $$ or $?
 * @head: Head of the list.
 * @input: Input string.
 * @last: Last status of the Shell.
 * @data: Data.
 * Return: Integer.
 */

int vars_check(var_t **head, char *input, char *last, shell_data *data)
{
	int i, lst, lpd;

	lst = string_len(last);
	lpd = string_len(data->pid);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				insert_varnode_at_end(head, 2, last, lst), i++;
			else if (input[i + 1] == '$')
				insert_varnode_at_end(head, 2, data->pid, lpd), i++;
			else if (input[i + 1] == '\n')
				insert_varnode_at_end(head, 0, NULL, 0);
			else if (input[i + 1] == '\0')
				insert_varnode_at_end(head, 0, NULL, 0);
			else if (input[i + 1] == ' ')
				insert_varnode_at_end(head, 0, NULL, 0);
			else if (input[i + 1] == '\t')
				insert_varnode_at_end(head, 0, NULL, 0);
			else if (input[i + 1] == ';')
				insert_varnode_at_end(head, 0, NULL, 0);
			else
				environ_check(head, input + i, data);
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

char *replace_input(var_t **head, char *input, char *new_input, int nlen)
{
	var_t *indx;
	int i, j, k;

	indx = *head;

	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->var_length) && !(indx->val_length))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->var_length && !(indx->val_length))
			{
				for (k = 0; k < indx->var_length; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->val_length; k++)
				{
					new_input[i] = indx->value[k];
					i++;
				}
				j += (indx->var_length);
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
 * @input_str: Input string.
 * @data: Data.
 * Return: String.
 */

char *replace_var(char *input_str, shell_data *data)
{
	var_t *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = _itos(data->stat);
	head = NULL;
	olen = vars_check(&head, input_str, status, data);

	if (head == NULL)
	{
		free(status);
		return (input_str);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->val_length - indx->var_length);
		indx = indx->next;
	}

	nlen += olen;
	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';
	new_input = replace_input(&head, input_str, new_input, nlen);
	free(input_str);
	free(status);
	free_var_list(&head);

	return (new_input);
}
