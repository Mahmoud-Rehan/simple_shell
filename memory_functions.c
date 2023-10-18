#include "main.h"

/**
 * memory_cpy - Copies information between void pointers.
 * @newptr: Dest pointer.
 * @ptr: Src pointer.
 * @size: Size of the new pointer.
 */

void memory_cpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
	{
		char_newptr[i] = char_ptr[i];
	}
}

/**
 * reallocate - Reallocates a memory block.
 * @ptr: Pointer to the previously allocated memory.
 * @old_size: Size of the allocated space of ptr.
 * @new_size: New size of the new memory block.
 * Return: Void ptr.
 */

void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);

	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		memory_cpy(newptr, ptr, new_size);
	else
		memory_cpy(newptr, ptr, old_size);

	free(ptr);

	return (newptr);
}

/**
 * realloc_dptr - Reallocates a memory block of a double pointer.
 * @ptr: Double pointer to the previously allocated memory.
 * @old_size: Size of the allocated space of ptr.
 * @new_size: New size of the new memory block.
 * Return: Ptr.
 */

char **realloc_dptr(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);

	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
