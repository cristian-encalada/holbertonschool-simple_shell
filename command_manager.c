#include "shell.h"

/**
 * ex_path - Executes a command in the PATH.
 *
 * @argv: Command name and arguments.
 * Return: 1 on Success, -1 on Error.
*/
int ex_path(char **argv)
{
	char *path = strdup(getenv("PATH"));
	char *path_copy = path;
	char *dir, *full_path;
	int len_dir, len_cmd, result;

	if (!path || !*argv)
		return (-1);

	len_cmd = strlen(*argv);

	while ((dir = strtok(path_copy, ":")))
	{
		len_dir = strlen(dir);
		full_path = malloc(len_dir + len_cmd + 2);

		if (!full_path)
			return (-1);

		sprintf(full_path, "%s/%s", dir, *argv);

		result = access(full_path, X_OK);

		if (result == 0)
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("fork");
				free(full_path);
				return (-1);
			}
			else if (pid == 0)
			{
				execve(full_path, argv, NULL);
				_exit(127);
			}
			else
			{
				waitpid(pid, NULL, 0);
				free(full_path);
				free(path);
				return (1);
			}
		}

		free(full_path);
		path_copy = NULL;
	}

	free(path);
	return (-1);
}



/**
 * ex_builtin - Executes a built-in command
 * 
 * @command: Command name.
 * Return: 1 on Success, -1 on Error.
*/
int ex_builtin(char *command, char **args)
{
	command_t commands[] = {
		{"exit", exit_cmd},
		{"env", env_cmd},
		{"clear", clear_cmd},
		{NULL, NULL}
	};
	unsigned int i = 0;

	while (commands[i].cmd != NULL)
	{
		if (strcmp(command, commands[i].cmd) == 0)
		{
			commands[i].f(args);
			return (1);
		}
			
		i++;
	}
	return (-1);
}

/**
 * call_command - Call an executable
 * 
 * @command: String containing the command name.
 * Return: void
*/
void call_command(char *command)
{
	char **argv = split_str(command);
	pid_t pid;

	/* Check if the cmd is built-in */
	if (ex_builtin(argv[0], argv) == 1)
	{
		free_array(argv);
		return;
	}

	/* Check if the cmd is in PATH*/
	if (ex_path(argv) == 1)
	{
		free_array(argv);
		return;
	}
		
	pid = fork();

	if (pid == -1)
		perror("Error");
	else if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
			free(command);
			_exit(127);
		}
			
	}
	else
		waitpid(pid, NULL, 0);
	
	free_array(argv);
}