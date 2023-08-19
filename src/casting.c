/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   casting.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 22:12:24 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/19 23:55:45 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

typedef struct		s_vector
{
	double			x;
	double			y;
	double			direction;
}					t_vector;




t_vector	set_vector(double angle)
{
	t_vector	vector;

	vector.direction = angle;
	vector.x = cos(angle);
	vector.y = sin(angle);
	return (vector);
}

double	cast_ray(t_data *data, t_vector ray)
{
	int			map_x;
	int			map_y;

	int			step_x;
	int			step_y;

	double		side_x;
	double		side_y;

	double		delta_x;
	double		delta_y;

	map_x = (int) data->player.x;
	map_y = (int) data->player.y;

	if (ray.x == 0)
		delta_x = 1e30;
	else
		delta_x = fabs(1 / ray.x);

	if (ray.y == 0)
		delta_y = 1e30;
	else
		delta_y = fabs(1 / ray.y);

	if (ray.x < 0) // left
	{
		step_x = -1;
		side_x = delta_x * (data->player.x - map_x);
	}
	else // right
	{
		step_x = 1;
		side_x = delta_x * (map_x + 1 - data->player.x);
	}

	if (ray.y < 0) // up
	{
		step_y = -1;
		side_y = delta_y * (data->player.y - map_y);
	}
	else // down
	{
		step_y = 1;
		side_y = delta_y * (map_y + 1 - data->player.y);
	}

	int side;
	while (is_wall(data, map_x, map_y) == false)
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			map_x += step_x;
			side = 0; // horizontal
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
			side = 1; // vertical
		}
	}
	if (side == 0)
		return (side_x - delta_x);
	else
		return (side_y - delta_y);
}

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_line(t_data *data, int x, double distance)
{
	const unsigned int		colour = get_rgba(255, 255, 255, 255 - distance);
	size_t					lineheight; 
	size_t					start_y;
	size_t					y;

	lineheight = (WIN_HEIGHT / distance);
	if (lineheight > WIN_HEIGHT)
		lineheight = WIN_HEIGHT;

	start_y = WIN_HEIGHT / 2 - lineheight / 2;

	y = 0;
	while (y < lineheight)
	{
		mlx_put_pixel(data->screen, x, start_y + y, colour);
		y++;
	}
}

void		clear_line(mlx_image_t *img, size_t x)
{
	size_t		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(img, x, y, 0x00000000);
		y++;
	}
}

void	cast_all_rays(t_data *data)
{
	const double		fov_in_radians = 90 * (M_PI / 180);
	const double		increment = fov_in_radians / WIN_WIDTH;
	double				ray_angle;
	double 				distance;
	size_t				x;


	ray_angle = data->player.angle - fov_in_radians / 2;

	x = 0;
	while (x < WIN_WIDTH)
	{
		distance = cast_ray(data, set_vector(ray_angle));

		clear_line(data->screen, x);
		draw_line(data, x, distance);

		ray_angle += increment;
		x++;
	}
}
