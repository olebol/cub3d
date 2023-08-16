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

static void	draw_square(t_map *map, int x, int y, unsigned int color)
{
	int				i = 0;
	int				j = 0;
	const int		tileSize = map->tileSize;

	x *= tileSize;
	y *= tileSize;
	while (i < tileSize - 1)
	{
		j = 0;
		while (j < tileSize - 1)
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
	t_map		*map = &data->map;

	data->map.minimap = mlx_new_image(data->mlx, \
				data->map.width * data->map.tileSize, \
				data->map.height * data->map.tileSize);
	if (!data->map.minimap)
		ft_error("Error\nFailed to create minimap image\n");

	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '1')
				draw_square(&data->map, x, y, 0xC6E2E9FF);
			else if (map->map[y][x] == '0')
				draw_square(&data->map, x, y, 0xF8DF81FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, map->minimap, 0, 0);
}
