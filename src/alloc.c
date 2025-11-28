/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:17:08 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/28 15:17:49 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	free_everything(t_data *data)
{
	if (data->escape_times)
	{
		free(data->escape_times);
		data->escape_times = NULL;
	}
	if (data->orbits)
	{
		free(data->orbits);
		data->orbits = NULL;
	}
	if (data->px)
	{
		free(data->px);
		data->px = NULL;
	}
}

void	free_and_exit(t_data *data)
{
	if (data->frame)
		mlx_delete_image(data->mlx, data->frame);
	if (data->mlx)
		mlx_terminate(data->mlx);
	free_everything(data);
	exit (1);
}

void	allocate_everything(t_data *data)
{
	data->px = malloc(data->px_count * sizeof(t_complex));
	data->orbits = malloc(data->px_count * sizeof(t_complex));
	data->escape_times = calloc(data->px_count, sizeof(int));
	if (!data->px || !data->orbits || !data->escape_times)
		free_and_exit(data);
}
