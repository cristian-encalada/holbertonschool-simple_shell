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
#include <errno.h>
#include <stdarg.h>

enum errors
{
	cmd, mem, custom
};
extern char *fileName;
extern char *prevDir;
extern int last_status;

/**
 * struct command - Struct for commands
 * @cmd: Command name
 * @f: Function pointer
 */
typedef struct command
{
	char *cmd;
	void (*f)(char **args);
} command_t;

/* alias_utils.c */
int set_alias(char *name, char *value);
void print_aliases(void);
void print_alias(char *arg, char *name, char *value);

/* errors.c */
void _perror(enum errors err, char *s, ...);

/* custom_commands */
void exit_cmd(char **args);
void env_cmd(char **args);
void clear_cmd(char **args);
void setenv_cmd(char **args);
void unsetenv_cmd(char **args);
void cd_cmd(char **args);
void alias_cmd(char **args);
void help_cmd(char **args);
void history_cmd(char **args);

/* main.c */
int read_lines_interactive(void);
int read_lines_non_interactive(void);
void sigint_handler(int sig);

/* command_manager.c */
int call_command(char *command);
void ex_filecmd(char *file);
int ex_builtin(char *command, char **args);
int ex_path(char **argv);

/* string_utils.c */
char **split_str(char *str, const char *delim);
int str_count_words(char *s, const char *delim);
void free_array(char **arr);
char *remove_comment(char *str);

/* dir_utils.c */
char *get_current_dir(void);
int _getline(char *s, int lim);

#endif /* _SHELL_H_ */
