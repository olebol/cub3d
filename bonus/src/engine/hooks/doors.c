/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:30:02 by evalieve          #+#    #+#             */
/*   Updated: 2024/06/03 18:52:52 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include "utils.h"
#include <math.h>

static void	ft_free_ray(t_ray_data *ray)
{
	t_ray_data		*next;

	while (ray)
	{
		next = ray->next;
		free(ray);
		ray = next;
	}
}

/**
 * @brief	Open or close the door
 * 
 * @param	data	Pointer to the main data structure
 */
static void	interact(t_data *data, t_ray_data *ray)
{
	if (ray->tile_hit == CLOSED_DOOR)
		set_tile_type(&data->map, ray->hit_x, ray->hit_y, OPEN_DOOR);
	else if (ray->tile_hit == OPEN_DOOR)
		set_tile_type(&data->map, ray->hit_x, ray->hit_y, CLOSED_DOOR);
}

/**
 * @brief	Door hook to check whether to open or close the door
 * 
 * @param	data	Pointer to the main data structure
 */
void	door_hook(t_data *data)
{
	t_ray_data			*ray;
	static double		last_time = 0;
	const double		current_time = mlx_get_time();

	if (mlx_is_key_down(data->mlx, MLX_KEY_E) == true)
	{
		if (current_time - last_time < 0.2)
			return ;
		ray = cast_ray(data, WIDTH / 2, true);
		if (ray->distance > 1.5 || ray->distance < 0)
		{
			ft_free_ray(ray);
			return ;
		}
		interact(data, ray);
		last_time = current_time;
		ft_free_ray(ray);
	}
}