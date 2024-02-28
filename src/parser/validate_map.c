/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:41:54 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/28 21:36:27 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include "errors.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>

static bool		check_square(t_map *map, int x, int y)
{
	if (map->map[y][x] == WALL)
		return (true);

	// Edge of the map
	if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1)
		return (false);

	if (map->map[y][x] == EMPTY)
		return (false);

	return (true);
}

static bool		is_closed(t_map *map, int x, int y)
{
	// Check all directions
	if (check_square(map, x, y) == false ||
		check_square(map, x + 1, y) == false ||
		check_square(map, x - 1, y) == false ||
		check_square(map, x, y + 1) == false ||
		check_square(map, x, y - 1) == false ||
		check_square(map, x + 1, y + 1) == false ||
		check_square(map, x + 1, y - 1) == false ||
		check_square(map, x - 1, y + 1) == false ||
		check_square(map, x - 1, y - 1) == false)
		return (false);

	return (true);
}

static bool		is_map_closed(t_map *map)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] != WALL &&
				map->map[y][x] != EMPTY)
			{
				if (is_closed(map, x, y) == false)
				{
					ft_free_str_arr(map->map);
					return (false);
				}
			}
			x++;
		}
		y++;
	}

	return (true);
}

static bool		contains_valid_symbols(t_map *map)
{
	int			y;
	int			x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] != EMPTY &&
				map->map[y][x] != WALL &&
				map->map[y][x] != FLOOR &&
				map->map[y][x] != '\n' &&
				map->map[y][x] != 'N' &&
				map->map[y][x] != 'E' &&
				map->map[y][x] != 'S' &&
				map->map[y][x] != 'W')
			{
				return (false);
			}
			x++;
		}
		y++;
	}

	return (true);
}

void	validate_map(t_map *map)
{
	if (contains_valid_symbols(map) == false)
		error(E_MAP_INVALID);

	if (is_map_closed(map) == false)
		error(E_MAP_UNCLOSED);
}