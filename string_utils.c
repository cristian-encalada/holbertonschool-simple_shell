#include "shell.h"

/**
 * split_str - Splits a string by a given delimiter.
 * @str: String to be splitted.
 * @delim: Delimiter to use for splitting.
 *
 * Return: An array of strings representing the split input.
 */
char **split_str(char *str, const char *delim)
{
	char *tok, *copy, *comment;
	char **array;
	unsigned int len = 0, count = 0, i = 0;
	int numWords = str_count_words(str, delim);

	/* Make a copy of the input string */
	copy = strdup(str);
	if (copy == NULL)
		return (NULL);

	for (i = 0; copy[i]; i++)
	{	
		if (copy[i] == ' ')
			continue;
		count = 1;
		break;
	}
	if (count == 0)
	{
		free(copy);
		return (NULL);
	}
	count = 0;

	array = (char **) malloc((numWords + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);

	/* Check if the string starts with a colon */
	if (copy[0] == ':') 
	{
		array[count] = strdup("");
		if (array[count] == NULL) 
		{
			free_array(array);
			free(copy);
			return (NULL);
		}
		count++;
	}

	tok = strtok_r(copy, delim, &comment);

	for (i = 0; tok[i]; i++)
	{
		if (tok[i] == ' ')
		{
			memmove(&tok[i], &tok[i + 1], strlen(tok) - i);
		}
		else
			break;
	}
	
	while (tok != NULL)
	{
		len = strlen(tok);

		array[count] = (char *) malloc((len + 1) * sizeof(char));
		if (array[count] == NULL)
		{
			free_array(array);
			free(copy);
			return (NULL);
		}

		for (i = 0; i < len; i++)
			array[count][i] = tok[i];

	    array[count][i] = '\0';
		count++;
		tok = strtok_r(NULL, delim, &comment);
	}
	array[count] = NULL;
	free(copy);
	return (array);
}

/**
 * str_count_words - Count words in a string.
 * @s: String to be splitted.
 * @delim: Delimeter.
 *
 * Return: Number of words.
*/
int str_count_words(char *s, const char *delim)
{
	char *tok, *comment;
	int numWords = 0;
	char *newS = strdup(s);

	if (newS == NULL)
		return (0);

	tok = strtok_r(newS, delim, &comment);         /* Get first token */

	while (tok != NULL)               /* Check for delimiters */
	{
		numWords++;
		tok = strtok_r(NULL, delim, &comment);    /* Go through other tokens */
	}

	free(newS);
	return (numWords);
}

/**
 * remove_comment - Remove comments from a string.
 * @str: String to be checked.
 *
 * Return: 0 if no comment, 1 if comment removed.
*/
char *remove_comment(char *str)
{
	char *comment_ptr = strchr(str, '#');	/* first occurrence of the # */

	if (comment_ptr != NULL)
		*comment_ptr = '\0';
	return (str);								/* Return the modified string */
}

/**
 * _getline - Read a line into string
 * @str: string
 * @lim: limit of the line
 *
 * Return: Length
*/
int _getline(char *str, int lim)
{
	int ch, i;

	for (i = 0; i < lim - 1 && (ch = getchar()) != EOF && ch != '\n'; i++)
		str[i] = ch;
	if (ch == '\n')
	{
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
	return (i);
}

/**
 * free_array- Frees an array.
 * @arr: Array to be freed.
*/
void free_array(char **arr)
{
	int i = 0;

	for (; arr[i] != NULL; i++)
		free(arr[i]);
	free(arr);
}