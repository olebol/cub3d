/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_walls.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:52:29 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 15:28:06 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_closed(char *temp_map[], int x, int y, t_data *data)
{
	if (temp_map[y][x] == 'x' || temp_map[y][x] == '1')
		return (E_SUCCESS);
	if (x == 0 || y == 0 || x == data->map.width - 1 || y == data->map.height - 1 || temp_map[y][x] == ' ')
		return (set_error(data, E_UNCLOSED_MAP));//, R_UNCLOSED_MAP));
	temp_map[y][x] = 'x';
	check_closed_walls(temp_map, x, y, data);
	return (E_SUCCESS);
}

int	check_closed_walls(char *temp_map[], int x, int y, t_data *data)
{
	if (is_closed(temp_map, x + 1, y, data) != E_SUCCESS)
		return (data->e_code);
	if (is_closed(temp_map, x - 1, y, data) != E_SUCCESS)
		return (data->e_code);
	if (is_closed(temp_map, x, y + 1, data) != E_SUCCESS)
		return (data->e_code);
	if (is_closed(temp_map, x, y - 1, data) != E_SUCCESS)
		return (data->e_code);
	if (is_closed(temp_map, x + 1, y + 1, data) != E_SUCCESS)
		return (data->e_code);
	if (is_closed(temp_map, x - 1, y - 1, data) != E_SUCCESS)
		return (data->e_code);
	if (is_closed(temp_map, x + 1, y - 1, data) != E_SUCCESS)
		return (data->e_code);
	if (is_closed(temp_map, x - 1, y + 1, data) != E_SUCCESS)
		return (data->e_code);
	return (E_SUCCESS);
}

int	validate_structure_map(t_data *data)
{
	size_t	x;
	size_t	y;
	char	**map;

	x = 0;
	y = 0;
	map = copy_map(data->map.map, data->map.width, data->map.height);
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				is_closed(map, x, y, data);
				if (data->e_code != E_SUCCESS)
					return (data->e_code);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (E_SUCCESS);
}
