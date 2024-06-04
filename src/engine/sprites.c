/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:18:28 by opelser           #+#    #+#             */
/*   Updated: 2024/06/04 23:15:01 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"
#include "casting.h"

#include <math.h>

static double	get_distance(t_sprite *sprite)
{
	return (pow(sprite->distance_x, 2) + pow(sprite->distance_y, 2));
}

void	sort_sprites(t_sprite **sprites)
{
	t_sprite	*current;
	t_sprite	*prev;
	t_sprite	*next;

	current = *sprites;
	while (current)
	{
		prev = NULL;
		next = current->next;
		while (next)
		{
			if (get_distance(current) < get_distance(next))
			{
				if (prev)
					prev->next = next;
				else
					*sprites = next;

				current->next = next->next;
				next->next = current;
				current = next;
			}

			prev = current;
			current = next;
			next = next->next;
		}

		current = current->next;
	}
}

void	update_frames(t_sprite *sprites)
{
	t_sprite			*current;
	static double		last_time = 0;
	const double		current_time = mlx_get_time();

	if (current_time - last_time < 0.1)
		return ;

	current = sprites;
	while (current)
	{
		current->current_frame++;

		if (current->current_frame >= current->frames)
			current->current_frame = 0;

		current = current->next;
	}

	last_time = current_time;
}

// Something is wrong with the calculations
void	transform_sprite_location(t_data *data, t_sprite *sprite, t_ray_data **rays)
{
	// Variables for readability
	const t_vector		player = data->player.dir;
	const t_vector		cam = data->player.cam;
	const double		distX = sprite->distance_x;
	const double		distY = sprite->distance_y;

	// [ transformX ]              [ dirY      -dirX ]   [ distX ]                                         [ dirY      -dirX ]   [ spriteX-playerX ]
	// [            ]    =    -1 * [                 ]   [       ]    =    1 / (planeX*dirY-dirX*planeY) * [                 ] * [                 ]
	// [ transformY ]              [ -planeY  planeX ]   [ distY ]                ^ always -1 ^            [ -planeY  planeX ]   [ spriteY-playerY ]

	// Multiplying our matrix by the Inverse Determinant (always -1 for unit vectors) is the same as dividing by the determinant
	const double		transformX = -1 * ((player.y * distX) - (player.x * distY));
	const double		transformY = -1 * (( -cam.y  * distX) + (  cam.x  * distY));

	// Calculate sprite screen position
	const int			spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));

	sprite->screen_x = spriteScreenX;
	sprite->distance = transformY;

	// Draw the sprite
	draw_sprite(data, rays, sprite);
}

void	sprites(t_data *data, t_ray_data **rays)
{
	t_sprite	*sprite;

	sprite = data->sprites;
	while (sprite)
	{
		// Calculate distance to the player
		sprite->distance_x = sprite->x - data->player.x;
		sprite->distance_y = sprite->y - data->player.y;

		sprite = sprite->next;
	}

	// Sort sprites by distance using bubble sort
	sort_sprites(&data->sprites);

	// Draw the sprites
	sprite = data->sprites;
	while (sprite)
	{
		transform_sprite_location(data, sprite, rays);

		sprite = sprite->next;
	}

	// Update the sprites
	update_frames(data->sprites);
}
