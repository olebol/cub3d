/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:25:25 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/14 18:28:51 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>

void	copy_map_to_array(t_map *map, char *line)
{
	size_t	i;
	size_t	j;
	size_t	k;

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
			map->map[j][k] = line[i];
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
		if (line[height] == '\n')
			height++;
		i++;
	}
	if (line[height - 1] != '\n') // even nadenken over hoe de laatste line eruit kan zien en wel of niet meetellen icm input file
		height++;
	return (height);
}

int	map_width(char *line)
{
	size_t	width;

	width = 0;
	while (line[width] != '\n' && line[width] != '\0')
		width++;
	return (width);
}

// size_t	ft_strlen(char *str)
// {
// 	size_t len;

// 	len = 0;
// 	while (str[len])
// 		len++;
// 	return (len);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	j;
// 	size_t	len;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	str = (char *)malloc(len * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i] != '\0' && i < len)
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0' && i < len)
// 	{
// 		str[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	str[i] = '\0';
// 	free(s1);
// 	return (str);
// }

char	*copy_line(int fd) // get_next_line style
{
	char	*line;
	char	*temp;
	int		ret;

	line = (char *)malloc(1 * sizeof(char));
	if (!line)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}
	line[0] = '\0';
	temp = (char *)malloc(2 * sizeof(char));
	if (!temp)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}
	temp[1] = '\0';
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, temp, 1);
		if (ret == -1)
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Read failed\n", 2);
			exit(1);
		}
		line = ft_strjoin(line, temp);
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
	map->x = map_width(line);
	map->y = map_height(line);
	map->map = (char **)malloc((map->y + 1) * sizeof(char *));
	if (!map->map)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}
	map->map[map->y] = NULL;
	while (i < map->y)
	{
		printf("debug\n");
		map->map[i] = (char *)malloc((map->x + 1) * sizeof(char));
		if (!map->map[i])
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Malloc failed\n", 2);
			exit(1);
		}
		map->map[i][map->x] = '\0';
		i++;
	}
	copy_map_to_array(map, line);
	close(fd);
}