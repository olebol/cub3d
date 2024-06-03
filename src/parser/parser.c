/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:42:50 by evalieve          #+#    #+#             */
/*   Updated: 2024/06/03 17:40:37 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "errors.h"
#include "sprite.h"
#include "utils.h"

#include <math.h>
#include <fcntl.h>

static void	set_player(t_player *player, int x, int y, char direction)
{
	double		angle;

	player->x = x + 0.5;
	player->y = y + 0.5;
	angle = 0;
	if (direction == 'E')
		angle = 0;
	else if (direction == 'S')
		angle = M_PI / 2;
	else if (direction == 'W')
		angle = M_PI;
	else if (direction == 'N')
		angle = M_PI * 1.5;
	player->dir = get_vector(angle);
	player->cam = get_vector(angle + (M_PI / 2));
}

// Find better place for this function
static bool	find_player(t_data *data, char **map)
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
			if (ft_strchr("NSEW", map[y][x]) != NULL)
			{
				if (player_found == true)
					error(E_PLAYER_DUP);
				player_found = true;
				set_player(&data->player, x, y, map[y][x]);
				map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (player_found);
}

static char	*read_file(const char *filename)
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
	if (find_player(data, data->map.map) == false)
		error(E_PLAYER_NO);
	find_sprites(&data->map, data);
	free(content);
}
