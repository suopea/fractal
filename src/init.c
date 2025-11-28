/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:06:27 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:16:23 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	initialize_program(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->px_count = data->width * data->height;
	data->to_zoom_soon = 1;
	data->waiting_to_zoom = 0;
	data->mouse_last_position = 0;
	data->frame = NULL;
	data->mlx = NULL;
	allocate_everything(data);
}

int	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!data->mlx)
		return (0);
	data->frame = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->frame)
		return (0);
	if (mlx_image_to_window(data->mlx, data->frame, 0, 0) < 0)
		return (0);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	return (1);
}

void	reset(t_data *data)
{
	data->paused = false;
	data->resizing = 0;
	data->px_count = data->width * data->height;
	bzero(data->escape_times, data->px_count * sizeof(int));
	data->scale = DEFAULT_SCALE;
	data->location.i = 0;
	data->location.r = 0;
	data->iteration = 0;
	update_locations(data);
	new_location_from_center(data, 0, 0);
}
