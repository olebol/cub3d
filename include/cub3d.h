/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:43 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 21:31:34 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
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
t_map_tile	get_wall_type(t_data *data, double x, double y);

#endif