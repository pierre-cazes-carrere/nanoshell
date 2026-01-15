#include "../include/exec.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *resolve_cmd(const char *cmd, char **envp)
{
	char	*path;
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;
	size_t	cmd_len;
	size_t	dir_len;

	if (!cmd)
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	cmd_len = strlen(cmd);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + 1 + cmd_len + 1);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

int execute_external(char **argv, char **envp)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!argv || !argv[0])
		return (0);

	path = resolve_cmd(argv[0], envp);
	if (!path)
	{
		fprintf(stderr, "nanoshell: weird, %s is not here... :/\n", argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (1);
	}

	if (pid == 0)
	{
		execve(path, argv, envp);
		perror("execve");
		_exit(1);
	}

	free(path);
	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (0);
}
