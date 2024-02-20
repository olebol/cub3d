/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:12:24 by opelser           #+#    #+#             */
/*   Updated: 2024/02/20 14:09:16 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rays.h"
#include <math.h>

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_line(t_data *data, int x, t_ray_data *ray_data)
{
	const double			distance = ray_data->distance;
	unsigned int			colour;
	size_t					lineheight;
	size_t					start_y;
	size_t					y;

	colour = get_rgba(255, 255, 255, 255);
	if (ray_data->side == VERTICAL)
		colour = get_rgba(255, 255, 255, 220);
	lineheight = (WIN_HEIGHT / distance) * 2;
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

void	cast_ray(t_data *data, t_ray_data *ray)
{
	int			map_x;
	int			map_y;

	map_x = (int) data->player.x;
	map_y = (int) data->player.y;

	while (is_wall(data, map_x, map_y) == false)
	{
		if (ray->dda.distance_x < ray->dda.distance_y)
		{
			ray->dda.distance_x += ray->dda.delta_x;
			map_x += ray->dda.map_step_x;
			ray->side = HORIZONTAL;
		}
		else
		{
			ray->dda.distance_y += ray->dda.delta_y;
			map_y += ray->dda.map_step_y;
			ray->side = VERTICAL;
		}
	}
	if (ray->side == HORIZONTAL)
		ray->distance = (ray->dda.distance_x - ray->dda.delta_x);
	else
		ray->distance = (ray->dda.distance_y - ray->dda.delta_y);
}

void	cast_all_rays(t_data *data)
{
	t_ray_data			ray_data;
	const double		fov_in_radians = 90 * (M_PI / 180);
	const double		increment = fov_in_radians / WIN_WIDTH;
	double				ray_angle;
	size_t				x;

	ray_angle = data->player.angle - fov_in_radians / 2;

	x = 0;
	while (x < WIN_WIDTH)
	{
		set_ray_data(data, &ray_data, ray_angle);
		cast_ray(data, &ray_data);

		draw_line(data, x, &ray_data);

		ray_angle += increment;
		x++;
	}
}
