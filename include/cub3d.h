/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:43 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/16 20:14:38 by evan-der      ########   odam.nl         */
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
# include <fcntl.h>
# include <stdbool.h>

// PARSER UTILS
int	parse_infile(char *infile, t_map *map, t_textures *textures);
char	*file_to_str(int fd);
int	len_path(char *line);
// bool	is_valid_rgb(int value);
char	*strip_path(char *line, int path_len);
int	parse_rgb_component(char *str);
unsigned int	get_rgb_color(char *rgb); // miss even andere naam bedenken
int	path_textures_to_struct(char *line, char *surface, t_textures *textures);
void	get_path_to_textures(char *line, t_textures *textures);
bool	extension_check(char *infile); // bool?


// VISUALIZATION UTILS
void		draw_map(t_data *data);

// ERROR UTILS
void	fatal(char *error);
void	fatal_perror(char *error);

#endif