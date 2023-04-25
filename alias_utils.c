#include "shell.h"

/**
 * set_alias - sets an alias for a given name and value.
 *
 * @name: name of the alias.
 * @value: value of the alias.
 * Return: 0 on success, -1 on failure.
 */
int set_alias(char *name, char *value)
{
	char buffer[1024];
	char line[1024];
	int found = 0;
	FILE *fp = fopen(".aliases", "r");
	FILE *tmp = fopen(".aliases.tmp", "w");

	if (!fp || !tmp)
	{
		_perror(custom, "Error: Could not open aliases file.\n");
		return (-1);
	}

	snprintf(buffer, 1024, "%s='%s'", name, value);

	/* Search for an existing alias with the same name */
	while (fgets(line, 1024, fp))
	{
		if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == '=')
		{
			/* Replace existing alias */
			found = 1;
			fputs(buffer, tmp);
			fputs("\n", tmp);
		}
		else
		{
			/* Copy non-matching lines to temporary file */
			fputs(line, tmp);
		}
	}

	/* If no existing alias was found, add a new one */
	if (!found)
	{
		fputs(buffer, tmp);
		fputs("\n", tmp);
	}

	/* Close files and replace original file with temporary file */
	fclose(fp);
	fclose(tmp);
	if (rename(".aliases.tmp", ".aliases") != 0)
	{
		_perror(custom, "Error: Could not update aliases file.\n");
		return (-1);
	}

	return (0);
}

/**
 * print_aliases - prints all aliases.
 * 
 * Return: void
 */
void print_aliases()
{
	char line[1024];
	FILE *fp = fopen(".aliases", "r");

	if (!fp)
	{
		_perror(custom, "Error: Could not open aliases file.\n");
		return;
	}

	while (fgets(line, 1024, fp))
	{
		printf("%s", line);
	}

	fclose(fp);
}

void print_alias(char *arg, char *name, char *value)
{
	FILE *fp;
	ssize_t read;
	size_t len = 0;
	char *file = ".aliases", *line = NULL;

	fp = fopen(file, "r");

	if (!fp)
	{
		_perror(custom, "Error: The file cannot be read.\n");
		return;
	}

	while ((read = getline(&line, &len, fp)) != -1)
	{
		name = strtok(line, "=");

		if (strcmp(name, arg) == 0)
		{
			value = strtok(NULL, "=");
			value[strcspn(value, "\n")] = 0;
			printf("%s=%s\n", arg, value);
			break;
		}
	}

	if (read == -1)
		_perror(custom, "Error: Alias not found.\n");

	fclose(fp);
	free(line);
}

