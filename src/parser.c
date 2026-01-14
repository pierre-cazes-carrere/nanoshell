#include "../include/nanoshell.h"

/*
 * is_whitespace: Check if character is whitespace
 */
static int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/*
 * trim_line: Remove leading/trailing whitespace and return trimmed string
 */
static char *trim_line(const char *line)
{
	int start;
	int end;
	char *trimmed;
	int len;

	if (!line)
		return (NULL);

	/* Find first non-whitespace character */
	start = 0;
	while (line[start] && is_whitespace(line[start]))
		start++;

	/* Find last non-whitespace character */
	end = strlen(line) - 1;
	while (end >= start && is_whitespace(line[end]))
		end--;

	/* Allocate and copy trimmed string */
	len = end - start + 1;
	if (len <= 0)
		return (calloc(1, 1)); /* Return empty string */

	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);

	strncpy(trimmed, line + start, len);
	trimmed[len] = '\0';

	return (trimmed);
}

/*
 * parser_parse_line: Parse a line into command and arguments
 * Returns: allocated t_command struct, or NULL on error
 * The caller must free the result using parser_free_command
 */
t_command *parser_parse_line(const char *line)
{
	t_command *cmd;
	char *trimmed;
	char *copy;
	char *token;
	int i;

	if (!line)
		return (NULL);

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);

	cmd->argv = malloc(sizeof(char *) * MAX_ARGS);
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}

	trimmed = trim_line(line);
	if (!trimmed)
	{
		free(cmd->argv);
		free(cmd);
		return (NULL);
	}

	/* If empty line, return empty command */
	if (strlen(trimmed) == 0)
	{
		cmd->cmd = NULL;
		cmd->argc = 0;
		free(trimmed);
		return (cmd);
	}

	/* Make a copy for strtok */
	copy = malloc(strlen(trimmed) + 1);
	if (!copy)
	{
		free(cmd->argv);
		free(cmd);
		free(trimmed);
		return (NULL);
	}
	strcpy(copy, trimmed);

	/* Split by spaces */
	i = 0;
	token = strtok(copy, " \t");
	while (token && i < MAX_ARGS - 1)
	{
		cmd->argv[i] = malloc(strlen(token) + 1);
		if (!cmd->argv[i])
		{
			/* TODO: Handle allocation error and cleanup */
			break;
		}
		strcpy(cmd->argv[i], token);
		i++;
		token = strtok(NULL, " \t");
	}
	cmd->argv[i] = NULL;
	cmd->cmd = cmd->argv[0];
	cmd->argc = i;

	free(copy);
	free(trimmed);

	return (cmd);
}

/*
 * parser_free_command: Free a command structure
 */
void parser_free_command(t_command *cmd)
{
	int i;

	if (!cmd)
		return;

	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	free(cmd);
}
