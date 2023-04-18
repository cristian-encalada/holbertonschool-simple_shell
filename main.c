#include "shell.h"

int str_count_words(char *s, const char *delim){
  char *tok;
  int numWords;
  tok = strtok(strdup(s), delim);         /* Get first token */

  while (tok != NULL)               /* Check for delimiters */
  {
    numWords++;
    tok = strtok(NULL, delim);    /* Go through other tokens */
  }
  return (numWords);
}

/**
 * split_str - Splits a string.
 * @s: String to be splitted.
 *
 * Return: Void
*/
char **split_str(char *str)
{
  const char *delim = " ";         /* Delimiter */
  char *tok;
  char **array;
  unsigned int len = 0, numWords = str_count_words(str, delim), count = 0, i = 0;

  array = (char **) malloc((numWords + 1) * sizeof(char *));

  if (array == NULL)
    return (NULL);
  
  tok = strtok(str, delim);

  while (tok != NULL)
  {
    for (len = 0; tok[len]; len++)
      ;

    array[count] = (char *) malloc((len + 1) * sizeof(char));
    if (array[count] == NULL)
      return (NULL);

    for (i = 0; i < len; i++)
    {
      array[count][i] = tok[i];
    }
    
    array[count][i] = '\0';

    count++;
    tok = strtok(NULL, delim);
  }

  array[count] = NULL;
  return (array);
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
  int status;
  pid = fork();

  if (pid == -1)
    perror("Error");
  else if (pid == 0)
  {
    if (execve(argv[0], argv, NULL) == -1)
      perror("Error");
  }
  else
    waitpid(pid, &status, 0);
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