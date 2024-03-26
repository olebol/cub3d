/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doors.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 15:30:02 by evalieve      #+#    #+#                 */
/*   Updated: 2024/03/26 17:19:30 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include <math.h>

void		door_hook(t_data *data)
{
	t_ray_data	ray;

	static double		last_time = 0;
	const double 		current_time = mlx_get_time();

	if (current_time - last_time > 0.2)
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_E) == true)
		{
			ray = cast_ray(data, WIN_WIDTH / 2);
			if (ray.distance > 2 || ray.distance < 0)
				return ;
			if (ray.tile_hit == CLOSED_DOOR)
				data->map.map[(int)ray.tile_y][(int)ray.tile_x] = OPEN_DOOR;
			else if (ray.tile_hit == OPEN_DOOR)
				data->map.map[(int)ray.tile_y][(int)ray.tile_x] = CLOSED_DOOR;
			last_time = current_time;
		}
	}
}

