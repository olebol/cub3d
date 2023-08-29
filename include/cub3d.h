/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:43 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/29 18:18:31 by evan-der      ########   odam.nl         */
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
bool	extension_check(char *infile);
void	split_elements_and_map(char *line, t_textures *textures, t_map *map);
char	*file_to_str(int fd);
bool	is_valid_rgb(int value);
int parse_rgb_component(char *str, int *comp);
unsigned int	str_to_rgb(char *str);
char	*strip_path(char *line);
int	get_path_len(char *line);
int	len_path(char *line);
int	skip_empty(char *line, int i);
int	skip_chars(char *line, int i, char *c);
int	check_map(char *line, t_map *map);
bool	end_of_map(char *map, int i);
void	copy_map_to_array(t_map *map, char *line, int len);
int	get_elements(char *line, t_textures *textures);
int path_textures_to_struct(char *line, char *surface, t_textures *textures, int id_len);
bool	all_elements_found(int *tracker);
char **copy_map(t_map *map);
void is_closed(char *temp_map[], int x, int y, t_map *map);
void	check_closed_walls(char *temp_map[], int x, int y, t_map *map);
void	start_wall_check(char *temp_map[], t_map *map);
const char	*elements(t_elem elem);

// VISUALIZATION UTILS
void		draw_map(t_data *data);

// ERROR UTILS
void	fatal(char *error);
void	fatal_perror(char *error);


void	print_map(char **map);
#endif