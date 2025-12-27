#include "fractal.h"
#include <stdlib.h>

static t_scene	line_to_scene(char *string);

void	scene_switch(t_data *data, int i)
{
	printf("index before %lu ", data->scene_index);
	data->scene_index = (data->scene_index + data->scene_count + i) % data->scene_count;
	printf("\nindex after %lu \n\n", data->scene_index);
	data->location.r = data->scenes[data->scene_index].location.r;
	data->location.i = data->scenes[data->scene_index].location.i;
	data->scale = data->scenes[data->scene_index].scale;
	update_locations(data);
}

t_scene	*string_to_scene_array(char *string, size_t scene_count)
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

