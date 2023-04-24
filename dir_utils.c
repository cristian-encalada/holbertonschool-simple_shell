#include "shell.h"
char *prevDir;
char *get_current_dir()
{
	char *current_dir = getcwd(NULL, 0);

	if (!current_dir)
		return (NULL);

	return (current_dir);
}