#include "fractal.h"
#include <stdlib.h>

static void	append_float_to_file(char *string, int file, double number);
static char	*read_file(char *filename);
static t_scene	*string_to_scene_array(char *string, size_t scene_count);
static size_t	newline_count(char *str);
static t_scene	line_to_scene(char *string);

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
	data->scene_count = newline_count(scenes_string);
	data->scenes = string_to_scene_array(scenes_string, data->scene_count);
	display_scene_array(data);

	return (EXIT_SUCCESS);
}

static t_scene	*string_to_scene_array(char *string, size_t scene_count)
{
	t_scene	*scene_array;
	char	**line_array;
	size_t	i = 0;

	assert(!strstr(string, "\n\n"));
	line_array = calloc(scene_count + 1, sizeof(char *));
	line_array[i] = strtok(string, "\n");
	while (i < scene_count)
	{
		i++;
		line_array[i] = strtok(NULL, "\n");
	}

	scene_array = calloc(scene_count + 1, sizeof(t_scene));
	i = 0;
	while (i < scene_count)
	{
		scene_array[i] = line_to_scene(line_array[i]);
		i++;
	}
	free(line_array);
	return (scene_array);
}

static t_scene	line_to_scene(char *string)
{
	t_scene	scene;
	char	*token;

	token = strtok(string, ",");
	scene.location.r = strtod(token, NULL);
	token = strtok(NULL, ",");
	scene.location.i = strtod(token, NULL);
	token = strtok(NULL, ",");
	scene.scale = strtod(token, NULL);
	return (scene);	
}

static size_t	newline_count(char *str)
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
