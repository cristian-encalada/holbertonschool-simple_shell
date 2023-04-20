#include "shell.h"

/**
 * clear_cmd - Clear the cmd.
 * 
 * Return: void.
*/
void clear_cmd()
{
	system("printf '\033[H\033[J'");
}

/**
 * exit_cmd - Exit the shell.
 * 
 * Return: void.
*/
void exit_cmd()
{
	free(buffer);
	exit(0);
}

/**
 * env_cmd - Prints the environment.
 * 
 * Return: void.
*/
void env_cmd()
{
	unsigned int i = 0;
	extern char **environ;

	for (; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
