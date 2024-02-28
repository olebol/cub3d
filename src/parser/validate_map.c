/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:41:54 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/28 18:20:46 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include "errors.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>

// Copies one map struct to another
static void		copy_map(t_map *copy, t_map *orig)
{
	const int		height = orig->height;
	int				i;

	copy->map = (char **) ft_malloc((height + 1) * sizeof(char *));
	copy->map[height] = NULL;

	i = 0;
	while (i < height)
	{
		copy->map[i] = ft_strdup(orig->map[i]);

		if (copy->map[i] == NULL)
			error(E_MALLOC);

		i++;
	}
}

static bool		is_closed(t_map *map, int x, int y)
{
	if (map->map[y][x] == 'x' || map->map[y][x] == '1')
		return (true);

	if (x == 0 || y == 0 ||
		x == map->width - 1 || y == map->height - 1 ||
		map->map[y][x] == ' ')
	{
		return (false);
	}

	// Mark square as visited
	map->map[y][x] = 'x';

	// Check all 8 surrounding directions
	is_closed(map, x + 1, y);
	is_closed(map, x - 1, y);
	is_closed(map, x, y + 1);
	is_closed(map, x, y - 1);
	is_closed(map, x + 1, y + 1);
	is_closed(map, x - 1, y - 1);
	is_closed(map, x + 1, y - 1);
	is_closed(map, x - 1, y + 1);

	return (true);
}

static		bool	is_map_closed(t_map *map)
{
	t_map		copy;
	size_t		x;
	size_t		y;

	copy_map(&copy, map);

	y = 0;
	while (copy.map[y])
	{
		x = 0;
		while (copy.map[y][x])
		{
			if (copy.map[y][x] == '0' && is_closed(&copy, x, y) == false)
			{
				ft_free_str_arr(copy.map);
				return (false);
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
			if (map->map[y][x] != EMPTY && map->map[y][x] != WALL && map->map[y][x] != FLOOR && map->map[y][x] != '\n' &&
				map->map[y][x] != 'N' && map->map[y][x] != 'E' && map->map[y][x] != 'S' && map->map[y][x] != 'W')
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