/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:21:48 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/28 16:29:45 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "errors.h"

t_tile		get_tile_type(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (EMPTY);

	return (map->map[(int) y][(int) x]);
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
