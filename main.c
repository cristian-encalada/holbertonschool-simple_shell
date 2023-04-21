#include "shell.h"

/**
 * main - Main entry of the program.
 * 
 * @argc: amount of arguments passed.
 * @argv: an array of arguments.
 * Return: 0 on Success, -1 on Error.
*/
int main(int argc, char **argv)
{
	signal(SIGINT, SIG_IGN);

	/* Disable Ctrl-C terminal interrupt for interactive shell only */
	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		system("stty -echoctl");
	}

	if (argc == 1) {
		/* Run in interactive mode */
		read_lines_interactive();
	} else if (argc == 2 && strcmp(argv[1], "-n") == 0) {
		/* Run in non-interactive mode */
		read_lines_non_interactive();
	} else {
		/* Invalid command line arguments */
		fprintf(stderr, "Usage: %s [-n]\n", argv[0]);
		exit(1);
	}

	return (0);
}

/**
 * read_lines_interactive - Logic for reading user input in interactive mode.
 * 
 * Return: 1 on Success.
*/
int read_lines_interactive()
{
	size_t bufsize = 1024;
	int chars_read = 0;

	buffer = (char *) malloc(bufsize * sizeof(char));
	if(!buffer)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	while (1)
	{
		printf("$ ");
		chars_read = getline(&buffer, &bufsize, stdin);
		
		if (buffer[chars_read - 1] != '\n'){
			printf("\n");
			free(buffer);
			exit(1);
		}
		
		buffer[chars_read - 1] = '\0';
		call_command(buffer);
	}

	free(buffer);
	return (0);
}

/**
 * read_lines_non_interactive - Logic for reading user input in non-interactive mode.
 * 
 * Return: 1 on Success.
*/
int read_lines_non_interactive()
{
	size_t bufsize = 1024;
	int chars_read = 0;

	buffer = (char *) malloc(bufsize * sizeof(char));
	if(!buffer)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	while ((chars_read = getline(&buffer, &bufsize, stdin)) != -1)
	{
		if (buffer[chars_read - 1] != '\n'){
			printf("\n");
			free(buffer);
			exit(1);
		}
		
		buffer[chars_read - 1] = '\0';
		call_command(buffer);
	}

	free(buffer);
	return (0);
}