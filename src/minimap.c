/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:49:13 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 18:13:06 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_square(char **map, int x, int y, int color)
{
	int			i = 0;
	int			j = 0;

	while (i < 10)
	{
		while (j < 10)
		{
			my_mlx_pixel_put(map, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(char **map)
{
	int			x = 0;
	int			y = 0;

	while (map[x][y])
	{
		while (map[x][y])
		{
			if (map[x][y] == '1')
				draw_square(x, y, 0x00FF00);
			else if (map[x][y] == '0')
				draw_square(x, y, 0x000000);
			x++;
		}
		y++;
	}
}
