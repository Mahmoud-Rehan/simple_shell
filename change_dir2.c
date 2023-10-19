#include "main.h"

/**
 * cd_current - Cd to the current directory.
 * @data: Data.
 * Return: 1 if success.
 */

int cd_current(shell_data *data)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = data->arguments[1];

	if (dir != NULL)
	{
		ishome = string_cmp("$HOME", dir);
		ishome2 = string_cmp("~", dir);
		isddash = string_cmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home(data);
		return (1);
	}

	if (string_cmp("-", dir) == 0)
	{
		cd_prev(data);
		return (1);
	}

	if (string_cmp(".", dir) == 0 || string_cmp("..", dir) == 0)
	{
		cd_parent(data);
		return (1);
	}

	change_dir(data);

	return (1);
}
