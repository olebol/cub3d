/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:19:35 by opelser           #+#    #+#             */
/*   Updated: 2024/06/04 23:13:26 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

// Forward declaration
typedef struct s_ray_data		t_ray_data;
typedef struct s_map			t_map;
typedef struct s_data			t_data;

typedef struct s_sprite_draw_data
{
	uint32_t	*pixels;

	int			screen_x;

	int			height;
	int			width;

	int			start_x;
	int			end_x;

	int			start_y;
	int			end_y;

	double		distance;

	double		step;
}			t_sprite_draw_data;

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
typedef struct s_sprite			t_sprite;

struct s_sprite
{
	mlx_texture_t	*texture;

	double			x;
	double			y;

	double			distance_x;
	double			distance_y;

	int				screen_x;
	double			distance;

	int				width;
	
	int				frames;
	int				current_frame;

	t_sprite		*next;
};

void		draw_sprite(t_data *data, t_ray_data **rays, t_sprite *sprite);

void		sprites(t_data *data, t_ray_data **rays);

void		find_sprites(t_map *map, t_data *data);

#endif