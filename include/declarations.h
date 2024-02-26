/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declarations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:59:57 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 22:31:09 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

# include "cub3d.h"
# include "vector.h"

# define WIN_WIDTH 2048
# define WIN_HEIGHT 1024

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

/**
 * @brief struct for player
 * 
 * @param x			player position X
 * @param y			player position Y
 */
typedef struct s_player
{
	double			x;
	double			y;

	t_vector		vec;
}					t_player;

/**
 * @brief struct for mlx
 * 
 * @param *mlx		pointer to mlx struct
 * 
 * @param *screen	pointer to image covering whole screen
 * @param map		map struct
 * @param player	player struct
 */
typedef struct s_data
{
	mlx_t			*mlx;

	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	t_map			map;
	t_player		player;
}					t_data;

#endif
