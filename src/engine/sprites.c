/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:18:28 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 17:51:50 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"
#include "casting.h"

#include <math.h>

bool		is_sprite_in_view(t_player *player, t_sprite *sprite)
{
	(void)player;
	(void)sprite;
	return (true);
}

double		get_distance(t_player *player, t_sprite *sprite)
{
	double		x;
	double		y;

	x = sprite->x - player->x;
	y = sprite->y - player->y;

	return (sqrt(x * x + y * y));
}

void		sort_sprites(t_sprite **sprites)
{
	t_sprite	*current;
	t_sprite	*next;
	t_sprite	*prev;

	current = *sprites;
	while (current)
	{
		next = current->next;
		prev = NULL;
		while (next)
		{
			if (current->distance < next->distance)
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

#include <stdio.h>

void	print_sprites(t_sprite *sprites)
{
	t_sprite	*current;

	current = sprites;
	while (current)
	{
		printf("Sprite at x: %f, y: %f\n", current->x, current->y);
		current = current->next;
	}
}

void		draw_sprites(t_data *data, t_ray_data *ray_data)
{
	// Get all sprites
	// Calculate their distance to the player
	// Sort them by distance
	// Draw the sprites:
		// 	- Calculate the sprite position on the screen
		// 	- Calculate the sprite size
		// 	- Get the line draw data
		// 	- Draw the sprite line

	(void) ray_data;
	print_sprites(data->sprites);
}
