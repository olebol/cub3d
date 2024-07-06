/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:28:28 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 16:16:53 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include "map.h"

/**
 * @brief Returns the type of tile at the given coordinates
 * 
 * @param map 			map to get retrieve the tile type from
 * @param x 			x coordinate
 * @param y 			y coordinate
*/
t_tile		get_tile_type(t_map *map, double x, double y);

/**
 * @brief Sets the type of tile at the given coordinates
 * 
 * @param map 			map to set the tile type in
 * @param x 			x coordinate
 * @param y 			y coordinate
 * @param type 			type of tile to set
*/
void		set_tile_type(t_map *map, double x, double y, t_tile type);

/**
 * @brief Attempts to malloc size bytes and calls error with E_MALLOC on fail
 * 
 * @param size 			bytes of memory to allocate
*/
void		*ft_malloc(size_t size);

/**
 * @brief Checks if the file has the given extension
 * 
 * @param file 			file to check
 * @param extension 	extension to check for
 * 
 * @return true if the file has the given extension, false otherwise
*/
bool		is_valid_extension(const char *file, const char *extension);

#endif