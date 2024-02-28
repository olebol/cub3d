/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:47:57 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 18:19:26 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "errors.h"
#include "libft.h"

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}	t_texture;

int		ft_atoi(const char *str)
{
	int		sign;
	int		res;
	int		i;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	res = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

// String to RGBA
static uint32_t		str_to_rgba(char *str)
{
	size_t		i;
	size_t		len;
	uint32_t	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		len = 0;

		// Get the length of the number
		while (str[len + i] && ft_isdigit(str[len + i]))
			len++;

		// Check the length of the number and the separator
		// if (len > 3 || len == 0 || (str[len + i] != ',' && str[len + i] != '\0'))
		// 	error(E_ELEM_RGB);

		num = num * 256 + ft_atoi(str + i);

		i += len + 1;
	}

	return (num);
}

static void		set_element(t_elements *elements, char *str)
{
	char	**parts = ft_split(str, ' ');
	char	*id = parts[0];
	char	*value = parts[1];

	// Check the value

	if (ft_strcmp(id, "NO") == 0)
		elements->textures[NORTH] = mlx_load_png(value);
	else if (ft_strcmp(id, "SO") == 0)
		elements->textures[SOUTH] = mlx_load_png(value);
	else if (ft_strcmp(id, "WE") == 0)
		elements->textures[WEST] = mlx_load_png(value);
	else if (ft_strcmp(id, "EA") == 0)
		elements->textures[EAST] = mlx_load_png(value);
	else if (ft_strcmp(id, "F") == 0)
		elements->floor = str_to_rgba(value);
	else if (ft_strcmp(id, "C") == 0)
		elements->ceiling = str_to_rgba(value);
	else
		error(E_ELEM_ID);

	ft_free_str_arr(parts);
}

size_t	parse_elements(t_elements *elements, char *str)
{
	size_t		loops;
	size_t		i;
	int			start;
	char		*current;

	i = 0;
	loops = 0;
	while (str[i] && loops < 6)
	{
		// Skip spaces
		start = i;
		while (str[start] && (str[start] == ' ' || str[start] == '\t'))
			start++;

		// Get the length of the str
		i = start;
		while (str[i] && str[i] != '\n')
			i++;

		// Get the substring and process the element
		current = ft_substr(str, start, i - start);
		set_element(elements, current);
		free(current);

		i++;
		loops++;
	}

	// Check if all elements are loaded
	// if (loops < 6)
	// 	error(E_ELEM_MISS);

	// if (elements->textures[NORTH] == NULL || elements->textures[SOUTH] == NULL ||
	// 	elements->textures[WEST] == NULL || elements->textures[EAST] == NULL)
	// 	error(E_ELEM_VALUE);

	return (i);
}
