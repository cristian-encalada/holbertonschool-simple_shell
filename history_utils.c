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

void addCmdHistory(char *cmd)
{
	unsigned int len = 0;
	char *cmd_copy;
	char **new_content = NULL;

	if (!cmd || !history)
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

	new_content = calloc(len + 2, sizeof(char *));

	if (!new_content)
	{
		_perror(mem, "Couldn't allocate mem for the new cmd.");
		return;
	}

	memcpy(new_content, history, len * sizeof(char *));
	new_content[len] = malloc(sizeof(char) * strlen(cmd_copy) + 1);

	if (!new_content[len])
	{
		_perror(mem, "Couldn't allocate mem for the new cmd.");
		free(new_content);
		return;
	}

	strcpy(new_content[len], cmd_copy);
	free(history);
	history = new_content;
	free(cmd_copy);
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

	if (history == NULL)
		return (-1);
	
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
 * Return: void.
*/
void loadHistory()
{
	char line[1024];
	char **content = NULL;
	char **new_content = NULL;
	size_t content_size = 0, line_len;
	FILE *fp = fopen(".simple_shell_history", "r");

	if (!fp)
	{
		_perror(custom, "Error: Could not access history file");
		return;
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
		
		new_content = calloc(content_size + 2, sizeof(char *));
		if (!new_content)
		{
			_perror(mem, "Error: Could not allocate memory");
			fclose(fp);
			free_array(content); 
			return;
		}
		memcpy(new_content, content, sizeof(char *) * content_size);
		free(content);
		content = new_content;

		content[content_size] = malloc((line_len + 1) * sizeof(char));
		if (!content[content_size])
		{
			free(content);
			_perror(mem, "Error: Could not allocate memory");
			fclose(fp);
			return;
		}
		
		strcpy(content[content_size], line);
		content_size++;
	}
	
	if (ferror(fp))
	{
		_perror(custom, "Error: Could not read history file");
		fclose(fp);
		free_array(content);
		return;
	}

	if (content == NULL)
		content = malloc(sizeof(char*) * 1);

	if (content == NULL)
	{
		_perror(mem, "Error: Could not allocate memory");
		free_array(content);
		return;
	}
	
	fclose(fp);
	
	history = content;
}