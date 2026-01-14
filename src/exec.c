#include "../include/nanoshell.h"

/*
 * exec_find_in_path: Search for an executable in PATH
 * Returns: allocated string with full path, or NULL if not found
 * The caller must free the returned string
 */
char *exec_find_in_path(const char *cmd)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char full_path[MAX_LINE_LENGTH];
	struct stat st;

	if (!cmd)
		return (NULL);

	/* TODO: Implement PATH search using strtok on PATH environment variable */
	/* TODO: For each directory in PATH, construct full_path = dir + "/" + cmd */
	/* TODO: Check if full_path is executable using stat() or access() */
	/* TODO: Return first match found, or NULL if none found */

	return (NULL);
}

/*
 * exec_execute: Execute a command via fork/execve/waitpid
 * Handles both relative/absolute paths and PATH search
 */
void exec_execute(const char *cmd, char **argv)
{
	pid_t pid;
	int status;
	char *full_path;

	if (!cmd)
		return;

	/* TODO: If cmd contains '/', use it as-is (relative or absolute path) */
	/* TODO: Otherwise, search in PATH using exec_find_in_path() */
	/* TODO: If not found, print "nanoshell: weird, <cmd> is not here... :/" */
	/* TODO: Fork a child process */
	/* TODO: In child: execve(full_path, argv, environ) */
	/* TODO: In parent: waitpid() for child completion */
	/* TODO: Free allocated memory (full_path if needed) */
}
