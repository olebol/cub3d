/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:12:24 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 17:21:22 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rays.h"
#include <math.h>

static unsigned int		get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void		draw_line(t_data *data, int x, t_ray_data *ray_data)
{
	const double			distance = ray_data->distance;
	unsigned int			colour;
	size_t					lineheight;
	size_t					start_y;
	size_t					y;

	// Set the colour of the line
	colour = get_rgba(255, 255, 255, 255);
	if (ray_data->side == VERTICAL)
		colour = get_rgba(255, 255, 255, 220);

	// Calculate the height of the line to draw
	lineheight = (WIN_HEIGHT / distance) * 2;
	if (lineheight > WIN_HEIGHT)
		lineheight = WIN_HEIGHT;

	// Set the start position of the line to draw to have the middle point of the line be the middle of the screen
	start_y = WIN_HEIGHT / 2 - lineheight / 2;

	// Draw the line
	y = 0;
	while (y < lineheight)
	{
		mlx_put_pixel(data->screen, x, start_y + y, colour);
		y++;
	}
}

static void		cast_ray(t_data *data, t_ray_data *ray)
{
	int			map_x;
	int			map_y;

	// Set the current map position to the player's position
	map_x = (int) data->player.x;
	map_y = (int) data->player.y;

	while (get_tile_type(&data->map, map_x, map_y) == FLOOR)
	{
		// Move to the next tile depending on the distance to the next intersection
		
		// Move to the next horizontal intersection
		if (ray->dda.distance_x < ray->dda.distance_y)
		{
			ray->side = HORIZONTAL;

			ray->dda.distance_x += ray->dda.delta_x;
			map_x += ray->dda.map_step_x;
		}
		// Move to the next vertical intersection
		else
		{
			ray->side = VERTICAL;

			ray->dda.distance_y += ray->dda.delta_y;
			map_y += ray->dda.map_step_y;
		}
	}

	// Set distance to the wall hit -1 step 
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

	// Set the angle of the first ray to the leftmost side of the screen
	ray_angle = data->player.vec.direction - fov_in_radians / 2;

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
