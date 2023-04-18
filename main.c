#include "shell.h"

/**
 * split_str - Splits a string.
 * 
 * @s: String to be splitted.
 * Return: An array of words.
*/
/*
char **split_str(char *s)
{
  char **splitted = malloc(sizeof(char) * strlen(s));
  unsigned int i = 0, a = 0;

  if (!splitted)
    return (NULL);

  for (; s[i]; i++)
  {
    if (s[i] == ' ')
    {
      a++;
      continue;
    }
    splitted[a][i] = s[i];
  }

  return (splitted);
}
*/
/**
 * split_str - Splits a string.
 * @s: String to be splitted.
 *
 * Return: Void
*/
void split_str(char *str)
{
  const char *delim = " ";         /* Delimiter */
  char *tok;

  tok = strtok(str, delim);         /* Get first token */

  while (tok != NULL)               /* Check for delimiters */
  {
      printf("%s\n", tok);          /* Print the word followed by a new line */
      tok = strtok(NULL, delim);    /* Go through other tokens */
  }
}


/**
 * call_command - Call an executable
 * 
 * @command: String containing the command name.
 * Return: void
*/
void call_command(char *command)
{
  char *argv[] = {"", NULL};

  if (execve(command, argv, NULL) == -1)
  {
    perror("Error");
  }
}

/**
 * read_line - Logic for reading user input.
 * 
 * Return: 1 on Success.
*/
int read_line(){
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
    
    if (buffer[chars_read - 1] != '\n'){
      printf("\n");
      exit(1);
    }

    buffer[chars_read - 1] = '\0';
    call_command(buffer);
    split_str(buffer);
  }

  free(buffer);
  return (1);
}

/**
 * main - Main entry of the program.
 * 
 * @argc: amount of arguments passed.
 * @argv: an array of arguments.
 * Return: 0 on Success, -1 on Error.
*/
int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;

  read_line();
  return (0);
}