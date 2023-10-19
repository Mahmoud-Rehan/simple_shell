#include "main.h"

/**
 * insert_sepnode_at_end - Insert a separator at the end.
 * @head_ptr: Head of the list.
 * @sp: Separator.
 * Return: Address.
 */

sep_t *insert_sepnode_at_end(sep_t **head_ptr, char sp)
{
	sep_t *new, *temp;

	new = malloc(sizeof(sep_t));

	if (new == NULL)
		return (NULL);

	new->sep = sp;
	new->next = NULL;
	temp = *head_ptr;

	if (temp == NULL)
	{
		*head_ptr = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new;
	}

	return (*head_ptr);
}

/**
 * free_sep_list - Frees The sep_t.
 * @head_ptr: Head of the list.
 */

void free_sep_list(sep_t **head_ptr)
{
	sep_t *temp;
	sep_t *curr;

	if (head_ptr != NULL)
	{
		curr = *head_ptr;

		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}

		*head_ptr = NULL;
	}
}

/**
 * insert_cmdnode_at_end - Insert a command at the end.
 * @head_ptr: Head of the list.
 * @command: Command.
 * Return: Address.
 */

cmdline_t *insert_cmdnode_at_end(cmdline_t **head_ptr, char *command)
{
	cmdline_t *new, *temp;

	new = malloc(sizeof(cmdline_t));

	if (new == NULL)
		return (NULL);

	new->cmd = command;
	new->next = NULL;
	temp = *head_ptr;

	if (temp == NULL)
	{
		*head_ptr = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new;
	}

	return (*head_ptr);
}

/**
 * free_cmdline_list - Frees The line_list.
 * @head_ptr: Head of the list.
 */

void free_cmdline_list(cmdline_t **head_ptr)
{
	cmdline_t *temp;
	cmdline_t *curr;

	if (head_ptr != NULL)
	{
		curr = *head_ptr;

		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}

		*head_ptr = NULL;
	}
}
