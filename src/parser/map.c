/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:41:54 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 16:02:46 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	validate_elements_map(const char *map, t_data *data)
{
	size_t	i;
	size_t	j;
	int		special_id[4] = {0, 0, 0, 0};
	char	special_chars[] = {'N', 'S', 'W', 'E'};

	i = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
		{
			j = 0;
			while (j < 4)
			{
				if (map[i] == special_chars[j])
				{
					if (special_id[0] == 1 || special_id[1] == 1 || \
							special_id[2] == 1 || special_id[3] == 1)
						return (set_error(data, E_PLAYER_DUP));
					special_id[j] = 1;
				}
				j++;
			}
		}
		else if (map[i] != ' ' && map[i] != '1' && map[i] != '0' && map[i] != '\n')
			return (set_error(data, E_INVALID_MAP));
		i++;
	}
	if (special_id[0] == 0 && special_id[1] == 0 && special_id[2] == 0 && special_id[3] == 0)
		return (set_error(data, E_NO_PLAYER));
	return (E_SUCCESS);
}

char	**set_map(const char *content, int width, int height)
{
	char	**map;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	map = (char **)ft_malloc((height + 1) * sizeof(char *));
	map[height] = NULL;
	map[i] = (char *)ft_malloc((width + 1) * sizeof(char));
	map[i][width] = '\0';
	while (content[i])
	{
		if (content[i] == '\n')
		{
			while (k < width)
			{
				map[j][k] = ' ';
				k++;
			}
			j++;
			if (j < height)
			{
				map[j] = (char *)ft_malloc((width + 1) * sizeof(char));
				map[j][width] = '\0';
			}
			
			k = 0;
		}	
		else
		{
			map[j][k] = content[i];
			k++;
		}
		i++;
	}
	if (k < width)
	{
		while (k < width)
		{
			map[j][k] = ' ';
			k++;
		}
	}
	return (map);
}

void	locate_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' || \
				data->map.map[i][j] == 'W' || data->map.map[i][j] == 'E')
			{
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				get_vector(data->map.map[i][j]);
				data->map.map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}

}

int	verify_map(const char *content, t_data *data, size_t *pos)
{
	char	*tmp_map;

	tmp_map = trim_map(&content[*pos]);
	// checken of map bestaat
	if (validate_elements_map(tmp_map, data) != E_SUCCESS)
		return (data->e_code);
	data->map.width = width_map(tmp_map);
	data->map.height = height_map(tmp_map);
	data->map.map = set_map(tmp_map, data->map.width, data->map.height);
	if (validate_structure_map(data) != E_SUCCESS)
		return (data->e_code);
	return (E_SUCCESS);
}