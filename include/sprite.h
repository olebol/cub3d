/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:19:35 by opelser           #+#    #+#             */
/*   Updated: 2024/03/28 15:44:16 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

// Forward declaration
typedef struct s_ray_data t_ray_data;
typedef struct s_map t_map;
typedef struct s_data t_data;

/**
 * @brief Structure to store sprite data
 * 
 * @param texture 		Pointer to the texture of the sprite
 * 
 * @param x 			X coordinate of the sprite
 * @param y 			Y coordinate of the sprite
 * 
 * @param distance_x 	Distance from the player to the sprite on the x axis
 * @param distance_y 	Distance from the player to the sprite on the y axis
 * 
 * @param next 			Pointer to the next sprite
*/
typedef struct	s_sprite t_sprite;

struct s_sprite
{
	mlx_texture_t		*texture;

	double			x;
	double			y;
	
	double			distance_x;
	double			distance_y;

	t_sprite		*next;
};

void		sprites(t_data *data, t_ray_data *ray_data);

void		find_sprites(t_map *map, t_data *data);

#endif