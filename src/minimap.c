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

void	draw_map(t_data *data)
{
	t_map		*map = &data->map;
	t_player	*player = &data->player;
	int			screenX = player->x - map->minimapSize / 2;
	int			screenY = player->y - map->minimapSize / 2;

	// Draw the map surrounding the player
	for (int i = 0; i < map->minimapSize; i++)
	{
		int		mapX = (screenX + i) / map->tileSize;
		for (int j = 0; j < map->minimapSize; j++)
		{
			int		mapY = (screenY + j) / map->tileSize;
			if (mapX >= 0 && mapX < map->width && mapY >= 0 && mapY < map->height)
			{
				if (map->map[mapY][mapX] == '1')
					mlx_put_pixel(data->screen, i, j, 0x00FF00FF);
				else if (map->map[mapY][mapX] == '0')
					mlx_put_pixel(data->screen, i, j, 0x0000FFFF);
				else
					mlx_put_pixel(data->screen, i, j, 0x000000FF);
			}
		}
	}
}
