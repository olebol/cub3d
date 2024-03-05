/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:43 by opelser           #+#    #+#             */
/*   Updated: 2024/03/05 16:14:55 by opelser          ###   ########.fr       */
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

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define MAP_EXTENSION ".cub"

/**
 * @brief struct for player
 * 
 * @param x			player position X
 * @param y			player position Y
 * @param fov		player field of view in radians
 * @param vec		player direction vector
 */
typedef struct s_player
{
	double			x;
	double			y;

	double			fov;
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
}					t_data;

// Init
void		init(t_data *data, const char *filename);

// Minimap
void		draw_minimap(t_data *data);

// Loop
void		captainhook(void *data);

// Casting
void		draw_world(t_data *data);

// Parsing
void		parse_file(t_data *data, const char *filename);

#endif