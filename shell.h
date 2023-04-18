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

/* main.c */
int read_lines();

/* command_manager.c */
void call_command(char *command);

/* string_utils.c */
char **split_str(char *str);
int str_count_words(char *s, const char *delim);

#endif