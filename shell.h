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
	void (*f)(char **args);
} command_t;

char *buffer;

/* custom_commands */
void exit_cmd(char **args);
void env_cmd(char **args);
void clear_cmd(char **args);

/* main.c */
int read_lines_interactive();
int read_lines_non_interactive();
/* command_manager.c */
void call_command(char *command);
int ex_builtin(char *command, char **args);
int ex_path(char **argv);

/* string_utils.c */
char **split_str(char *str);
int str_count_words(char *s, const char *delim);
void free_array(char **arr);

int _getline(char *s, int lim);

#endif