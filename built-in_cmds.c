#include "shell.h"

/**
 * exit_cmd - Exit the shell.
 * 
 * Return: void.
*/
void exit_cmd(){
  exit(0);
}

/**
 * env_cmd - Prints the environment.
 * 
 * Return: void.
*/
void env_cmd(){
  unsigned int i = 0;
  extern char **environ;

  for (; environ[i] != NULL; i++)
  {
    printf("%s\n", environ[i]);
  }
}
