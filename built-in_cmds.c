#include "shell.h"

/**
 * clear_cmd - Clear the cmd.
 * 
 * Return: void.
*/
void clear_cmd(char **args)
{
	(void) args;
	system("printf '\033[H\033[J'");
}

/**
 * exit_cmd - Exit the shell.
 * 
 * Return: void.
*/
void exit_cmd(char **args)
{
	int status = 0;

	free(buffer);

	if (args[0] != NULL)
		status = atoi(args[1]);
	exit(status);
}

/**
 * env_cmd - Prints the environment.
 * 
 * Return: void.
*/
void env_cmd(char **args)
{
	unsigned int i = 0;
	extern char **environ;

	(void) args;
	for (; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
