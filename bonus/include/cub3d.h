/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:43 by opelser           #+#    #+#             */
/*   Updated: 2024/06/03 18:41:06 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"

# include "vector.h"
# include "elements.h"
# include "sprite.h"
# include "map.h"

# define GAME_NAME "cub3D"

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# define MAP_EXTENSION ".cub"

typedef struct s_ray_data	t_ray_data;

/**
 * @brief		Structure to store the data needed for drawing
 * 
 * @param		texture 		Pointer to the texture
 * @param		length 	The original height of the wall
 * @param		start 		Starting position of the wall
 * @param		end 		Ending position of the wall
 * @param		tex_x 			Position of the texture on the x axis
 * @param		step 			Step to take on the texture
*/
typedef struct s_draw_data
{
	mlx_texture_t	*texture;

	int				length;

	int				start;
	int				end;

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
 * @brief struct for storing data required throughout the program
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

	t_sprite		*sprites;

	int				mid;
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
void		door_hook(t_data *data);

// Drawing world
t_draw_data	set_draw_data(t_data *data, t_ray_data *ray);
void		draw_world(t_data *data);

// Parsing
void		parse_file(t_data *data, const char *filename);

#endif