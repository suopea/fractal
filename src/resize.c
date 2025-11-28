/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:12:42 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/28 15:16:00 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	resize(t_data *data)
{
	t_complex	location_temp;
	double		scale_temp;	

	location_temp = data->location;
	scale_temp = data->scale * ((float)data->width / data->new_width);
	data->width = data->new_width;
	data->height = data->new_height;
	data->px_count = data->new_px_count;
	mlx_delete_image(data->mlx, data->frame);
	data->frame = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->frame
		|| mlx_image_to_window(data->mlx, data->frame, 0, 0) < 0)
		free_and_exit(data);
	free_everything(data);
	allocate_everything(data);
	reset(data);
	data->location = location_temp;
	data->scale = scale_temp;
	update_locations(data);
}

int	about_to_resize(t_data *data)
{
	if (data->resizing)
	{
		if (data->resizing > RESIZE_WAIT)
		{
			resize(data);
			return (1);
		}
		data->resizing++;
		return (1);
	}
	return (0);
}
