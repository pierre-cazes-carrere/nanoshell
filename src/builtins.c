#include "../include/nanoshell.h"

/*
 * builtins_is_builtin: Check if command is a builtin
 * Returns: 1 if builtin, 0 otherwise
 */
int builtins_is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);

	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);

	return (0);
}

/*
 * builtins_run: Execute a builtin command
 * Returns: exit code, or -1 on error
 *          Special: returns 2 to signal shell should exit
 */
int builtins_run(const char *cmd, char **argv)
{
	if (!cmd)
		return (-1);

	if (strcmp(cmd, "cd") == 0)
	{
		/* TODO: Handle 'cd' builtin
		 * cd with no args or 'cd ~' -> go to HOME
		 * cd .. -> go to parent directory
		 * cd somedir -> go to somedir (relative to current dir)
		 * Use chdir() syscall
		 * Return 0 on success, -1 on failure
		 */
		return (0);
	}

	if (strcmp(cmd, "pwd") == 0)
	{
		/* TODO: Handle 'pwd' builtin
		 * Print current working directory using getcwd()
		 * Return 0
		 */
		return (0);
	}

	if (strcmp(cmd, "env") == 0)
	{
		/* TODO: Handle 'env' builtin
		 * Print all environment variables using extern char **environ
		 * Return 0
		 */
		return (0);
	}

	if (strcmp(cmd, "exit") == 0)
	{
		/* TODO: Handle 'exit' builtin
		 * Parse optional exit code from argv[1]
		 * Return 2 to signal main loop to exit
		 */
		return (2);
	}

	return (-1);
}
