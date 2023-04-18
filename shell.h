#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct command{
  char *cmd;
  void (*f)();
} command_t;

/* custom_commands */
void exit_cmd();
void env_cmd();

/* main.c */
int read_lines();

/* command_manager.c */
void call_command(char *command);
int ex_builtin(char *command);
int ex_path(char **argv);

/* string_utils.c */
char **split_str(char *str);
int str_count_words(char *s, const char *delim);

#endif