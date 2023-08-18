/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   casting.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 22:12:24 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/19 00:05:10 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

double	cast_ray(t_data *data, double angle)
{
	const double		delta_x = cos(angle) / data->map.tileSize;
	const double		delta_y = sin(angle) / data->map.tileSize;

	double				ray_x = data->player.x;
	double				ray_y = data->player.y;

	double				distance = 0;

	while (distance < 255) // depth of field
	{
		ray_x += delta_x;
		ray_y += delta_y;

		// printf("ray_x: %f\n", ray_x);

		// check if wall
		if (is_wall(data, ray_x, ray_y) == true)
			break ;

		// add step to distance
		distance += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
		mlx_put_pixel(data->screen, ray_x, ray_y, 0x00FF00FF);
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

	colour = get_colour(255, 255, 255, 255 - distance / 3);

	lineheight = (data->map.tileSize / distance) * data->map.tileSize * 64;
	if (lineheight > WIN_HEIGHT)
		lineheight = WIN_HEIGHT;

	int		start = WIN_HEIGHT / 2 - lineheight / 2;

	for (int j = 0; j < lineheight; j++)
		mlx_put_pixel(data->screen, x, start + j, colour);
}
void		clear_screen(mlx_image_t *img)
{
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		// for (int j = 0; j < WIN_HEIGHT / 2; j++) // make dark green
		// 	mlx_put_pixel(img, i, j, 0x023020FF);
		// for (int j = WIN_HEIGHT / 2; j < WIN_HEIGHT; j++)
		// 	mlx_put_pixel(img, i, j, 0xDAF7A6FF);
		for (int j = 0; j < WIN_HEIGHT; j++)
			mlx_put_pixel(img, i, j, 0x000000FF);
	}
}

void	cast_all_rays(t_data *data)
{
	double		fov = 90;
	double		ray_angle = data->player.angle - (fov * M_PI / 180) / 2;

	double		increment = (fov * M_PI / 180) / WIN_WIDTH;

	double 		distance;

	clear_screen(data->screen);
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		distance = cast_ray(data, ray_angle) * data->map.tileSize;

		ray_angle += increment;

		draw_line(data, i, distance);
	}
}
