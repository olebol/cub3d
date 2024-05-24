/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:25 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 17:34:31 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include "utils.h"

#include <math.h>

void	set_distances_and_map_steps(t_dda_values *dda, \
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

	if (ray->dir.x == 0)
		dda.delta_x = INFINITY;
	else
		dda.delta_x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		dda.delta_y = INFINITY;
	else
		dda.delta_y = fabs(1 / ray->dir.y);
	dda.map_x = (int) x;
	dda.map_y = (int) y;
	set_distances_and_map_steps(&dda, ray, x, y);
	return (dda);
}

// Move to the next horizontal or vertical intersection
void	go_to_next_intersection(t_ray_data *ray, t_dda_values *dda)
{
	if (dda->distance_x < dda->distance_y)
	{
		dda->distance_x += dda->delta_x;
		dda->map_x += dda->map_step_x;
		ray->side = HORIZONTAL;
	}
	else
	{
		dda->distance_y += dda->delta_y;
		dda->map_y += dda->map_step_y;
		ray->side = VERTICAL;
	}
}

// Calculate the exact position of the wall hit and the distance to the wall hit
void	calculate_hit(t_data *data, t_ray_data *ray, t_dda_values *dda)
{
	if (ray->side == HORIZONTAL)
	{
		ray->distance = (dda->distance_x - dda->delta_x);
		ray->hit_x = dda->map_x;
		ray->hit_y = data->player.y + (ray->distance * ray->dir.y);
	}
	else
	{
		ray->distance = (dda->distance_y - dda->delta_y);
		ray->hit_x = data->player.x + (ray->distance * ray->dir.x);
		ray->hit_y = dda->map_y;
	}
}

// DDA algorithm to calculate the distance to the next wall hit
void	dda(t_data *data, t_ray_data *ray)
{
	t_dda_values	dda;

	dda = get_dda_values(ray, data->player.x, data->player.y);
	while (true)
	{
		ray->tile_hit = get_tile_type(&data->map, dda.map_x, dda.map_y);
		if (ray->tile_hit == WALL)
			break ;
		go_to_next_intersection(ray, &dda);
	}
	calculate_hit(data, ray, &dda);
}

t_ray_data	cast_ray(t_data *data, int x)
{
	t_ray_data		ray;
	const double	fov = M_PI / 2;
	const double	camera_plane_x = fov * (x / (double) WIDTH) - fov / 2;

	ray.dir.x = data->player.dir.x + (data->player.cam.x * camera_plane_x);
	ray.dir.y = data->player.dir.y + (data->player.cam.y * camera_plane_x);
	ray.side = NO_SIDE;
	ray.hit_x = 0;
	ray.hit_y = 0;
	ray.tile_hit = EMPTY;
	ray.distance = 0;
	dda(data, &ray);
	return (ray);
}
