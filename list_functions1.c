#include "main.h"

/**
 * insert_varnode_at_end - Insert a variable at the end.
 * @head_ptr: Head of the list.
 * @var_len: Length of the variable.
 * @value: value of the variable.
 * @val_len: Length of the value.
 * Return: Address.
 */

var_t *insert_varnode_at_end(var_t **head_ptr, int var_len,
		char *value, int val_len)
{
	var_t *new, *temp;

	new = malloc(sizeof(var_t));

	if (new == NULL)
		return (NULL);

	new->var_length = var_len;
	new->value = value;
	new->val_length = val_len;
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
 * free_var_list - Frees The r_var list.
 * @head_ptr: head of the list.
 */

void free_var_list(var_t **head_ptr)
{
	var_t *temp;
	var_t *curr;

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
