/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:42:50 by evalieve          #+#    #+#             */
/*   Updated: 2024/03/01 17:19:58 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

#include <fcntl.h>
#include <math.h>

// Find better place for this function
static bool	locate_player(t_data *data, char **map)
{
	int		x;
	int		y;
	bool	player_found;

	player_found = false;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'W' || map[y][x] == 'E')
			{
				if (player_found == true)
					error(E_PLAYER_DUP);
				player_found = true;

				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				data->player.fov = 90 * (M_PI / 180);
				data->player.vec = get_vector(0); // change this to the correct angle

				map[y][x] = '0';
			}
			x++;
		}
		y++;
	}

	return (player_found);
}

static char		*read_file(const char *filename)
{
	const int	fd = open(filename, O_RDONLY, 0);
	char		*filestr;
	char		*line;

	if (is_valid_extension(filename, MAP_EXTENSION) == false)
		error(E_FILE_EXTENSION);

	if (fd < 0)
		error(E_FILE);

	filestr = NULL;
	while (get_line(fd, &line) == GNL_SUCCESS)
	{
		filestr = ft_strjoin_replace(filestr, line);
		free(line);
	}
	return (filestr);
}

void	parse_file(t_data *data, const char *filename)
{
	char		*content;
	size_t		map_start;

	content = read_file(filename);

	map_start = parse_elements(&data->elements, content);
	parse_map(&data->map, content + map_start);
	validate_map(&data->map);

	if (locate_player(data, data->map.map) == false)
		error(E_PLAYER_NO);

	free(content);
}
