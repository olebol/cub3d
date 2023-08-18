/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:43 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/18 16:18:12 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"
# include "colors.h"
# include "declarations.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

// Init
int			init_mlx_data(t_data *data);
int			init_player(t_data *data);

// Errors
void		ft_error(char *message);

// Parsing
void		parse_map(char *map_file, t_map *map);

// Minimap
void		draw_map(t_data *data);

// Loop
void		captainhook(void *data);

// Casting
void		cast_all_rays(t_data *data);

// Utils
bool		is_wall(t_data *data, double x, double y);

#endif