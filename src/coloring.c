
#include "fractal.h"

int32_t	get_pixel_color(uint8_t *pixels, int i)
{
	pixels += i * 4;
	return ((pixels[0] << 24)
		+ (pixels[1] << 16)
		+ (pixels[2] << 8)
		+ pixels[3]);
}

void	clear_screen(t_data *data)
{
	memset(data->frame->pixels, 0, data->px_count * sizeof(int32_t));
}

void	color_pixels(t_data *data)
{
	int	i;
	int	color;

	i = 0;
	while (i < data->px_count)
	{
		if (!data->escape_times[i])
			mlx_put_pixel(data->frame, x(i, data), y(i, data), 0xFF);
		else
		{
			color = (((data->iteration - data->escape_times[i] + WAVE_START)
					% WAVE_BRIGHTEST) * WAVE_STEP + WAVE_DARKEST) << 8 | 0xFF;
			mlx_put_pixel(data->frame, x(i, data), y(i, data), color);
		}
		i++;
	}
}
