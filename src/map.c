/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:25:25 by evan-der          #+#    #+#             */
/*   Updated: 2024/02/26 22:53:52 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	copy_map_to_array(t_map *map, char *line)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			j++;
			k = 0;
		}
		else
		{
			map->map[j][k] = line[i];
			k++;
		}
		i++;
	}
}

int		map_height(char *line)
{
	uint32_t	height;
	uint32_t	i;

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

int		map_width(char *line)
{
	uint32_t	width;

	width = 0;
	while (line[width] != '\n' && line[width] != '\0')
		width++;
	return (width);
}

char	*copy_line(int fd) // get_next_line style
{
	char	*line;
	char	*temp;
	int		ret;

	line = (char *) malloc(1 * sizeof(char));
	if (!line)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}
	line[0] = '\0';
	temp = (char *) malloc(2 * sizeof(char));
	if (!temp)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}
	temp[1] = '\0';
	ret = read(fd, temp, 1);
	while (ret > 0)
	{
		if (ret == -1)
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Read failed\n", 2);
			exit(1);
		}
		line = ft_strjoin_replace(line, temp);
		ret = read(fd, temp, 1);
	}
	free(temp);
	return (line);
}

void	parse_map(char *map_file, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Could not open file\n", 2);
		exit(1);
	}
	line = copy_line(fd);

	map->width = map_width(line);
	map->height = map_height(line);

	map->map = (char **) malloc((map->height + 1) * sizeof(char *));
	if (!map->map)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}

	map->map[map->height] = NULL;
	while (i < map->height)
	{
		map->map[i] = (char *) malloc((map->width + 1) * sizeof(char));
		if (!map->map[i])
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Malloc failed\n", 2);
			exit(1);
		}
		map->map[i][map->width] = '\0';
		i++;
	}
	copy_map_to_array(map, line);
	free(line);
	close(fd);
}

t_map_tile		get_wall_type(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (EMPTY);

	return (map->map[(int) y][(int) x]);
}
