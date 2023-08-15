/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:49:13 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 20:27:54 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_square(mlx_image_t *minimap, int x, int y, int color)
{
	int			i = 0;
	int			j = 0;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	while (i < TILE_SIZE - 1)
	{
		j = 0;
		while (j < TILE_SIZE - 1)
		{
			mlx_put_pixel(minimap, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int			x = 0;
	int			y = 0;
	char		**map = data->map.map;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(data->map.minimap, x, y, 0xC6E2E9FF);
			else if (map[y][x] == '0')
				draw_square(data->map.minimap, x, y, 0xF8DF81FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->map.minimap, 0, 0);
}
