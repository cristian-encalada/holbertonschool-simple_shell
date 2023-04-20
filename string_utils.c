#include "shell.h"

/**
 * split_str - Splits a string.
 * @s: String to be splitted.
 *
 * Return: Void
*/
char **split_str(char *str)
{
	const char *delim = " ";         /* Delimiter */
	char *tok, *copy;
	char **array;
	unsigned int len = 0, numWords = str_count_words(str, delim), count = 0, i = 0;

	/* Make a copy of the input string */
	copy = strdup(str);
	if (copy == NULL)
		return (NULL);

	array = (char **) malloc((numWords + 1) * sizeof(char *));

	if (array == NULL)
		return (NULL);
	
	tok = strtok(copy, delim);

	while (tok != NULL)
	{
		for (len = 0; tok[len]; len++)
			;

		array[count] = (char *) malloc((len + 1) * sizeof(char));
		if (array[count] == NULL)
		{
			free_array(array);
			free(copy);  /* Free the copy of the input string */
			return (NULL);
		}

		for (i = 0; i < len; i++)
		{
			array[count][i] = tok[i];
		}
		
		array[count][i] = '\0';

		count++;
		tok = strtok(NULL, delim);
	}

	array[count] = NULL;

	free(copy);  /* Free the copy of the input string */
	
	return (array);
}


int str_count_words(char *s, const char *delim)
{
	char *tok;
	int numWords = 0;
	char *newS = strdup(s);

	if (newS == NULL)
		return (0);

	tok = strtok(newS, delim);         /* Get first token */

	while (tok != NULL)               /* Check for delimiters */
	{
		numWords++;
		tok = strtok(NULL, delim);    /* Go through other tokens */
	}

	free(newS);
	return (numWords);
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

  for (i = 0; i < lim -1 && (ch = getchar()) != EOF && ch != '\n';i++)
    str[i] = ch;
  if (ch == '\n')
  {
    str [i] = ch;
    i++;  
  }
  str [i] = '\0';
  return (i);
}

/**
 * free_array- Frees an array
 * 
 * @array: Array to be freed.
 * Return: void.
*/
void free_array(char **arr)
{
	int i = 0;

	for (; arr[i] != NULL; i++) {
		free(arr[i]);
	}
	free(arr);
}