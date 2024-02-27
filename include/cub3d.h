/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:43 by opelser       #+#    #+#                 */
/*   Updated: 2024/02/27 14:37:33 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include "vector.h"
# include "map.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define GAME_NAME "cub3D"
# define WIN_WIDTH 2048
# define WIN_HEIGHT 1024
# define EXTENSION ".cub"
# define EXTENSION_LEN 4
# define ELEM_COUNT 8
# define ERROR -1
# define BUF_SIZE 1

typedef enum s_return
{
	R_SUCCESS,
	R_ARGC,
	R_MLX_INIT,
	R_EXTENSION,
	R_ELEM_DUP,
	R_ELEM_WRONG,
	R_ELEM_MISS,
	R_RGB,
	R_ELEM_VALUE,
	R_PLAYER_DUP,
	R_INVALID_MAP,
	R_NO_PLAYER,
	R_UNCLOSED_MAP,
}			t_return;

typedef enum s_error
{
	E_SUCCESS,
	E_ARGC,
	E_MLX_INIT,
	E_EXTENSION,
	E_FILE,
	E_ELEM_DUP,
	E_ELEM_WRONG,
	E_ELEM_MISS,
	E_RGB,
	E_ELEM_VALUE,
	E_PLAYER_DUP,
	E_INVALID_MAP,
	E_NO_PLAYER,
	E_UNCLOSED_MAP,
}			t_error;


/**
 * @brief struct for elements
 * 
 * @param no		north texture
 * @param so		south texture
 * @param we		west texture
 * @param ea		east texture
 * 
 * @param f			floor texture
 * @param c			ceiling texture
 * @param rgb_f		floor color
 * @param rgb_c		ceiling color
 */
typedef struct	s_elements
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;

	char		*f;
	char		*c;
	unsigned int	rgb_f;
	unsigned int	rgb_c;
}				t_elements;


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
	t_map			map;
	t_elements		*elements;
	t_player		player;
	// t_return		r_value;
	t_error			e_code;
}					t_data;

// typedef struct	s_data
// {
// 	mlx_t			*mlx;		// mlx struct

// 	mlx_image_t		*screen;	// image covering whole screen
// 	t_map			map;		// map struct
// 	t_textures		textures;	// textures struct
// 	t_return		r_value;	// return value
// 	t_error			e_message;		// error value
// }				t_data;

// Init
void		init_data(t_data *data, char *map_path);
int			init_player(t_data *data);

// Errors
void		ft_error(char *message);

// Minimap
void		draw_minimap(t_data *data);

// Loop
void		captainhook(void *data);

// Casting
void		cast_all_rays(t_data *data);

// Parser
void	*ft_malloc(size_t size);
char	*read_file(int fd);
int	validate_rgb_format(t_data *data, unsigned int *color);
unsigned int	set_rgb_component(char *str, size_t len);
int	check_element_rgb(char *str, t_data *data);
size_t	skip_empty(const char *content, size_t i);
int	check_element_path(char *path, t_data *data);
char	*strip_path(char *line, int start);
bool compare_ids(char *str, char *id);
bool	elements_missing(int *tracker);
int	check_information_elements(t_elements *elements, t_data *data);
size_t set_element(char *content, t_elements *elements, char *id);
int	search_elements(t_elements *elements, t_data *data, char *content, int *tracker, size_t *pos);
int	verify_elements(char *content, t_data *data, size_t *pos);
char **copy_map(char **map, int width, int height);
size_t	width_map(const char *map);
size_t height_map(const char *map);
char	*trim_map(const char *map);
int	is_closed(char *temp_map[], int x, int y, t_data *data);
int	check_closed_walls(char *temp_map[], int x, int y, t_data *data);
int	validate_structure_map(t_data *data);
int	validate_elements_map(const char *map, t_data *data);
char	**set_map(const char *content, int width, int height);
int	verify_map(const char *content, t_data *data, size_t *pos);
int	verify_extension(const char *file, t_data *data);
int	parse_file(const char *file, t_data *data);
char	*read_file(int fd);

// Error
void	fatal(void);
void	free_elems(t_elements *elements);
const char	*error_messages(t_error error);
int	set_error(t_data *data, t_error e_code);//, t_return r_value);
int	error(t_data *data);


#endif