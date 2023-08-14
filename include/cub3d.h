/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:43 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 21:01:50 by opelser       ########   odam.nl         */
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


void		parse_map(char *map_file, t_map *map);

void		draw_map(t_data *data);


#endif