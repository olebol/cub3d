/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:28:28 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 16:29:45 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

/**
 * @brief Returns the type of tile at the given coordinates
 * 
 * @param map 		map to get retrieve the tile type from
 * @param x 		x coordinate
 * @param y 		y coordinate
*/
t_tile	get_tile_type(t_map *map, double x, double y);

/**
 * @brief Attempts to malloc size bytes and calls error with E_MALLOC on fail
 * 
 * @param size 	bytes of memory to allocate
*/
void		*ft_malloc(size_t size);

#endif
