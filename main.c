#include "shell.h"
int last_status;
/**
 * main - Main entry of the program.
 * @argc: amount of arguments passed.
 * @argv: an array of arguments.
 *
 * Return: 0 on Success, -1 on Error.
*/
int main(int argc, char **args)
{
	int interactive = 1;
	char *fileName = args[0];

	signal(SIGINT, sigint_handler);

	if (args[1])
	{
		ex_filecmd(args[1], fileName);
		return (0);
	}
	
	signal(SIGINT, sigint_handler);

	if (args[1])
	{
		ex_filecmd(args[1], fileName);
		return (0);
	}

	/* Disable Ctrl-C terminal interrupt for interactive shell only */
	if (isatty(STDIN_FILENO) && argc > 1 && strcmp(args[1], "-n") == 0)
		system("stty -echoctl");

	if (isatty(STDIN_FILENO))
		system("./logo/logo");		/* Executes the Holberton logo executable */
	else
		interactive = 0;
	
	return (read_lines(interactive, fileName));
}

/**
 * sigint_handler - handler for the SIGINT signal
 * @sig: signal number
 */
void sigint_handler(int sig)
{
	char *dir = get_current_dir();
	(void) sig;
	printf("\n%s$ ", dir);
	free_current_dir(dir);
	fflush(stdout);
}

/**
 * read_lines - Logic for reading user input.
 * 
 * Return: 0 on Success, 127 on Error.
*/
int read_lines(int interactive, char *fileName)
{
	char *buffer;
	size_t bufsize = 1024;
	int chars_read = 0;

	buffer = (char *) malloc(bufsize * sizeof(char));
	if (!buffer)
	{
		_perror(mem, strerror(errno));
		exit(1);
	}

	while (1)
	{
		if (interactive)
		{
			char *dir = get_current_dir();
			printf("%s$ ", dir);
			free_current_dir(dir);
		}
		
		chars_read = getline(&buffer, &bufsize, stdin);

		if (chars_read == EOF)
		{
			if (interactive)
				printf("\n");
			break; /* End of input stream reached */
		}

		if (chars_read == 1 && buffer[0] == '\n')
			continue; /* Empty input string, read the next line */

		if (buffer[chars_read - 1] != '\n')
		{
			printf("\n");
			continue;						/* read the next line */
		}

		buffer[chars_read - 1] = '\0';
		if (call_command(buffer, fileName) == 127)	/* execve failed to execute the command */
		{
			last_status = 127;
			continue; /* Keep the previous value of last_status */
		}
		last_status = 0; /* Command was executed successfully */
	}
	/* Free the fileName variable */
	free(fileName);
	free(buffer);
	return (last_status);
}