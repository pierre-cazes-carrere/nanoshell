#include "../include/nanoshell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

extern char **environ;

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
 * builtin_pwd: Print current working directory
 */
static int builtin_pwd(void)
{
    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return (0);
    }
    else
    {
        perror("pwd");
        return (-1);
    }
}

/*
 * builtin_env: Print all environment variables
 */
static int builtin_env(void)
{
    for (char **env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);
    }
    return (0);
}

/*
 * builtin_cd: Change directory
 * Handles: cd, cd ~, cd .., cd somedir
 */
static int builtin_cd(char **argv)
{
    const char *path;
    char *home;
    
    /* cd with no args or 'cd ~' -> go to HOME */
    if (argv[1] == NULL || strcmp(argv[1], "~") == 0)
    {
        home = getenv("HOME");
        if (!home)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return (-1);
        }
        path = home;
    }
    /* cd .. -> go to parent directory */
    else if (strcmp(argv[1], "..") == 0)
    {
        path = "..";
    }
    /* cd somedir -> go to specified directory */
    else
    {
        path = argv[1];
    }
    
    if (chdir(path) != 0)
    {
        perror("cd");
        return (-1);
    }
    
    return (0);
}

/*
 * builtin_exit: Exit the shell
 * Can parse optional exit code from argv[1]
 */
static int builtin_exit(char **argv)
{
    int exit_code = 0;
    
    /* Parse optional exit code */
    if (argv[1] != NULL)
    {
        exit_code = atoi(argv[1]);
    }
    
    /* Return 2 to signal the shell should exit */
    (void)exit_code;
    return (2);
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
        return builtin_cd(argv);
    }
    
    if (strcmp(cmd, "pwd") == 0)
    {
        return builtin_pwd();
    }
    
    if (strcmp(cmd, "env") == 0)
    {
        return builtin_env();
    }
    
    if (strcmp(cmd, "exit") == 0)
    {
        return builtin_exit(argv);
    }
    
    return (-1);
}
