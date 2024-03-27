/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:25 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 20:16:46 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include "utils.h"

#include <math.h>

// set the distance to the next horizontal intersection to the left and define the direction to take on the map
void		set_distances_and_map_steps(t_dda_values *dda, \
										t_ray_data *ray, double x, double y)
{
	// ray pointed left
	if (ray->dir.x < 0)
	{
		dda->distance_x = dda->delta_x * (x - dda->map_x);
		dda->map_step_x = -1;
	}
	// ray pointed right
	else
	{
		dda->distance_x = dda->delta_x * (dda->map_x + 1 - x);
		dda->map_step_x = 1;
	}

	// ray pointed upwards
	if (ray->dir.y < 0)
	{
		dda->distance_y = dda->delta_y * (y - dda->map_y);
		dda->map_step_y = -1;
	}
	// ray pointed downwards
	else
	{
		dda->distance_y = dda->delta_y * (dda->map_y + 1 - y);
		dda->map_step_y = 1;
	}
}

t_dda_values	get_dda_values(t_ray_data *ray, double x, double y)
{
	t_dda_values	dda;

	// Set the distance between two intersections
	if (ray->dir.x == 0) // parallel
		dda.delta_x = INFINITY;
	else
		dda.delta_x = fabs(1 / ray->dir.x);
	
	if (ray->dir.y == 0) // parallel
		dda.delta_y = INFINITY;
	else
		dda.delta_y = fabs(1 / ray->dir.y);

	// Set the current map position to the player's position
	dda.map_x = (int) x;
	dda.map_y = (int) y;

	set_distances_and_map_steps(&dda, ray, x, y);

	return (dda);
}

// Move to the next horizontal or vertical intersection
void		go_to_next_intersection(t_ray_data *ray, t_dda_values *dda)
{
	if (dda->distance_x < dda->distance_y) // Move to the next horizontal intersection
	{
		dda->distance_x += dda->delta_x;
		dda->map_x += dda->map_step_x;

		ray->side = HORIZONTAL;
	}
	else // Move to the next vertical intersection
	{
		dda->distance_y += dda->delta_y;
		dda->map_y += dda->map_step_y;

		ray->side = VERTICAL;
	}
}

// Calculate the exact position of the wall hit and the distance to the wall hit
void		calculate_hit(t_data *data, t_ray_data *ray, t_dda_values *dda)
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
		// Save the tile type of the current position
		ray->tile_hit = get_tile_type(&data->map, dda.map_x, dda.map_y);

		// Stop the DDA algorithm
		if (ray->tile_hit == WALL || 
			ray->tile_hit == CLOSED_DOOR)
			break ;

		// Save location and keep going until the ray hits a wall
		if (ray->tile_hit == OPEN_DOOR)
		{
			break ;
		}

		// Move to the next tile depending on the distance to the next intersection
		go_to_next_intersection(ray, &dda);
	}

	// Set distance to the wall hit -1 step and calculate the exact position of the wall hit
	calculate_hit(data, ray, &dda);
}

t_ray_data		cast_ray(t_data *data, int x)
{
	t_ray_data		ray;
	const double	fov = M_PI / 2; // field of view
	const double	camera_plane_x = fov * (x / (double) WIN_WIDTH) - fov / 2; // value between -1 and 1 representing the x-coordinate on the camera plane

	// Calculate the direction of the ray
	ray.dir.x = data->player.dir.x + (data->player.cam.x * camera_plane_x);
	ray.dir.y = data->player.dir.y + (data->player.cam.y * camera_plane_x);

	// Set all fields to 0
	ray.side = NO_SIDE;
	ray.hit_x = 0;
	ray.hit_y = 0;
	ray.tile_hit = EMPTY;
	ray.distance = 0;

	dda(data, &ray);

	return (ray);
}
