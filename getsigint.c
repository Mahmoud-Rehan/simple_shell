#include "main.h"

/**
 * _getsigint - Handle the crtl + c call in prompt.
 * @sig: Signal handler.
 */

void _getsigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
