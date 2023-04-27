#include "shell.h"
extern char **environ;

void ex_filecmd(char *file, char *fileName)
{
	FILE *fp;
	char line[1024];

	fp = fopen(file, "r");		/* read-only mode */

	if (!fp)
	{
		_perror(custom, "Error: File not found.\n");
		return;
	}

	while (fgets(line, 1024, fp))
	{
		call_command(line, fileName);
		putchar('\n');
	}

	fclose(fp);
}

/**
 * ex_path - Executes a command in the PATH.
 *
 * @argv: Command name and arguments.
 * Return: 1 on Success, -1 on Error.
 */
int ex_path(char **argv)
{
	char *env = getenv("PATH");
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
		{	pid_t pid = fork();

			if (pid == -1)
			{	
				perror("fork");
				free(full_path);
				return (-1);
			}
			else if (pid == 0)
			{	
				execve(full_path, argv, environ);
				perror("execve");
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
	char **commands = split_str(clean_command, ";");
	int i = 0, status = 0;
	pid_t pid;

	if (commands == NULL)
		return (status);

	while (commands[i] != NULL)
	{
		char **argv = split_str(commands[i], " \t\n\r");

		if (commands[i][0] == '#')  /* Ignore commands that start with "#" */
		{
			i++;
			continue;
		}
		if (argv == NULL)
		{
			free(clean_command);
			free_array(commands);
			return (127);
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
			free_array(argv);
			i++;
			continue;
		}
		pid = fork();
		if (pid == -1)
		{	
			perror("fork");
			free_array(argv);
			free_array(commands);
			exit(EXIT_FAILURE); /* terminates the child process if execve fails */
		}
		else if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{	
				fprintf(stderr, "%s: 1: %s: not found\n", fileName, argv[0]);
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status)) /* Check if the child process exited normally */
				status = WEXITSTATUS(status); /* Get the status of the child process */
		}
		free_array(argv);
		i++;
	}
	free_array(commands);
	return (status); /* Return the exit status */
}
