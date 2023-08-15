/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declarations.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 20:59:57 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/15 14:29:26 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

# include "cub3d.h"

# define TILE_SIZE 64
# define WIN_WIDTH 1024
# define WIN_HEIGHT 512

typedef struct	s_map
{
	char		**map;			// char array of map
	mlx_image_t	*minimap;		// image of minimap

	int			width;			// width of map
	int			height;			// height of map
}				t_map;

typedef struct	s_data
{
	mlx_t			*mlx;		// mlx struct

	mlx_image_t		*screen;	// image covering whole screen
	t_map			map;		// map struct
}				t_data;

#endif
