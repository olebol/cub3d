/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   casting.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 22:12:24 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/17 22:56:47 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

double	cast_ray(t_data *data, double angle)
{
	double		delta_x;
	double		delta_y;

	double		ray_x = data->player.x;
	double		ray_y = data->player.y;

	delta_x = cos(angle);
	delta_y = sin(angle);

	double		distance = 0;

	

	while (distance < 255) // depth of field
	{
		ray_x += delta_x;
		ray_y += delta_y;

		// check if wall
		if (data->map.map[(int) ray_y / data->map.tileSize][(int) ray_x / data->map.tileSize] == '1')
			break ;

		// add step to distance
		distance += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	}
	return (distance);
}

unsigned int	get_colour(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_line(t_data *data, int x, double distance)
{
	int		lineheight; 
	int		colour;

	if (distance <= 0)
			distance = 1;

	colour = get_colour(255, 255, 255, 255 - distance);

	lineheight = (data->map.tileSize / distance) * data->map.tileSize * 10;
	if (lineheight > WIN_HEIGHT)
		lineheight = WIN_HEIGHT;


	int		start = WIN_HEIGHT / 2 - lineheight / 2;

	for (int j = 0; j < lineheight; j++)
		mlx_put_pixel(data->screen, x, start + j, colour);
}

void	cast_all_rays(t_data *data)
{
	double		fov = 90;
	double		ray_angle = data->player.angle - (fov * M_PI / 180) / 2;

	double		increment = (fov * M_PI / 180) / WIN_WIDTH;

	double 		distance;

	for (int i = 0; i < WIN_WIDTH; i++)
	{
		distance = cast_ray(data, ray_angle);

		ray_angle += increment;

		draw_line(data, i, distance);
	}
}
