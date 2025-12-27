#include "fractal.h"
#include <stdlib.h>

static void	append_float_to_file(char *string, int file, double number);
static char	*read_file(char *filename);
static t_scene	*string_to_scene_array(char *string);

int	save_scene(t_data *data)
{
	char	*buffer;
	int		fd;

	buffer = calloc(SAVE_PRECISION + 1, 1);
	if (!buffer)
		return (EXIT_FAILURE);
	fd = open(SCENE_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
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

int	load_scenes(t_data *data)
{
	char	*scenes_string;

	scenes_string = read_file(SCENE_FILE);
	printf("\n\n%s\n", scenes_string);
	data->scenes = string_to_scene_array(scenes_string);

	return (EXIT_SUCCESS);
}

static t_scene	*string_to_scene_array(char *string)
{
	// t_scene	*array;
	char	*line;

	line = strtok(string, "\n");
	while (line)
	{
		printf("line: %s\n", line);
		line = strtok(NULL, "\n");
	}

	return (NULL);
}

static char	*read_file(char *filename)
{
	int		fd;
	char	*buffer;
	ssize_t	bytes_read;
	ssize_t	offset;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = NULL;
	offset = 0;
	do
	{
		buffer = realloc(buffer, BUFFER_SIZE + offset);
		bytes_read = read(fd, buffer + offset, BUFFER_SIZE);
		offset += bytes_read;
	} while (bytes_read);
	return (buffer);
}
