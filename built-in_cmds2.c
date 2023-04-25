#include "shell.h"
/**
 * cd_cmd - Changes the current directory of the process.
 * @args: Input arguments.
 * Return: void.
*/
void cd_cmd(char **args)
{
	char *home_dir = getenv("HOME"), *current_dir, *cmd;

	current_dir = get_current_dir();
	if (!current_dir)
	{	_perror(custom, "Error: could not get current directory\n");
		return;
	}
	if (!home_dir)
	{	_perror(custom, "Error: HOME environment variable not set\n");
		return;
	}
	if (!args[1])
	{
		if (chdir(home_dir) != 0)
		{	_perror(custom, "Error: could not change directory to %s\n", home_dir);
			return;
		}
	}
	else
	{	/* If the argument is "-", change to the previous directory */
		if (strcmp(args[1], "-") == 0)
		{
			if (!prevDir)
			{	_perror(custom, "Error: no previous directory\n");
				return;
			}
			if (chdir(prevDir) != 0)
			{	_perror(custom, "Error: could not change directory to %s\n", prevDir);
				return;
			}
		}
		else	/* The argument is a directory */
		{
			if (chdir(args[1]) != 0)
			{	_perror(custom, "Error: could not change directory to %s\n", args[1]);
				return;
			}
			prevDir = strdup(current_dir);
			if (!prevDir)
			{	_perror(custom, "Error: could not save previous directory\n");
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

/**
 * alias_cmd - Define an alias or list them.
 *
 * @args: List of arguments passed to the function.
 * Return: void.
 */
void alias_cmd(char **args)
{
	char *name, *value;
	unsigned int i;

	if (!args[1])
	{
		/* Print all aliases */
		print_aliases();
		putchar('\n');
		return;
	}

	/* Parse arguments */
	for (i = 1; args[i]; i++)
	{
		if (strchr(args[i], '='))
		{
			/* Define an alias */
			name = strtok(args[i], "=");
			value = strtok(NULL, "=");

			if (set_alias(name, value) != 0)
				_perror(custom, "Error: Could not define alias.\n");
		}
		else
		{
			/* Print an alias */
			print_alias(args[i], name, value);
		}
	}
}

/**
 * help_cmd - Define an alias or list them.
 *
 * @args: List of arguments passed to the function.
 * Return: void.
 */
void help_cmd(char **args)
{
	FILE *fp;
	char *file, *extension = ".help";
	char line[1024];

	if (!args[1])
	{
		_perror(cmd, "help (built-in)");
		return;
	}

	file = malloc(strlen(args[1]) + strlen(extension) + 1);
	if (!file)
	{
		_perror(mem, strerror(errno));
		return;
	}
	file[0] = '\0'; /* set first byte to zero */
	strcat(file, args[1]);
	strcat(file, extension);

	printf("Opening file: %s\n", file);
	fp = fopen(file, "r");

	if (!fp)
	{
		_perror(custom, "Error: Unknown command or no help was found.\n");
		return;
	}

	while (fgets(line, 1024, fp))
	{
		printf("%s", line);
	}

	fclose(fp);
}
