/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:25 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 19:34:50 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rays.h"

// Set the vector of the ray
void	set_vector(double angle, t_ray_data *ray_data)
{
	ray_data->vector.direction = angle;
	ray_data->vector.x = cos(angle);
	ray_data->vector.y = sin(angle);
}

// Use the vector to calculate the distance to the next wall
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

// Set up the data used by the DDA algorith: what direction to take on the map and the initial distance traveled
void	set_dda(t_player *player, t_ray_data *ray_data)
{
	if (ray_data->vector.x < 0)
	{
		ray_data->dda.distance_x = ray_data->dda.delta_x * (player->x - (int) player->x);
		ray_data->dda.map_step_x = -1;
	}
	else
	{
		ray_data->dda.distance_x = ray_data->dda.delta_x * ((int) player->x + 1 - player->x);
		ray_data->dda.map_step_x = 1;
	}

	if (ray_data->vector.y < 0)
	{
		ray_data->dda.distance_y = ray_data->dda.delta_y * (player->y - (int) player->y);
		ray_data->dda.map_step_y = -1;
	}
	else
	{
		ray_data->dda.distance_y = ray_data->dda.delta_y * ((int) player->y + 1 - player->y);
		ray_data->dda.map_step_y = 1;
	}
}

void	set_ray_data(t_data *data, t_ray_data *ray_data, double angle)
{
	set_vector(angle, ray_data);
	set_side_step_distance(ray_data);
	set_dda(&(data->player), ray_data);
	ray_data->side = 0;
}
