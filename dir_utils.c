#include "shell.h"
char *prevDir;

/**
 * get_current_dir - Get the current working directory.
 *
 * Return: The current working directory.
*/
char *get_current_dir(void)
{
	char *current_dir = getcwd(NULL, 0);

	if (!current_dir)
		return (NULL);

	return (current_dir);
}
