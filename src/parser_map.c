/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:23:02 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/23 16:26:30 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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


int map_height(char *line)
{
	size_t	height;
	size_t	i;

	height = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			height++;
		i++;
	}
	if (line[height - 1] != '\n') // even nadenken over hoe de laatste line eruit kan zien en wel of niet meetellen icm input file
		height++;
	return (height);
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