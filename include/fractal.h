/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:47:25 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:24:24 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "MLX42/MLX42.h"

# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <assert.h>

# define WIDTH 1000
# define HEIGHT 600
# define DEFAULT_SCALE 0.005
# define ZOOM_WAIT 15
# define RESIZE_WAIT 10
# define SCROLL_AMOUNT 1.1
# define BOX_COLOR 0x77777700
# define CURSOR_COLOR 0x33333300
# define CURSOR_FADE 20
# define SAVE_PRECISION 20

# define WAVE_BRIGHTEST 0xCC
# define WAVE_DARKEST 0x111111
# define WAVE_START 80
# define WAVE_STEP 0x010101

# define KEY_ESC MLX_KEY_ESCAPE
# define KEY_REITERATE MLX_KEY_I
# define KEY_RESET MLX_KEY_R
# define KEY_SAVE MLX_KEY_S

# define SCENE_FILE "saved_scenes"
# define BUFFER_SIZE 10

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_data
{
	t_complex		*px;
	int				px_count;
	t_complex		*orbits;
	int				*escape_times;
	mlx_image_t		*frame;
	double			scale;
	double			to_zoom_soon;
	int				waiting_to_zoom;
	int				iteration;
	t_complex		location;
	mlx_t			*mlx;
	int				width;
	int				height;
	int				new_width;
	int				new_height;
	int				new_px_count;
	bool			paused;
	int				resizing;
	int				mouse_last_position;
	int				cursor_fading;
	char			**scenes;
}	t_data;

/* input validation */

void	validate_inputs(int argc, char **argv);
double	ft_strtod(char *in, int *flag);
int		ft_strcmp(char *s1, char *s2);

/* starting up and resetting stuff */

void	initialize_program(t_data *data);
int		initialize_mlx(t_data *data);
void	reset(t_data *data);
void	reset_orbits(t_data *data);

/* hooks */

void	scroll_hook(double xdelta, double ydelta, void *input);
void	key_hook(mlx_key_data_t keydata, void *input);
void	resize_hook(int32_t width, int32_t height, void *input);
void	mouse_hook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *input);

/* mandelbrot math */

void	iterate_once(t_data *data);

/* draw */

void	clear_screen(t_data *data);
void	color_pixels(t_data *data);
int32_t	get_pixel_color(uint8_t *pixels, int i);
void	draw_cursor_cross(t_data *data);
void	draw_zoom_box(t_data *data);

/* coordinates and scaling */

void	update_locations(t_data *data);
void	new_location_from_center(t_data *data, int x, int y);
void	zoom_to_point(t_data *data, int x, int y, float change);
void	get_cursor_location_and_zoom(t_data *data, float zoom_amount);
void	resize(t_data *data);
int		about_to_resize(t_data *data);

/* converting between indexes and coordinates */

int		center(t_data *data);
int		i(int x, int y, t_data *data);
int		x(int i, t_data *data);
int		y(int i, t_data *data);

/* memory allocation */

void	allocate_everything(t_data *data);
void	free_everything(t_data *data);
void	free_and_exit(t_data *data);

/* save and restore scenes */

int		save_scene(t_data *data);
int		load_scenes(t_data *data);

#endif
