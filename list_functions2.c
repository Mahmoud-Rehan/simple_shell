#include "main.h"

/**
 * insert_sepnode_at_end - Insert a separator at the end.
 * of a sep_list.
 * @head: Head of the list.
 * @sep: Separator.
 * Return: Address.
 */

sep_list *insert_sepnode_at_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));

	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - Frees The sep_list.
 * @head: Head of the list.
 */

void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;

		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}

		*head = NULL;
	}
}

/**
 * insert_cmdlinenode_at_end - Insert a command at the end
 * of a line_list.
 * @head: Head of the list.
 * @line: Command.
 * Return: Address.
 */

line_list *insert_cmdnode_at_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));

	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new;
	}

	return (*head);
}

/**
 * free_cmdline_list - Frees The line_list.
 * @head: Head of the list.
 */

void free_cmdline_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;

		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}

		*head = NULL;
	}
}
