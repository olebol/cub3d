/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   casting.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 22:12:24 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/17 00:08:07 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	cast_ray(t_data *data, float angle)
{
	float		delta_x;
	float		delta_y;

	float		ray_x = data->player.x;
	float		ray_y = data->player.y;

	delta_x = cos(angle);
	delta_y = sin(angle);

	while (data->map.map[(int) ray_y / data->map.tileSize][(int) ray_x / data->map.tileSize] != '1')
	{
		ray_x += delta_x;
		ray_y += delta_y;
		mlx_put_pixel(data->screen, ray_x + WIN_WIDTH / 2, ray_y + WIN_HEIGHT / 2, 0x00FFFFFF);
	}
}
