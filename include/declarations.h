/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declarations.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 20:59:57 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/17 16:20:15 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

# include "cub3d.h"

# define TILE_SIZE 32
# define WIN_WIDTH 1024
# define WIN_HEIGHT 512

# define EXTENSION_LEN 4
# define EXTENSION ".cub"
# define MAX_ID 6

typedef struct	s_map
{
	char		**map;			// char array of map
	mlx_image_t	*minimap;		// image of minimap

	int			width;			// width of map
	int			height;			// height of map
}				t_map;

typedef struct	s_textures
{
	char		*no;			// north texture
	char		*so;			// south texture
	char		*we;			// west texture
	char		*ea;			// east texture

	// in hexa (unsigned int?)
	unsigned int	f;				// floor texture
	unsigned int	c;				// ceiling texture
}				t_textures;

typedef struct	s_data
{
	mlx_t			*mlx;		// mlx struct

	mlx_image_t		*screen;	// image covering whole screen
	t_map			map;		// map struct
	t_textures		textures;	// textures struct
}				t_data;

#endif
