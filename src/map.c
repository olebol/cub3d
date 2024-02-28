/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:25:25 by evan-der          #+#    #+#             */
/*   Updated: 2024/02/27 20:29:54 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

t_map_tile		get_wall_type(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (EMPTY);

	return (map->map[(int) y][(int) x]);
}
