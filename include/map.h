/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:41:51 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 22:52:00 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef enum MAP_TILE
{
	EMPTY = 0,
	FLOOR = '1',
	WALL = '2',
}	t_map_tile;

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

void		parse_map(char *map_file, t_map *map);
t_map_tile	get_wall_type(t_map *map, double x, double y);

#endif