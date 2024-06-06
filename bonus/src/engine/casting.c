/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:25 by opelser           #+#    #+#             */
/*   Updated: 2024/06/06 23:00:41 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include "utils.h"

#include <math.h>

// DDA algorithm to calculate the distance to the next wall hit
static void	dda_door(t_data *data, t_ray_data *ray, t_dda_values *dda)
{
	while (true)
	{
		ray->tile_hit = get_tile_type(&data->map, dda->map_x, dda->map_y);
		if (ray->tile_hit != FLOOR)
			break ;
		go_to_next_intersection(ray, dda);
	}
	calculate_hit(data, ray, dda);
}

// DDA algorithm to calculate the distance to the next wall hit
static t_ray_data	*dda_loop(t_data *data, t_ray_data *ray, t_dda_values *dda)
{
	while (true)
	{
		ray->tile_hit = get_tile_type(&data->map, dda->map_x, dda->map_y);
		if (ray->tile_hit == WALL || ray->tile_hit == CLOSED_DOOR)
			break ;
		if (ray->tile_hit == OPEN_DOOR)
		{
			calculate_hit(data, ray, dda);
			ray = copy_ray(ray);
		}
		go_to_next_intersection(ray, dda);
	}
	calculate_hit(data, ray, dda);
	return (ray);
}

t_ray_data	*cast_ray(t_data *data, int x, bool door_interaction)
{
	const double	fov = M_PI / 2;
	const double	camera_plane_x = fov * (x / (double) WIDTH) - fov / 2;
	t_ray_data		*ray;
	t_dda_values	dda_values;

	ray = (t_ray_data *) ft_malloc(sizeof(t_ray_data));
	ray->next = NULL;
	ray->dir.x = data->player.dir.x + (data->player.cam.x * camera_plane_x);
	ray->dir.y = data->player.dir.y + (data->player.cam.y * camera_plane_x);
	ray->side = NO_SIDE;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->tile_hit = EMPTY;
	ray->distance = 0;
	dda_values = get_dda_values(ray, data->player.x, data->player.y);
	if (door_interaction)
		dda_door(data, ray, &dda_values);
	else
		ray = dda_loop(data, ray, &dda_values);
	return (ray);
}
