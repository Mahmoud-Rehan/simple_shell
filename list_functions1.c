#include "main.h"

/**
 * insert_varnode_at_end - Insert a variable at the end
 * of a r_var list.
 * @head: Head of the list.
 * @lvar: Length of the variable.
 * @val: value of the variable.
 * @lval: Length of the value.
 * Return: Address.
 */

r_var *insert_varnode_at_end(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));

	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;
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
 * free_var_list - Frees The r_var list.
 * @head: head of the list.
 */

void free_var_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
