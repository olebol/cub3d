/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:25 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 23:57:27 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rays.h"
#include <math.h>

// Use the normalized vector to calculate the distance between two walls
void	set_side_step_distance(t_ray_data *ray_data)
{
	if (ray_data->vector.x == 0)
		ray_data->dda.delta_x = 1e30;
	else
		ray_data->dda.delta_x = fabs(1 / ray_data->vector.x);

	if (ray_data->vector.y == 0)
		ray_data->dda.delta_y = 1e30;
	else
		ray_data->dda.delta_y = fabs(1 / ray_data->vector.y);
}

/**
	@brief Calculates and sets values used by the DDA algorithm.

	@param x current x position of the player
	@param y current y position of the player
	@param ray_data ray_data struct
*/
void	set_dda_values(t_ray_data *ray_data, double x, double y)
{
	t_dda_values	*dda;

	dda = &(ray_data->dda);
	if (ray_data->vector.x < 0)
	{
		dda->distance_x = dda->delta_x * (x - (int) x);
		dda->map_step_x = -1;
	}
	else
	{
		dda->distance_x = dda->delta_x * ((int) x + 1 - x);
		dda->map_step_x = 1;
	}

	if (ray_data->vector.y < 0)
	{
		dda->distance_y = dda->delta_y * (y - (int) y);
		dda->map_step_y = -1;
	}
	else
	{
		dda->distance_y = dda->delta_y * ((int) y + 1 - y);
		dda->map_step_y = 1;
	}
}

void	set_ray_data(t_data *data, t_ray_data *ray_data, double angle)
{
	ray_data->vector = get_vector(angle);
	set_side_step_distance(ray_data);
	set_dda_values(ray_data, data->player.x, data->player.y);
	ray_data->side = 0;
}
