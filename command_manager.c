#include "shell.h"
char **commands = NULL;

/**
 * ex_filecmd - Executes all the commands in a file.
 *
 * @file: File to read from.
 * @fileName: Executable file.
 *
 * Return: Exit status. 0 on Success, 127 on Error.
*/
int ex_filecmd(char *file, char *fileName)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(file, "r");		/* read-only mode */

	if (!fp)
	{
		_perror(custom, "%s: 0: Can't open %s\n", fileName, file);
		return (127);
	}

	while ((read = getline(&line, &len, fp)) != -1)
	{
		call_command(line, fileName);
	}

	if (fclose(fp) != 0)
	{
		_perror(custom, "Error closing file.\n");
		return (127);
	}

	return (0);
}

/**
 * ex_path - Executes a command in the PATH.
 *
 * @argv: Command name and arguments.
 * Return: 1 on Success, -1 on Error.
 */
int ex_path(char **argv)
{
	char *env = _getenv("PATH");
	char *path;
	char *path_copy, *dir, *full_path;
	int len_dir, len_cmd, result;

	if (!env)
		return (-1);

	path = strdup(env);
	path_copy = path;

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
				free_array(argv);
				return (-1);
			}
			else if (pid == 0)
			{
				execve(full_path, argv, environ);
				perror("execve");
				free_array(argv);
				_exit(127);
			}
			else
			{
				waitpid(pid, NULL, 0);
				free(full_path);
				free(path);

				free_array(argv);
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
 * @command: Command name.
 * @args: Input arguments.
 *
 * Return: 1 on Success, -1 on Error.
*/
int ex_builtin(char *command, char **args)
{
	command_t commands[] = {
		{"exit", exit_cmd},
		{"env", env_cmd},
		{"clear", clear_cmd},
		{"setenv", setenv_cmd},
		{"unsetenv", unsetenv_cmd},
		{"cd", cd_cmd},
		{"alias", alias_cmd},
		{"help", help_cmd},
		{"history", history_cmd},
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
 * @command: String containing the command name.
 * @fileName: The name of the shell executable file.
 * Return: 0 on Success, 127 on Error.
*/
int call_command(char *command, char *fileName)
{
	char *clean_command = remove_comment(command);
	int i = 0, status = 0, j = 0, ret = -1, prev_cmd_failed = 0;
	pid_t pid;
	char **argv;

	commands = split_str(clean_command, ";&|");

	if (commands == NULL)
	{
		free(command);
		return (status);
	}

	addCmdHistory(command);
	free(command);

	while (commands[i] != NULL)
	{
		argv = split_str(commands[i], " \t\n\r");

		if (commands[i][0] == '#')  /* Ignore commands that start with "#" */
		{
			i++;
			free_array(argv);
			continue;
		}
		if (argv == NULL)
		{
			free(clean_command);
			free_array(commands);
			return (127);
		}

		/* Handle variable replacement */
		for (j = 1; argv[j] != NULL; j++)
		{
			char *var = argv[j];

			if (var[0] == '$')
			{
				char *val;

				if (strcmp(var, "$$") == 0)
				{
					val = malloc(10);       /* allocate space for pid */
					sprintf(val, "%d", getpid());
				}
				else if (strcmp(var, "$?") == 0)
				{
					val = malloc(10);       /* allocate space for exit status */
					sprintf(val, "%d", last_status);
				}
				else
					val = getenv(var + 1);
				if (val != NULL)
				{
					free(argv[j]);         /* free the old argv[j] */
					argv[j] = val;
				}
				else
					free(val);              /* free the unused val */
			}
		}
		/* Check if the cmd is built-in */
		if (ex_builtin(argv[0], argv) == 1)
		{
			free_array(argv);
			i++;
			continue;
		}
		/* Check if the cmd is in PATH*/
		if (ex_path(argv) == 1)
		{
			i++;
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free_array(argv);
			free_array(commands);
			free(clean_command);
			saveHistory();
			exit(EXIT_FAILURE); /* terminates the child process if execve fails */
		}
		else if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", fileName, argv[0]);
				free_array(commands);
				free_array(argv);
				saveHistory();
				exit(127);
			}
		}
		else
		{	/* parent process */
			waitpid(pid, &status, 0);
			if (WIFEXITED(status)) /* Check if the child process exited normally */
			{
				status = WEXITSTATUS(status); /* Get the status of the child process */
				if (i == 0)						/* Check if it's the first command */
				{
					if (status == 0)	/* If the first command succeeds, don't update ret */
						ret = 0;
					else	/* If first command fails, update ret to the exit status of the failed command */
						ret = status;
				}
				else if (i > 0 && (commands[i - 1][0] == '|' || commands[i - 1][0] == '&' || commands[i - 1][0] == ';'))
				{
					/* Check if the previous operator is pipe or ampersand and the exit status of the previous command is non-zero */
					if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
						prev_cmd_failed = 1;
					else
						prev_cmd_failed = 0;
				}
				else if (strcmp(commands[i - 1], "||") == 0 && prev_cmd_failed)
				{	/* if previous operator was "||", the first command succeeded, and the current command failed */
					/* so, execute the next command */
					ret = status;
					prev_cmd_failed = 0;
				}
				else if (i == 0 || (ret != 0 && (commands[i - 1][0] == '|' || commands[i - 1][0] == '&' || commands[i - 1][0] == ';')))
				/* Check if previous operator is | or & and the status of the first command is non-zero */
				{
					free_array(argv);
					i++;
					continue; /* Skip executing the current command */
				}
			}
		}
		free_array(argv);
		i++;
	}
	free_array(commands);
	return (ret);		/* Return the exit status of the first command */
}

void free_commands(void)
{
	if (commands)
		free_array(commands);
}
