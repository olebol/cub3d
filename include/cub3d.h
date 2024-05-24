/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:43 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 16:34:57 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include "vector.h"
# include "map.h"
# include "errors.h"
# include "utils.h"
# include "elements.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define GAME_NAME "cub3D"

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif

# define MAP_EXTENSION ".cub"

/**
 * @brief		Structure to store the data needed for drawing
 * 
 * @param		texture 		Pointer to the texture
 * @param		line_height 	The original height of the wall
 * @param		wall_start 		Starting position of the wall
 * @param		wall_end 		Ending position of the wall
 * @param		tex_x 			Position of the texture on the x axis
 * @param		step 			Step to take on the texture
*/
typedef struct s_draw_data
{
	mlx_texture_t	*texture;

	int				line_height;

	int				wall_start;
	int				wall_end;

	int				tex_x;

	double			step;

}			t_draw_data;

/**
 * @brief struct for player
 * 
 * @param x			player position X
 * @param y			player position Y
 * @param vec		player direction vector
 */
typedef struct s_player
{
	double			x;
	double			y;

	t_vector		cam;
	t_vector		dir;
}					t_player;

/**
 * @brief struct for mlx
 * 
 * @param *mlx		pointer to mlx struct
 * 
 * @param *screen	pointer to image covering whole screen
 * @param *minimap	pointer to image covering minimap
 * @param map		map struct
 * @param player	player struct
 */
typedef struct s_data
{
	mlx_t			*mlx;

	mlx_image_t		*screen;
	mlx_image_t		*minimap;

	t_elements		elements;

	t_map			map;

	t_player		player;

	int				wall_middle;
}					t_data;

// Init
void		init(t_data *data, const char *filename);

// Minimap
void		draw_minimap(t_data *data);

// Loop
void		captainhook(void *data);
void		move_hook(t_data *data);
void		view_hook(t_data *data);
void		mouse_hook(double x, double y, void *dataPointer);

// Drawing world
void		draw_world(t_data *data);

// Parsing
void		parse_file(t_data *data, const char *filename);

#endif