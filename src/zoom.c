
#include "fractal.h"

void	get_cursor_location_and_zoom(t_data *data, float zoom_amount)
{
	int	x;
	int	y;

	data->waiting_to_zoom = 0;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (zoom_amount >= 1)
		zoom_to_point(data, x, y, zoom_amount);
	else
	{
		data->location = data->px[i(x - data->width * data->to_zoom_soon / 2,
				y - data->height * data->to_zoom_soon / 2, data)];
		data->scale *= zoom_amount;
		update_locations(data);
	}
}

void	zoom_to_point(t_data *data, int x, int y, float change)
{
	if (change < 1)
	{
		data->location.r += (data->px[i(x, y, data)].r
				- data->location.r) * (1 - change);
		data->location.i += (data->px[i(x, y, data)].i
				- data->location.i) * (1 - change);
	}
	else
	{
		data->location.r -= (data->px[i(x, y, data)].r
				- data->location.r) * (change - 1);
		data->location.i -= (data->px[i(x, y, data)].i
				- data->location.i) * (change - 1);
	}
	data->scale *= change;
	update_locations(data);
}
