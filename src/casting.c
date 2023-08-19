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
	const double		delta_x = angle == 0 ? 1e30 : fabs(1 / cos(angle));
	const double		delta_y = angle == 0 ? 1e30 : fabs(1 / sin(angle));

	double				map_x = data->player.x;
	double				map_y = data->player.y;

	int					stepX;
	int					stepY;

	double				side_x;
	double				side_y;

	if (cos(angle) < 0) // left
	{
		stepX = -1;
		side_x = (map_x - (int) map_x) * delta_x;
	}
	else // right
	{
		stepX = 1;
		side_x = ((int) map_x + 1.0 - map_x) * delta_x;
	}
	if (sin(angle) < 0) // up
	{
		stepY = -1;
		side_y = (map_y - (int) map_y) * delta_y;
	}
	else // down
	{
		stepY = 1;
		side_y = ((int) map_y + 1.0 - map_y) * delta_y;
	}


	while (is_wall(data, map_x, map_y) == false) // depth of field
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			map_x += stepX;
		}
		else
		{
			side_y += delta_y;
			map_y += stepY;
		}
	}

	double				distance;
	if (side_x > side_y)
	{
		distance = side_x - delta_x;
		mlx_put_pixel(data->screen, ((int) map_x + 1) * 64 + 255, map_y * 64, 0x00FF00FF);
	}
	else
	{
		distance = side_y - delta_y;
		mlx_put_pixel(data->screen, map_x * 64 + 255, ((int) map_y + 1) * 64, 0x00FF00FF);
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

	// clear_screen(data->screen);
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		distance = cast_ray(data, ray_angle) * data->map.tileSize;

		ray_angle += increment;
		printf("distance: %f\n", distance);

		// draw_line(data, i, distance);
	}
}
