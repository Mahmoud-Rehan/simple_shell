#include "main.h"

/**
 * memory_cpy - Copies information between void pointers.
 * @newp: Dest pointer.
 * @p: Src pointer.
 * @ptr_size: Size of the new pointer.
 */

void memory_cpy(void *newp, const void *p, unsigned int ptr_size)
{
	char *char_ptr = (char *)p;
	char *char_newptr = (char *)newp;
	unsigned int i;

	for (i = 0; i < ptr_size; i++)
	{
		char_newptr[i] = char_ptr[i];
	}
}

/**
 * reallocate - Reallocates a memory block.
 * @p: Pointer to the previously allocated memory.
 * @size: Size of the allocated space of ptr.
 * @newsize: New size of the new memory block.
 * Return: Void ptr.
 */

void *reallocate(void *p, unsigned int size, unsigned int newsize)
{
	void *newptr;

	if (p == NULL)
		return (malloc(newsize));

	if (newsize == 0)
	{
		free(p);
		return (NULL);
	}

	if (newsize == size)
		return (p);

	newptr = malloc(newsize);

	if (newptr == NULL)
		return (NULL);

	if (newsize < size)
		memory_cpy(newptr, p, newsize);
	else
		memory_cpy(newptr, p, size);

	free(p);

	return (newptr);
}

/**
 * realloc_dptr - Reallocates a memory block of a double pointer.
 * @p: Double pointer to the previously allocated memory.
 * @size: Size of the allocated space of ptr.
 * @newsize: New size of the new memory block.
 * Return: Ptr.
 */

char **realloc_dptr(char **p, unsigned int size, unsigned int newsize)
{
	char **newptr;
	unsigned int i;

	if (p == NULL)
		return (malloc(sizeof(char *) * newsize));

	if (newsize == size)
		return (p);

	newptr = malloc(sizeof(char *) * newsize);

	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		newptr[i] = p[i];

	free(p);

	return (newptr);
}
