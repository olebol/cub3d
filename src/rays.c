/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:25 by opelser           #+#    #+#             */
/*   Updated: 2024/02/15 15:42:43 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rays.h"

t_vector	set_vector(double angle)
{
	t_vector	vector;

	vector.direction = angle;
	vector.x = cos(angle);
	vector.y = sin(angle);
	return (vector);
}

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
	ray_data->vector = set_vector(angle);
	set_side_step_distance(ray_data);
	set_dda(&data->player, ray_data);
}
