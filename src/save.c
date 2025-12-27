#include "fractal.h"

static void	append_float_to_file(char *string, int file, double number);

int	save_scene(t_data *data)
{
	char	*buffer;
	int		fd;

	buffer = calloc(SAVE_PRECISION + 1, 1);
	if (!buffer)
		return (EXIT_FAILURE);
	fd = open("saved_scenes", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (!fd)
	{
		free(buffer);
		return (EXIT_FAILURE);
	}
	append_float_to_file(buffer, fd, data->location.r);
	append_float_to_file(buffer, fd, data->location.i);
	append_float_to_file(buffer, fd, data->scale);
	write(fd, "\n", 1);
	close(fd);
	return (EXIT_SUCCESS);	
}

static void	append_float_to_file(char *string, int file, double number)
{
	string = gcvt(number, SAVE_PRECISION, string);	
	write(file, string, strlen(string));
	bzero(string, SAVE_PRECISION);
	write(file, ",", 1);
}


