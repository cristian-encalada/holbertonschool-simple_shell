#include "shell.h"

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