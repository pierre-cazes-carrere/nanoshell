#include "../include/nanoshell.h"

/*
 * prompt_display: Display the shell prompt
 */
void prompt_display(void)
{
	printf("?> ");
	fflush(stdout);
}

/*
 * prompt_read_line: Read a line from stdin
 * Returns: dynamically allocated string, or NULL on EOF
 * The caller must free the returned string
 */
char *prompt_read_line(void)
{
	char *line;
	int c;
	int i;

	line = malloc(MAX_LINE_LENGTH);
	if (!line)
	{
		perror("malloc");
		return (NULL);
	}

	i = 0;
	while (i < MAX_LINE_LENGTH - 1)
	{
		c = getchar();
		/* TODO: Handle EOF (Ctrl-D) gracefully */
		if (c == EOF)
		{
			if (i == 0)
				return (NULL);
			break;
		}
		if (c == '\n')
			break;
		line[i++] = c;
	}
	line[i] = '\0';

	return (line);
}
