/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:32:02 by opelser           #+#    #+#             */
/*   Updated: 2024/06/06 23:00:55 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_ray_data	*copy_ray(t_ray_data *old)
{
	t_ray_data		*new;

	new = (t_ray_data *) ft_malloc(sizeof(t_ray_data));
	new->dir.direction = old->dir.direction;
	new->dir.x = old->dir.x;
	new->dir.y = old->dir.y;
	new->side = old->side;
	new->distance = old->distance;
	new->hit_x = old->hit_x;
	new->hit_y = old->hit_y;
	new->tile_hit = old->tile_hit;
	new->next = old;
	return (new);
}
