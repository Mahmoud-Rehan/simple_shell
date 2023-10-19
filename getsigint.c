#include "main.h"

/**
 * _getsigint - Handle the crtl + c call in prompt.
 * @signal: Signal handler.
 */

void _getsigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
