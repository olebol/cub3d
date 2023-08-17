/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   casting.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 22:12:24 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/17 16:28:37 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

float	cast_ray(t_data *data, float angle)
{
	float		delta_x;
	float		delta_y;

	float		ray_x = data->player.x;
	float		ray_y = data->player.y;

	delta_x = cos(angle);
	delta_y = sin(angle);

	float		distance = 0;

	while (distance < 1000000) // depth of field
	{
		ray_x += delta_x;
		ray_y += delta_y;

		int		pixelX = (ray_x - data->player.x) + data->map.minimapSize / 2;
		int		pixelY = (ray_y - data->player.y) + data->map.minimapSize / 2;

		// check if wall
		if (data->map.map[(int) ray_y / data->map.tileSize][(int) ray_x / data->map.tileSize] != '1')
			distance += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
		else
			break ;

		// Draw ray on minimap
		if (pixelX >= 0 && pixelX < data->map.minimapSize 
			&& pixelY >= 0 && pixelY < data->map.minimapSize)
			mlx_put_pixel(data->screen, pixelX, pixelY, 0x00FFFFFF);
	}
	return (distance);
}

void	cast_all_rays(t_data *data)
{
	float		fov = 90;
	float		ray_angle = data->player.angle - (fov * M_PI / 180) / 2;

	float		increment = (fov * M_PI / 180) / WIN_WIDTH;

	float 		distance;

	for (int i = 0; i < WIN_WIDTH; i++)
	{
		distance = cast_ray(data, ray_angle);
		// draw_line
		// for (int j = distance / 2; j < distance * 2; j++)
		// {
		// 	mlx_put_pixel(data->screen, i, j + WIN_HEIGHT / 2, 0xFFFFFFFF);
		// }
		ray_angle += increment;
	}
}
