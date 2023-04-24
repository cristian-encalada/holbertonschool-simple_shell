#include "shell.h"

/**
 * cd_cmd - Changes the current directory of the process.
 * 
 * Return: void.
*/
void cd_cmd(char **args)
{
	char *home_dir = getenv("HOME"), *current_dir, *cmd;

	current_dir = get_current_dir();
	if (!current_dir)
	{
		_perror(custom, "Error: could not get current directory\n");
		return;
	}

	if (!home_dir)
	{
		_perror(custom, "Error: HOME environment variable not set\n");
		return;
	}

	if (!args[1])
	{
		if (chdir(home_dir) != 0)
		{
			_perror(custom, "Error: could not change directory to %s\n", home_dir);
			return;
		}
	}
	else
	{
	/* If the argument is "-", change to the previous directory */
		if (strcmp(args[1], "-") == 0)
		{
			if (!prevDir)
			{
				_perror(custom, "Error: no previous directory\n");
				return;
			}

			if (chdir(prevDir) != 0)
			{
				_perror(custom, "Error: could not change directory to %s\n", prevDir);
				return;
			}
		}
		/* The argument is a directory */
		else
		{
			if (chdir(args[1]) != 0)
			{
				_perror(custom, "Error: could not change directory to %s\n", args[1]);
				return;
			}
			
			prevDir = strdup(current_dir);
			if (!prevDir)
			{
				_perror(custom, "Error: could not save previous directory\n");
				return;
			}
		}
	}

	cmd = malloc(sizeof(char) * (strlen(current_dir) + 16));
	if (!cmd)
	{
		_perror(mem, strerror(errno));
		return;
	}

	sprintf(cmd, "setenv PWD %s", current_dir);
	call_command(cmd);
}