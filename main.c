#include "shell.h"

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

  read_lines();
  return (0);
}

/**
 * read_lines - Logic for reading user input.
 * 
 * Return: 1 on Success.
*/
int read_lines()
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