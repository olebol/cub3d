/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declarations.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 20:59:57 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/16 15:05:24 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

# include "cub3d.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 512


typedef struct		s_map
{
	char			**map;			// char array of map

	int				width;			// width of map
	int				height;			// height of map

	mlx_image_t		*minimap;		// image of minimap
	int				tileSize;		// size of tile for minimap
	int				minimapSize;		// width of minimap
}					t_map;

typedef struct		s_player
{
	mlx_image_t		*img;			// image of player for minimap

	int				x;			// player position X
	int				y;			// player position Y
	int				fov;			// field of view
}					t_player;

typedef struct		s_data
{
	mlx_t			*mlx;			// mlx struct

	mlx_image_t		*screen;		// image covering whole screen
	t_map			map;			// map struct
	t_player		player;			// player struct
}					t_data;

#endif
