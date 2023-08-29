/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declarations.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 20:59:57 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/29 18:08:42 by evan-der      ########   odam.nl         */
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
# define LEN_ID 2


typedef enum	e_elem
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	ELEM_COUNT,
}				t_elem;

// typedef enum e_return
// {
// 	SUCCESS,
// 	ERR_ARGC,
// 	ERR_EXTENSION,
// 	ERR_OPEN,
// 	ERR_MALLOC,
// 	ERR_READ,
// 	ERR_MAP,
// 	ERR_ID,
// 	ERR_ELEM_FORMAT,
// 	ERR_GARBAGE,
// 	ERR_ELEMENTS,
// 	ERR_TEXTURES,
// 	ERR_COLOR,
// 	ERR_RESOLUTION,
// 	ERR_PLAYER,
// }				t_return;


typedef struct	s_map
{
	char		**map;			// char array of map
	mlx_image_t	*minimap;		// image of minimap

	int			width;			// width of map
	int			height;			// height of map
	
	int			x;				// player x position
	int			y;				// player y
	char		dir;			// player direction
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
