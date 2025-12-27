#include "fractal.h"

size_t	newline_count(char *str)
{
	size_t	count = 0;

	while (*str)
	{
		if (*str == '\n')
			count++;
		str++;
	}
	return (count);
}
