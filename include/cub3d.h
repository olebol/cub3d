/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:43 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 23:01:48 by opelser          ###   ########.fr       */
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

# define WIN_WIDTH 2048
# define WIN_HEIGHT 1024

# define EXTENSION ".cub"
# define EXTENSION_LEN 4

# define ELEM_COUNT 6

# define BUF_SIZE 1

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

	t_vector		vec;
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
void		cast_all_rays(t_data *data);

// Vector
t_vector	get_vector(double angle);

// Parsing
void		parse_file(t_data *data, const char *file);

#endif