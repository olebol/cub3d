/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:01:40 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 14:42:02 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include "utils.h"
#include "errors.h"

#include <stdlib.h>

static size_t	get_map_width(const char *map_str)
{
	const size_t	map_len = ft_strlen(map_str);
	size_t			longest;
	size_t			current;
	size_t			i;

	if (!map_str || map_len == 0)
		return (0);

	i = 0;
	longest = 0;
	current = 0;
	while (i <= map_len)
	{
		if (map_str[i] == '\n' || map_str[i] == '\0')
		{
			if (current > longest)
				longest = current;
			current = 0;
		}
		else
			current++;

		i++;
	}
	return (longest);
}

static size_t	get_map_height(const char *map_str)
{
	size_t	i;
	size_t	height;

	if (!map_str || map_str[0] == '\0')
		return (0);

	i = 0;
	height = 0;
	while (map_str[i])
	{
		if (map_str[i] == '\n')
			height++;
		i++;
	}
	return (height + 1);
}

static void		fill_map(t_map *map, const char *map_str)
{
	const int	map_len = ft_strlen(map_str);
	int			i;
	int			y;
	int			x;

	i = 0;
	x = 0;
	y = 0;
	while (i <= map_len)
	{
		if (map_str[i] == '\n' || map_str[i] == '\0')
		{
			// Fill the rest of the line with spaces
			while (x < map->width)
			{
				map->map[y][x] = ' ';
				x++;
			}
			x = 0;
			y++;
		}
		else
		{
			map->map[y][x] = map_str[i];
			x++;
		}

		i++;
	}
}

static char		*trim_map(const char *map)
{
	char		*trimmed;
	size_t		start;
	size_t		end;

	if (map == NULL || map[0] == '\0')
		error(E_MAP_EMPTY);

	// Skip leading whitespace
	start = 0;
	while (map[start] && (map[start] == '\n' || ft_isspace(map[start])))
		start++;

	// Go back to the first character after the newline
	while (start > 0 && map[start - 1] != '\n')
		start--;

	// Find the end of the map
	end = ft_strlen(map);
	while (end > 0 && (map[end] == '\n' || ft_isspace(map[end])))
		end--;

	if (end == 0)
		error(E_MAP_EMPTY);

	// Trim the map
	trimmed = ft_substr(map, start, end - start + 1);
	if (!trimmed)
		error(E_MALLOC);

	return (trimmed);
}

// Parse a map given as a string and fill the t_map struct including a 2d array representation of the map
void		parse_map(t_map *map, const char *file_string)
{
	const char	*map_string = trim_map(file_string);
	int			y;

	map->height = get_map_height(map_string);
	map->width = get_map_width(map_string);

	if (map->height == 0 || map->width == 0)
		error(E_MAP_EMPTY);

	if (map->height < 3 || map->width < 3)
		error(E_MAP_UNCLOSED);

	map->map = (char **) ft_malloc((map->height + 1) * sizeof(char *));
	map->map[map->height] = NULL;

	y = 0;
	while (y < map->height)
	{
		map->map[y] = (char *) ft_malloc((map->width + 1) * sizeof(char));
		map->map[y][map->width] = '\0';
		y++;
	}

	fill_map(map, map_string);

	free((void *) map_string);
}
