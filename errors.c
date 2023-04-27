#include "shell.h"

/**
 * _perror - Custom print error function.
 * @err: Which type of error is happening.
 * @s: Extra details about it.
*/
void _perror(enum errors err, char *s, ...)
{
	va_list args;

	if (!s)
		s = "(null)";

	va_start(args, s);

	switch (err)
	{
		case cmd:
			fprintf(stderr, "Error: Not valid sintax. Use: %s\n", s);
			break;
		case mem:
			fprintf(stderr, "Error: Failed to allocate memory: %s\n", s);
			break;
		case cwd:
			fprintf(stderr, "Error: Failed to get the current working directory: %s\n", s);
			break;
		case custom:
			vfprintf(stderr, s, args);
			break;
	}

	va_end(args);
}
