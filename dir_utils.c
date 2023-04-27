#include "shell.h"
char *prevDir;

/**
 * get_current_dir - Get the current working directory.
 *
 * Return: A pointer to the current directory string.
*/
char *get_current_dir(void)
{
    char *dir;
    size_t size = 1024;

    dir = malloc(size * sizeof(char));
    if (!dir)
    {
        _perror(mem, strerror(errno));
        exit(1);
    }

    while (getcwd(dir, size) == NULL)
    {
        /* If the buffer is too small, double its size and try again */
        if (errno == ERANGE)
        {
            size *= 2;
            dir = realloc(dir, size * sizeof(char));
            if (!dir)
            {
                _perror(mem, strerror(errno));
                exit(1);
            }
        }
        else
        {
            _perror(cwd, strerror(errno));
            exit(1);
        }
    }

    return (dir);
}

/**
 * free_current_dir - Frees the memory allocated by get_current_dir.
 * @dir: A pointer to the current directory
 *
 */
void free_current_dir(char *dir)
{
    free(dir);
}