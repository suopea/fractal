
#include "fractal.h"

void	display_scene_array(t_data *data)
{
	size_t	i = 0;

	while (i < data->scene_count)
	{
		printf("scene %lu:\n%f\n%f\n%f\n\n", i,
		 data->scenes[i].location.i, data->scenes[i].location.r,
		 data->scenes[i].scale);
		i++;
	}
}
