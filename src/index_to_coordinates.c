/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_to_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:21:03 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:14:41 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	i(int x, int y, t_data *data)
{
	return (y * data->width + x);
}

int	center(t_data *data)
{
	return (i(data->width / 2, data->height / 2, data));
}

int	x(int i, t_data *data)
{
	return (i % data->width);
}

int	y(int i, t_data *data)
{
	return (i / data->width);
}
