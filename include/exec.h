#ifndef EXEC_H
#define EXEC_H

#include <sys/types.h>

char *resolve_cmd(const char *cmd, char **envp);
int execute_external(char **argv, char **envp);

#endif
