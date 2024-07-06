/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_doors.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 23:02:21 by opelser       #+#    #+#                 */
/*   Updated: 2024/07/06 16:07:39 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdbool.h>

static bool	is_valid_door(t_map *map, int x, int y)
{
	if (map->map[y][x] == CLOSED_DOOR || map->map[y][x] == OPEN_DOOR)
	{
		if ((map->map[y][x + 1] != WALL || map->map[y][x - 1] != WALL) \
			&& (map->map[y + 1][x] != WALL || map->map[y - 1][x] != WALL))
			return (false);
		if (map->map[y][x + 1] == OPEN_DOOR \
			|| map->map[y][x - 1] == OPEN_DOOR \
			|| map->map[y + 1][x] == OPEN_DOOR \
			|| map->map[y - 1][x] == OPEN_DOOR)
			return (false);
		if (map->map[y][x + 1] == CLOSED_DOOR \
			|| map->map[y][x - 1] == CLOSED_DOOR \
			|| map->map[y + 1][x] == CLOSED_DOOR \
			|| map->map[y - 1][x] == CLOSED_DOOR)
			return (false);
	}
	return (true);
}

bool	are_doors_valid(t_map *map)
{
	int			y;
	int			x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_valid_door(map, x, y) == false)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
