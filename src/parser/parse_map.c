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

#include <stdlib.h>

static size_t	parse_map_width(const char *map)
{
	size_t	i;
	size_t	longest;
	size_t	current;

	i = 0;
	longest = 0;
	current = 0;
	while (map[i])
	{
		if (map[i] == '\n')
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

static size_t	parse_map_height(const char *map)
{
	size_t	i;
	size_t	height;

	i = 0;
	height = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			height++;
		i++;
	}
	return (height + 1);
}

static char		*trim_map(const char *map)
{
	size_t	i;
	size_t	start;
	char	*tmp_map;

	i = 0;
	start = 0;
	while (map[i] && (map[i] == '\n' || map[i] == ' ' || map[i] == '\t'))
		i++;
	start = i;
	while (start > 0)
	{
		if (map[start - 1] == '\n')
			break ;
		start--;
	}
	while (map[i] && map[i + 1])
		i++;
	while (i > start && (map[i] == '\n' || map[i] == ' ' || map[i] == '\t'))
		i--;
	while (map[i] && map[i] != '\n')
		i++;
	tmp_map = (char *) ft_malloc((i - start + 1) * sizeof(char));
	ft_strlcpy(tmp_map, &map[start], i - start + 1);
	return (tmp_map);
}

#include <stdio.h>

// Parse a map given as a string and fill the t_map struct including a 2d array representation of the map
void		parse_map(t_map *map, const char *content)
{
	const char	*map_string = trim_map(content);
	const int	map_len = ft_strlen(map_string);
	int			i;
	int			y;
	int			x;

	map->height = parse_map_height(map_string);
	map->width = parse_map_width(map_string);
	
	map->map = (char **) ft_malloc((map->height + 1) * sizeof(char *));
	map->map[map->height] = NULL;

	y = 0;
	while (y < map->height)
	{
		map->map[y] = (char *) ft_malloc((map->width + 1) * sizeof(char));
		map->map[y][map->width] = '\0';
		y++;
	}

	i = 0;
	x = 0;
	y = 0;
	while (i <= map_len)
	{
		if (map_string[i] == '\n' || map_string[i] == '\0')
		{
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
			map->map[y][x] = map_string[i];
			x++;
		}

		i++;
	}
}