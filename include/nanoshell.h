#ifndef NANOSHELL_H
#define NANOSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/* Maximum length for a command line */
#define MAX_LINE_LENGTH 1024

/* Maximum number of arguments */
#define MAX_ARGS 128

/* Maximum length for a single argument */
#define MAX_ARG_LENGTH 256

/* Struct to represent a parsed command */
typedef struct {
	char *cmd;
	char **argv;
	int argc;
} t_command;

/* ===== prompt.h ===== */
char *prompt_read_line(void);
void prompt_display(void);

/* ===== parser.h ===== */
t_command *parser_parse_line(const char *line);
void parser_free_command(t_command *cmd);

/* ===== exec.h ===== */
char *exec_find_in_path(const char *cmd);
void exec_execute(const char *cmd, char **argv);

/* ===== builtins.h ===== */
int builtins_is_builtin(const char *cmd);
int builtins_run(const char *cmd, char **argv);

#endif /* NANOSHELL_H */
