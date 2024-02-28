/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:42:50 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/28 15:44:30 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

static ssize_t		ft_read_cubed(int fd, void *buf, size_t count)
{
	ssize_t		ret;

	ret = read(fd, buf, count);
	if (ret == -1)
		error(E_READ);

	return (ret);
}

static char		*read_file(const char *filename)
{
	const int	fd = open(filename, O_RDONLY, 0);
	char		*content;
	char		*temp;
	char		*buf;

	if (fd < 0)
		error(E_FILE);

	content = (char *) ft_malloc(1 * sizeof(char));
	content[0] = '\0';
	buf = (char *)ft_malloc((BUF_SIZE + 1) * sizeof(char));
	buf[BUF_SIZE] = '\0';
	while (ft_read_cubed(fd, buf, BUF_SIZE) > 0)
	{
		temp = ft_strjoin(content, buf); // malloc handling!
		free(content);
		content = temp;
	}
	free(buf);
	close(fd);
	return (content);
}

static bool		is_valid_extension(const char *file)
{
	const size_t	fn_len = ft_strlen(file);

	if (fn_len < EXTENSION_LEN + 1 ||
		ft_strncmp(&file[fn_len - EXTENSION_LEN], EXTENSION, EXTENSION_LEN))
	{
		return (false);
	}

	return (true);
}

static bool	locate_player(t_data *data, char **map)
{
	int		i;
	int		j;
	bool	player_found;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (player_found == true)
					error(E_PLAYER_DUP);
				player_found = true;

				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				data->player.vec = get_vector(0); // change this to the correct angle

				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}

	return (player_found);
}

void	parse_file(t_data *data, const char *file)
{
	char		*content;
	size_t		map_start;

	if (is_valid_extension(file) == false)
		error(E_EXTENSION);

	content = read_file(file);

	map_start = parse_elementss(&data->elements, content);
	parse_map(&data->map, content + map_start);
	validate_map(&data->map);

	if (locate_player(data, data->map.map) == false)
		error(E_NO_PLAYER);

	free(content);
}
