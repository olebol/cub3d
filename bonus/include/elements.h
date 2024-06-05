/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:46:05 by opelser           #+#    #+#             */
/*   Updated: 2024/06/03 17:32:14 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "MLX42.h"

# define TEXTURE_FILE_EXTENSION ".png"
# define ELEMENTS_AMOUNT 9

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR_CLOSED,
	DOOR_OPEN,
	SPRITE,
	TEXTURE_AMOUNT
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
	mlx_texture_t	*textures[TEXTURE_AMOUNT];

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

/**
 * @brief Validates the elements
 * 
 * @param elements 	elements struct to validate
 * @param loops 	amount of loops
 * 
 * @return true if the elements are valid, false otherwise
*/
void		validate_elements(t_elements *elements, size_t loops);

/**
 * @brief Flips the color
 * 
 * @param color 		color to flip
 * 
 * @return the flipped color
*/
uint32_t	flip_color(uint32_t color);

/**
 * @brief Flips the texture
 * 
 * @param texture 		texture to flip
*/
void		flip_texture(mlx_texture_t *texture);

#endif