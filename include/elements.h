/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/27 21:46:05 by opelser       #+#    #+#                 */
/*   Updated: 2024/03/19 18:56:27 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "MLX42.h"

# define TEXTURE_FILE_EXTENSION ".png"

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}			t_texture;

/**
 * @brief struct for elements
 * 
 * @param *textures 		array of pointers to textures of the walls
 * @param floor 			color of the floor
 * @param ceiling 			color of the ceiling
*/
typedef struct s_elements
{
	mlx_texture_t	*textures[4];
	uint32_t		floor;
	uint32_t		ceiling;
}					t_elements;

/**
 * @brief Parses the elements from the given string 
 * 				and sets them in the given elements struct
 * 
 * @param elements 	elements struct to set the parsed elements in
 * @param str 		string to parse the elements from
*/
size_t		parse_elements(t_elements *elements, char *str);

#endif