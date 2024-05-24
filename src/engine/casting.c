/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:25 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 17:14:04 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include <math.h>

static double	get_side_step_distance(double dir)
{
	if (dir == 0)
		return (1e30);
	else
		return (fabs(1 / dir));
}

static void	set_distances_and_map_steps(t_dda_values *dda, \
										t_ray_data *ray, double x, double y)
{
	if (ray->dir.x < 0)
	{
		dda->distance_x = dda->delta_x * (x - dda->map_x);
		dda->map_step_x = -1;
	}
	else
	{
		dda->distance_x = dda->delta_x * (dda->map_x + 1 - x);
		dda->map_step_x = 1;
	}
	if (ray->dir.y < 0)
	{
		dda->distance_y = dda->delta_y * (y - dda->map_y);
		dda->map_step_y = -1;
	}
	else
	{
		dda->distance_y = dda->delta_y * (dda->map_y + 1 - y);
		dda->map_step_y = 1;
	}
}

t_dda_values	get_dda_values(t_ray_data *ray, double x, double y)
{
	t_dda_values	dda;

	dda.delta_x = get_side_step_distance(ray->dir.x);
	dda.delta_y = get_side_step_distance(ray->dir.y);
	dda.map_x = (int) x;
	dda.map_y = (int) y;
	set_distances_and_map_steps(&dda, ray, x, y);
	return (dda);
}

void	dda(t_data *data, t_ray_data *ray)
{
	t_dda_values	dda;

	dda = get_dda_values(ray, data->player.x, data->player.y);
	while (get_tile_type(&data->map, dda.map_x, dda.map_y) == FLOOR)
	{
		if (dda.distance_x < dda.distance_y)
		{
			ray->side = HORIZONTAL;
			dda.distance_x += dda.delta_x;
			dda.map_x += dda.map_step_x;
			ray->wall_hit = data->player.y \
				+ ((dda.map_x - data->player.x + (1 - dda.map_step_x) / 2) \
				/ ray->dir.x) * ray->dir.y;
		}
		else
		{
			ray->side = VERTICAL;
			dda.distance_y += dda.delta_y;
			dda.map_y += dda.map_step_y;
			ray->wall_hit = data->player.x \
				+ ((dda.map_y - data->player.y + (1 - dda.map_step_y) / 2) \
				/ ray->dir.y) * ray->dir.x;
		}
	}
	if (ray->side == HORIZONTAL)
		ray->distance = (dda.distance_x - dda.delta_x);
	else
		ray->distance = (dda.distance_y - dda.delta_y);
}

t_ray_data	cast_ray(t_data *data, int x)
{
	t_ray_data		ray;
	const double	camera_plane_x = 2 * x / (double) WIDTH - 1;

	ray.dir.x = data->player.dir.x + (data->player.cam.x * camera_plane_x);
	ray.dir.y = data->player.dir.y + (data->player.cam.y * camera_plane_x);
	ray.side = NO_SIDE;
	ray.distance = 0;
	dda(data, &ray);
	return (ray);
}
