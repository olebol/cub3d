/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:23:02 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/29 14:34:08 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void is_closed(char *temp_map[], int x, int y, t_map *map)
{
	if (temp_map[y][x] == 'x' || temp_map[y][x] == '1')
		return ;
	if (x == 0 || y == 0 || x == map->width || y == map->height || temp_map[y][x] == ' ')
	{
		printf("x: %d, y: %d, temp_map[y][x]: %c\n", x, y, temp_map[y][x]);
		print_map(temp_map);
		printf("\n");
		fatal("Map is not closed\n");
	}
	temp_map[y][x] = 'x';
	check_closed_walls(temp_map, x, y, map);
}

void	check_closed_walls(char *temp_map[], int x, int y, t_map *map) // temp_map
{
	is_closed(temp_map, x + 1, y, map);
	is_closed(temp_map, x - 1, y, map);
	is_closed(temp_map, x, y + 1, map);
	is_closed(temp_map, x, y - 1, map);
	is_closed(temp_map, x + 1, y + 1, map);
	is_closed(temp_map, x - 1, y - 1, map);
	is_closed(temp_map, x + 1, y - 1, map);
	is_closed(temp_map, x - 1, y + 1, map);
}

void	start_wall_check(char *temp_map[], t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (temp_map[y])
	{
		while (temp_map[y][x])
		{
			// char orig = temp_map[y][x];
			// temp_map[y][x] = 'q';	
			// print_map(temp_map);
			// printf("\n");
			// temp_map[y][x] = orig;
			if (temp_map[y][x] == '0')
				is_closed(temp_map, x, y, map);
			x++;
		}
		x = 0;
		y++;
	}
}

void	copy_map_to_array(t_map *map, char *line, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] && i < len)
	{
		if (line[i] == '\n' && k == map->width)
		{
			k = 0;
			j++;
		}
		else if (line[i] == '\n' && k < map->width)
		{
			while (k < map->width)
			{
				map->map[j][k] = ' ';
				k++;
			}
			k = 0;
			j++;
		}
		else
		{
			map->map[j][k] = line[i];
			k++;
		}
		i++;
	}
}

bool	end_of_map(char *map, int i) // same als skip_empty, maar dan voor de map :((
{
	while (map[i])
	{
		if (map[i] != '\n' && map[i] != ' ' && map[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	check_map(char *line, t_map *map)
{
	int	i;
	int	player;
	int	width;

	i = 0;
	player = 0;
	width = 0;
	map->width = 0;
	map->height = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			map->x = width; // wrm -1
			map->y = map->height;
			map->dir = line[i];
			line[i] = '0';
			player++; // ?? kan ook andere check hiervoor doen maar ok
		}
		else if (line[i] == '\n')
		{
			// printf(" width: %d\n", width);
			if (line[i - 1] && line[i - 1] == '\n')
				break ;
			if (width == 0 && end_of_map(line, i) == false)
				fatal("Invalid map\n"); // line of zo
			else if (width == 0 && end_of_map(line, i) == true)
				break ;
			map->height++;
			if (width > map->width)
			{
				// printf("\n>>>>\n\n");
				map->width = width;
			}
			width = -1;
		}
		else if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != ' ')
		{
			if (i == 0)
				fatal("Garbage before map\n"); // line of zo
			fatal("Invalid character in map\n"); // line of zo
		}
		// printf("i: %d, width: %d, char: %c\n", i, width, line[i]);
		width++;
		i++;
	}
	if (line[i] == '\0' && width > 0)
		map->height++;
	if (width > map->width)
		map->width = width;
	if (player != 1)
		fatal("Invalid number of players\n"); // line of zo
	return (i);
}