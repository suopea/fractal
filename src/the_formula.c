/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_formula.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:20:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:14:20 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	iterate_pixel(t_complex *c, t_complex *z, t_data *data, int i)
{
	double	i_squared;
	double	r_squared;

	i_squared = z->i * z->i;
	r_squared = z->r * z->r;
	z->r = (z->i + z->i) * z->r + c->r;
	z->i = i_squared - r_squared + c->i;
	if (i_squared + r_squared > 4)
		data->escape_times[i] = data->iteration;
}

void	iterate_once(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->px_count)
	{
		if (!data->escape_times[i])
			iterate_pixel(&data->px[i], &data->orbits[i], data, i);
		i++;
	}
	data->iteration++;
}
