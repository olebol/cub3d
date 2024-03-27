/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:18:28 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 23:58:25 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"
#include "casting.h"

#include <math.h>

void		sort_sprites(t_sprite **sprites)
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
			if (current->distance_x + current->distance_y 
				 < next->distance_x + next->distance_y)
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

void	draw_sprite(t_data *data, t_sprite *sprite, t_ray_data *rays)
{
	// ??
	const double		inverseDeterminant = 1.0 / ((data->player.cam.x * data->player.dir.y) - (data->player.dir.x * data->player.cam.y));
	
	// ???
	const double		transformX = inverseDeterminant *  ((data->player.dir.y * sprite->distance_x) - (data->player.dir.x * sprite->distance_y));
	const double		transformY = inverseDeterminant * ((-data->player.cam.y * sprite->distance_x) + (data->player.cam.x * sprite->distance_y));

	// Calculate sprite screen position
	const int			spriteScreenX = ((int) (WIN_WIDTH / 2) * (1 + transformX / transformY));

	// Calculate scaled sprite height and width
	const int			spriteHeight = abs((int) (WIN_HEIGHT / transformY));
	const int			spriteWidth  = abs((int) (WIN_HEIGHT / transformY));

	// Calculate draw start and end
	int			drawStartY = -spriteHeight / 2 + data->mid;
	if (drawStartY < 0)
		drawStartY = 0;

	int			drawEndY = spriteHeight / 2 + data->mid;
	if (drawEndY >= WIN_HEIGHT)
		drawEndY = WIN_HEIGHT - 1;

	int			drawStartX = -spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0)
		drawStartX = 0;

	int			drawEndX = spriteWidth / 2 + spriteScreenX;
	if (drawEndX >= WIN_WIDTH)
		drawEndX = WIN_WIDTH - 1;

	// Draw the sprite
	for (int x = drawStartX; x < drawEndX; x++)
	{
		// Check if a wall is in front of the sprite and if the sprite is on the screen
		if (transformY > 0 && transformY < rays[x].distance)
		{
			for (int y = drawStartY; y < drawEndY; y++)
			{
				mlx_put_pixel(data->screen, x, y, 0x00FF00FF);
			}
		}
	}
}

void		sprites(t_data *data, t_ray_data *rays)
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
		// print_sprite(sprite);

		draw_sprite(data, sprite, rays);

		sprite = sprite->next;
	}
}
