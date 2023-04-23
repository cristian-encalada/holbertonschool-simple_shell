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
	if (isatty(STDIN_FILENO) && argc > 1 && strcmp(argv[1], "-n") == 0)
		system("stty -echoctl");

	if (isatty(STDIN_FILENO))   /* Run in interactive mode */
		
		read_lines_interactive();
	else                        /* Run in non-interactive mode */

		read_lines_non_interactive();

	return (0);
}

/**
 * read_lines_interactive - Logic for reading user input in interactive mode.
 * 
 * Return: 1 on Success.
*/
int read_lines_interactive()
{
    char *buffer;
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

        if (chars_read == -1)
        {
            break; /* End of input stream reached */
        }

        if (chars_read == 1 && buffer[0] == '\n')
            continue; /* Empty input string, read the next line */

        if (strcmp(buffer, "exit\n") == 0)
        {
            break; /* User entered the "exit" command */
        }

        if (buffer[chars_read - 1] != '\n'){
            printf("\n");
            continue; /* Input did not end with a newline character, read the next line */
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
    char *buffer;
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
            continue; /* Input did not end with a newline character, read the next line */
        }

        buffer[chars_read - 1] = '\0';
        call_command(buffer);
    }

    free(buffer);
    return (0);
}