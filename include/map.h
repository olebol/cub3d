/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:41:51 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 16:42:14 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define VALID_MAP_CHARS " 0123NSEW&"

typedef enum map_tile_type
{
	EMPTY = ' ',
	FLOOR = '0',
	WALL = '1',
	CLOSED_DOOR = '2',
	OPEN_DOOR = '3',
}	t_tile;

/**
 * @brief struct for map
 * 
 * @param **map char array of map
 * 
 * @param width width of map
 * @param height height of map
 * 
 * @param tile_size size of tile for minimap
 * @param minimap_size width of minimap
 */
typedef struct s_map
{
	char			**map;

	int				width;
	int				height;
}					t_map;

void		parse_map(t_map *map, const char *content);

void		validate_map(t_map *map);

#endif