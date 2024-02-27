/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:42:03 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 15:33:38 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char **copy_map(char **map, int width, int height)
{
	char	**temp_map;
	int	i;
	int j;

	i = 0;
	j = 0;
	temp_map = (char **)ft_malloc((height + 1) * sizeof(char *));
	temp_map[height] = NULL;
	while (i < height)
	{
		temp_map[i] = (char *)ft_malloc((width + 1) * sizeof(char));
		temp_map[i][width] = '\0';
		i++;
	}
	i = 0;
	while (i < height)
	{
		while (j < width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				temp_map[i][j] = '0';
			else
				temp_map[i][j] = map[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	return (temp_map);
}

size_t	width_map(const char *map)
{
	size_t	i;
	size_t	width;
	size_t	tmp;

	i = 0;
	width = 0;
	tmp = 0;
	while (map[i])
	{
		if (map[i] != '\n')
			tmp++;
		else
		{
			if (width < tmp)
				width = tmp;
			tmp = 0;
		}
		i++;
	}
	return (width);
}

size_t height_map(const char *map)
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

char	*trim_map(const char *map)
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
	tmp_map = (char *)ft_malloc((i - start + 1) * sizeof(char));
	ft_strlcpy(tmp_map, &map[start], i - start + 1);
	return (tmp_map);
}
