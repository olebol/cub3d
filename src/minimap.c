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

#include "cub3d.h"

// Draw the player on the minimap
static void	draw_player(t_data *data)
{
	int		start_pos = (data->map.minimap_size / 2 - 2);
	int 	colour = 0xFF0000FF; // red

	// Draw player dot
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			mlx_put_pixel(data->screen, i + start_pos, j + start_pos, colour);

	// Draw player direction line
	for (int i = 0; i < 10; i++)
		mlx_put_pixel(data->screen, \
					start_pos + 2 + (data->player.delta_x * i), \
					start_pos + 2 + (data->player.delta_y * i), \
					colour);
}

// Draw a single map tile
void	draw_map_tile(t_data *data, double x, double y, int screen_x, int screen_y)
{
	unsigned int			color;

	if (is_wall(data, x, y) == true)
		color = 0x00FF00FF; // green
	else
		color = 0x0000FFFF; // blue
	mlx_put_pixel(data->screen, screen_x, screen_y, color);
}

// Check if a given coordinate is within the map limits
bool	is_within_map(t_data *data, double x, double y)
{	if (x >= 0 && x < (double) data->map.width
		&& y >= 0 && y < (double) data->map.height)
		return (true);
	return (false);
}

// Draw the map surrounding the player
void	draw_map(t_data *data)
{
	// Minimap size in pixels
	const int		minimap_size = data->map.minimap_size;

	// Minimap tile size in pixels
	const int		tile_size = data->map.tile_size;

	// Minimap top left corner position
	const double	offset_x = data->player.x - (minimap_size / tile_size / 2);
	const double	offset_y = data->player.y - (minimap_size / tile_size / 2);

	// Draw map tiles
	for (int x = 0; x < minimap_size; x++)
	{
		for (int y = 0; y < minimap_size; y++)
		{
			if (is_within_map(data, offset_x + ((double) x / tile_size), \
									offset_y + ((double) y / tile_size)) == false)
				mlx_put_pixel(data->screen, x, y, 0x000000FF); // black
			else
				draw_map_tile(data, offset_x + ((double) x / tile_size), \
									offset_y + ((double) y / tile_size), x, y);
		}
	}
	draw_player(data);
}
