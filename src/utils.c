/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:21:48 by evalieve          #+#    #+#             */
/*   Updated: 2024/06/03 17:30:17 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "errors.h"
#include "libft.h"

t_tile	get_tile_type(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (EMPTY);
	return (map->map[(int) y][(int) x]);
}

void		set_tile_type(t_map *map, double x, double y, t_tile type)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		error(E_MAP_BOUNDS);

	map->map[(int) y][(int) x] = type;
}

// Malloc with exit on fail
void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error(E_MALLOC);
	return (ptr);
}

bool	is_valid_extension(const char *file, const char *extension)
{
	const size_t	fn_len = ft_strlen(file);
	const size_t	ext_len = ft_strlen(extension);

	if (fn_len < ext_len + 1)
		return (false);
	if (ft_strncmp(file + (fn_len - ext_len), extension, ext_len))
		return (false);
	return (true);
}
