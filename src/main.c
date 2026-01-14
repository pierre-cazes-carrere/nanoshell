#include "../include/nanoshell.h"

/*
 * main: Main loop of the nanoshell
 * Displays prompt, reads command, parses it, and executes (builtin or external)
 */
int main(void)
{
	char *line;
	t_command *cmd;
	int should_exit;

	should_exit = 0;

	while (!should_exit)
	{
		/* Display prompt and read line */
		prompt_display();
		line = prompt_read_line();

		/* Handle EOF (Ctrl-D) */
		if (!line)
		{
			printf("\n");
			break;
		}

		/* Parse the line */
		cmd = parser_parse_line(line);
		if (!cmd)
		{
			free(line);
			continue;
		}

		/* Skip empty commands */
		if (!cmd->cmd || strlen(cmd->cmd) == 0)
		{
			parser_free_command(cmd);
			free(line);
			continue;
		}

		/* Check if builtin */
		if (builtins_is_builtin(cmd->cmd))
		{
			int result = builtins_run(cmd->cmd, cmd->argv);
			if (result == 2)
				should_exit = 1;
		}
		else
		{
			/* Execute as external command */
			exec_execute(cmd->cmd, cmd->argv);
		}

		/* Cleanup */
		parser_free_command(cmd);
		free(line);
	}

	return (0);
}
