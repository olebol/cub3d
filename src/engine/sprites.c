/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:18:28 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 17:59:08 by opelser          ###   ########.fr       */
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
	const double	x = sprite->x - player->x;
	const double	y = sprite->y - player->y;

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

void	print_sprite(t_sprite *sprite)
{
	printf("Sprite: %p\n", sprite);
	printf("X: %f\n", sprite->x);
	printf("Y: %f\n", sprite->y);
	printf("Distance: %f\n", sprite->distance);
	printf("Next: %p\n\n", sprite->next);
}

void		draw_sprites(t_data *data, t_ray_data *ray_data)
{
	(void) ray_data;

	t_sprite	*sprite;

	sprite = data->sprites;
	while (sprite)
	{
		// Calculate  distance to the player
		sprite->distance = get_distance(&data->player, sprite);

		sprite = sprite->next;
	}

	// Sort sprites by distance
	sort_sprites(&data->sprites);

	sprite = data->sprites;
	while (sprite)
	{
		print_sprite(sprite);

		sprite = sprite->next;
	}

	// Draw the sprites
	sprite = data->sprites;
	while (sprite)
	{
		// Check if the sprite is in the player view
		if (is_sprite_in_view(&data->player, sprite))
		{
			// Calculate the sprite position on the screen
			// Calculate the sprite size
			// Get the line draw data
			// Draw the sprite line
		}

		sprite = sprite->next;
	}
}
