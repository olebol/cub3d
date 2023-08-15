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

void	draw_square(t_data *data, int x, int y, unsigned int color)
{
	int				i = 0;
	int				j = 0;
	const t_map		*map = &data->map;
	const int		tileSize = map->tileSize;

	x *= tileSize;
	y *= tileSize;
	while (i < tileSize - 1 && (x + i < (map->width * tileSize)))
	{
		j = 0;
		while (j < tileSize - 1 && (y + j < (map->height * tileSize)))
		{
			mlx_put_pixel(map->minimap, x + i, y + j, color);
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
				draw_square(data, x, y, 0xC6E2E9FF);
			else if (map[y][x] == '0')
				draw_square(data, x, y, 0xF8DF81FF);
			x++;
		}
		y++;
	}
}
