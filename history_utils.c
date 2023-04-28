#include "shell.h"

char **history = NULL;

/**
 * getHistory - Get the command history
 * 
 * Return: Command history or NULL if doesn't exists.
*/
char **getHistory()
{
	return (history);
}

/**
 * printHistory - Print the command history.
 * 
 * Return: void.
*/
void printHistory()
{
	unsigned int i = 0;

	if (history == NULL)
	{
		_perror(custom, "Error: Empty or not valid file.\n");
		return;
	}

	for (; history[i]; i++)
		printf("%d - %s\n", i, history[i]);
}

/**
 * addCmdHistory - Add a command to the history.
 * 
 * @cmd: Command line to be added with arguments or not.
 * Return: void
*/
void addCmdHistory(char *cmd)
{
	unsigned int len = 0;
	char *cmd_copy;

	if (cmd == NULL || history == NULL)
		return;

	cmd_copy = strdup(cmd);

	if (cmd_copy == NULL)
		return;

	for (; history[len]; len++)
		;

	if (len == 0)
	{
		history[0] = cmd_copy;
		return;
	}

	history = realloc(history, sizeof(char *) * (len + 2));

	if (!history)
	{
		_perror(mem, "Couldn't allocate mem for the new cmd.");
		return;
	}

	history[len] = malloc(sizeof(char) * strlen(cmd_copy) + 1);

	if (!history[len])
	{
		_perror(mem, "Couldn't allocate mem for the new cmd.");
		return;
	}

	strcpy(history[len], cmd_copy);
}

/**
 * saveHistory - Save the command history in a file.
 * 
 * Return: 0 on Success, -1 on Error.
*/
int saveHistory()
{
	unsigned int i = 0;
	FILE *fp = fopen(".simple_shell_history", "w");

	if (!fp)
	{
		_perror(custom, "Error: Could not access history file.\n");
		return (-1);
	}
	
	for (; history[i]; i++)
	{
		fputs(history[i], fp);
		fputc('\n', fp);
	}
	
	fclose(fp);
	free_array(history);
	return (0);
}

/**
 * loadHistory - Loads the command history from the file to the variable.
 * 
 * Return: An array of commands or NULL on Error.
*/
char **loadHistory()
{
	char line[1024];
	char **content = NULL;
	char **new_content = NULL;
	size_t content_size = 0, line_len;
	FILE *fp = fopen(".simple_shell_history", "r");

	if (!fp)
	{
		_perror(custom, "Error: Could not access history file");
		return (NULL);
	}

	while (fgets(line, sizeof(line), fp))
	{
		line_len = strlen(line);
		if (line_len > 0 && line[line_len - 1] == '\n')
		{
			line[line_len - 1] = '\0';
			line_len--;
		}

		if (line_len == 0)
		{
			continue;
		}
		
		new_content = realloc(content, sizeof(char *) * (content_size + 2));
		if (!new_content)
		{
			_perror(mem, "Error: Could not allocate memory");
			return (NULL);
		}
		content = new_content;
		content[content_size] = malloc((line_len + 1) * sizeof(char));
		if (!content[content_size])
		{
			free(content);
			_perror(mem, "Error: Could not allocate memory");
			return (NULL);
		}
		
		strcpy(content[content_size], line);
		content_size++;
	}
	
	if (ferror(fp))
	{
		_perror(custom, "Error: Could not read history file");
		fclose(fp);
		return (NULL);
	}

	if (content == NULL)
		content = malloc(sizeof(char*) * 1);
	
	if (content == NULL)
	{
		_perror(mem, "Error: Could not allocate memory");
		return (NULL);
	}
	
	fclose(fp);
	history = content;
	return (content);
}