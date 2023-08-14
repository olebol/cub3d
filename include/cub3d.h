/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:43 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 18:33:46 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../lib/MLX/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_map
{
	char	**map;
	int		width;
	int		height;
}				t_map;

void		parse_map(char *map_file, t_map *map);


#endif