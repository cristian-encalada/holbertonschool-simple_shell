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
  char *tok;
  char **array;
  unsigned int len = 0, numWords = str_count_words(str, delim), count = 0, i = 0;

  array = (char **) malloc((numWords + 1) * sizeof(char *));

  if (array == NULL)
    return (NULL);
  
  tok = strtok(str, delim);

  while (tok != NULL)
  {
    for (len = 0; tok[len]; len++)
      ;

    array[count] = (char *) malloc((len + 1) * sizeof(char));
    if (array[count] == NULL)
      return (NULL);

    for (i = 0; i < len; i++)
    {
      array[count][i] = tok[i];
    }
    
    array[count][i] = '\0';

    count++;
    tok = strtok(NULL, delim);
  }

  array[count] = NULL;
  return (array);
}

int str_count_words(char *s, const char *delim)
{
  char *tok;
  int numWords;
  tok = strtok(strdup(s), delim);         /* Get first token */

  while (tok != NULL)               /* Check for delimiters */
  {
    numWords++;
    tok = strtok(NULL, delim);    /* Go through other tokens */
  }
  return (numWords);
}