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

static void		draw_player_dot(t_data *data, int start_pos, int colour)
{
	int		i;
	int		j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			mlx_put_pixel(data->minimap, \
						start_pos - 2 + i, \
						start_pos - 2 + j, \
						colour);
			j++;
		}
		i++;
	}
}

// Draw the player on the minimap
static void		draw_player(t_data *data, int start_pos, int colour)
{
	int		i;

	// Draw player dot
	draw_player_dot(data, start_pos, colour);

	// Draw player direction line
	i = 0;
	while (i < 10)
	{
		mlx_put_pixel(data->minimap, \
					start_pos + (data->player.dir.x * i), \
					start_pos + (data->player.dir.y * i), \
					colour);
		i++;
	}
}

// Draw a pixel to the map
void	draw_pixel(t_data *data, double x, double y, t_tile tile)
{
	if (tile == EMPTY)
		mlx_put_pixel(data->minimap, x, y, 0x0000003F);
	else if (tile == FLOOR)
		mlx_put_pixel(data->minimap, x, y, 0xFFFFFFFF);
	else if (tile == CLOSED_DOOR)
		mlx_put_pixel(data->minimap, x, y, 0xff000dFF);
	else if (tile == OPEN_DOOR)
		mlx_put_pixel(data->minimap, x, y, 0x57d115FF);
	else
		mlx_put_pixel(data->minimap, x, y, 0xA9A9A9FF);
}

void	fill_map(t_data *data, int tile_size, \
					double map_offset_x, double map_offset_y)
{
	t_tile		tile;
	uint32_t	x;
	uint32_t	y;
	double		map_x;
	double		map_y;

	y = 0;
	while (y < data->minimap->height)
	{
		x = 0;
		while (x < data->minimap->width)
		{
			map_x = map_offset_x + ((float) x / tile_size);
			map_y = map_offset_y + ((float) y / tile_size);

			tile = get_tile_type(&data->map, map_x, map_y);
			draw_pixel(data, x, y, tile);
			x++;
		}
		y++;
	}
}

// Draw the map surrounding the player
void	draw_minimap(t_data *data)
{
	// Minimap size in pixels
	const int		minimap_size = data->minimap->width;

	// Minimap tile size in pixels
	const int		tile_size = 32;

	// Map offset pointing to the top left corner of the minimap
	const double	offset = (float) minimap_size / tile_size / 2;
	const double	map_offset_x = data->player.x - offset;
	const double	map_offset_y = data->player.y - offset;

	// Draw map and player
	fill_map(data, tile_size, map_offset_x, map_offset_y);
	draw_player(data, minimap_size / 2, 0xFF0000FF);
}
