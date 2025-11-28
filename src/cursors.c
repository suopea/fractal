/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:31:14 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:15:56 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	rotate_pixel(t_data *data, int x, int y, uint32_t amount)
{
	uint32_t	color;

	if (x < 0 || data->width <= x || y < 0 || data->height <= y)
		return ;
	color = get_pixel_color(data->frame->pixels, i(x, y, data));
	color = (color + amount) % 0xFFFFFFFF;
	mlx_put_pixel(data->frame, x, y, color);
}

static uint32_t	color_from_brightness(uint8_t brightness)
{
	return ((brightness << 24)
		+ (brightness << 16)
		+ (brightness << 8)
		+ 0xFF);
}

static uint32_t	fade_cursor(uint32_t color, int steps, int time)
{
	uint32_t	brightness;

	brightness = (color >> 16 & 0xFF) / steps * time;
	return (color_from_brightness(brightness));
}

void	draw_cursor_cross(t_data *data)
{
	int32_t		mouse_x;
	int32_t		mouse_y;
	int			i;
	uint32_t	fade;

	fade = fade_cursor(CURSOR_COLOR, CURSOR_FADE, data->cursor_fading);
	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	if (data->mouse_last_position != mouse_x + mouse_y)
	{
		data->cursor_fading = CURSOR_FADE;
		data->mouse_last_position = mouse_x + mouse_y;
	}
	if (data->cursor_fading && !data->waiting_to_zoom)
	{
		i = 0;
		while (i < data->height && mouse_x < data->width)
			rotate_pixel(data, mouse_x, i++, fade);
		i = 0;
		while (i < data->width && mouse_y < data->height)
			rotate_pixel(data, i++, mouse_y, fade);
		data->cursor_fading--;
	}
}

void	draw_zoom_box(t_data *data)
{
	int32_t	x;
	int32_t	y;
	int32_t	color;
	int		i;

	color = fade_cursor(
			BOX_COLOR, ZOOM_WAIT, ZOOM_WAIT - data->waiting_to_zoom);
	mlx_get_mouse_pos(data->mlx, &x, &y);
	i = 0;
	while (i < data->height)
	{
		rotate_pixel(data, x - data->width * data->to_zoom_soon / 2, i, color);
		rotate_pixel(data, x + data->width * data->to_zoom_soon / 2, i, color);
		i++;
	}
	i = 0;
	while (i < data->width)
	{
		rotate_pixel(data, i, y - data->height * data->to_zoom_soon / 2, color);
		rotate_pixel(data, i, y + data->height * data->to_zoom_soon / 2, color);
		i++;
	}
}
