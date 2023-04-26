#include "shell.h"
char *fileName;
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
	signal(SIGINT, sigint_handler);

	fileName = args[0];

	if (args[1])
	{
		ex_filecmd(args[1]);
		return (0);
	}
	
	signal(SIGINT, sigint_handler);
	fileName = args[0];

	if (args[1])
	{
		ex_filecmd(args[1]);
		return (0);
	}

	/* Disable Ctrl-C terminal interrupt for interactive shell only */
	if (isatty(STDIN_FILENO) && argc > 1 && strcmp(args[1], "-n") == 0)
		system("stty -echoctl");

	if (isatty(STDIN_FILENO))
		return (read_lines_interactive());

	else
		return (read_lines_non_interactive());
	
	return (0);
}

/**
 * sigint_handler - handler for the SIGINT signal
 * @sig: signal number
 */
void sigint_handler(int sig)
{
	(void) sig;
	printf("\n%s$ ", get_current_dir());
	fflush(stdout);
}

/**
 * read_lines_interactive - Logic for reading user input in interactive mode.
 *
 * Return: 0 on Success,  127 on Error.
 */
int read_lines_interactive(void)
{
	char *buffer;
	size_t bufsize = 1024;
	int chars_read = 0;
	
	system("./logo/logo");		/* Executes the Holberton logo executable */

	buffer = (char *) malloc(bufsize * sizeof(char));
	if (!buffer)
	{
		_perror(mem, strerror(errno));
		exit(1);
	}

	while (1)
	{
		printf("%s$ ", get_current_dir());
		chars_read = getline(&buffer, &bufsize, stdin);

		if (chars_read == -1)
		{
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
		if (call_command(buffer) == 127)	/* execve failed to execute the command */
		{
			last_status = 127;
			continue; /* Keep the previous value of last_status */
		}
		last_status = 0; /* Command was executed successfully */
	}
	free(buffer);
	return (last_status);
}

/**
 * read_lines_non_interactive - Reading user input in non-interactive mode.
 *
 * Return: 1 on Success, 127 on Error.
*/
int read_lines_non_interactive(void)
{
	char *buffer;
	size_t bufsize = 1024;
	int chars_read = 0;
	int status, last_status = 0;

	buffer = (char *) malloc(bufsize * sizeof(char));
	if (!buffer)
	{
		_perror(mem, strerror(errno));
		exit(1);
	}

	while ((chars_read = getline(&buffer, &bufsize, stdin)) != -1)
	{
		buffer[chars_read - 1] = '\0';
		if (call_command(buffer) == 127)	/* execve failed to execute the command */
			status = 127;
		else
			status = 0;						/* Command was executed successfully */
		last_status = status;
	}

	free(buffer);
	return (last_status);
}
