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

static void	draw_player(t_data *data)
{
	// Draw player dot to image
	int		start_pos = data->map.minimapSize / 2 - 2;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			mlx_put_pixel(data->screen, i + start_pos, j + start_pos, 0xFF6961FF);
}

// Draw a single map tile
void	draw_map_tile(t_data *data, int screenX, int screenY, \
									int arrayX, int arrayY)
{
	if (arrayX >= 0 && arrayX < data->map.width
		&& arrayY >= 0 && arrayY < data->map.height)
	{
		char tile = data->map.map[arrayY][arrayX];
		int color;

		if (tile == '1')
			color = 0x00FF00FF;
		else if (tile == '0')
			color = 0x0000FFFF;
		else
			color = 0x000000FF;

		mlx_put_pixel(data->screen, screenX, screenY, color);
	}
	else
		mlx_put_pixel(data->screen, screenX, screenY, 0x000000FF);
}

// Draw the map surrounding the player
void	draw_map(t_data *data)
{
	const int	minimap_size = data->map.minimapSize;
	const int	tile_size = data->map.tileSize;

	const int	minimap_x = data->player.x - minimap_size / 2;
	const int	minimap_y = data->player.y - minimap_size / 2;

	int			array_x;
	int			array_y;

	for (int i = 0; i < minimap_size; i++)
	{
		array_y = (minimap_y + i) / tile_size;

		for (int j = 0; j < minimap_size; j++)
		{
			array_x = (minimap_x + j) / tile_size;

			// if the screen pixel is outside of map on the top or left
			// 		it should draw a black pixel
			draw_map_tile(data, j, i, array_x, array_y);
		}
	}
	draw_player(data);
}
