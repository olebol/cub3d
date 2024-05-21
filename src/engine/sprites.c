/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:18:28 by opelser           #+#    #+#             */
/*   Updated: 2024/05/21 15:36:49 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"
#include "casting.h"

#include <math.h>

static double 	get_distance(t_sprite *sprite)
{
	return (pow(sprite->distance_x, 2) + pow(sprite->distance_y, 2));
}

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

static void		draw_sprite(t_data *data, t_sprite *sprite, t_ray_data **rays, int spriteScreenX, double transformY)
{
	// Calculate scaled sprite height and width
	const int			spriteHeight = abs((int) (HEIGHT / transformY));
	const int			spriteWidth  = abs((int) (HEIGHT / transformY));

	// Calculate draw start and end
	int			drawStartY = data->mid - spriteHeight / 2;
	if (drawStartY < 0)
		drawStartY = 0;

	int			drawEndY = data->mid + spriteHeight / 2;
	if (drawEndY >= HEIGHT)
		drawEndY = HEIGHT - 1;

	int			drawStartX = spriteScreenX - spriteWidth / 2;
	if (drawStartX < 0)
		drawStartX = 0;

	int			drawEndX = spriteScreenX + spriteWidth / 2;
	if (drawEndX >= WIDTH)
		drawEndX = WIDTH - 1;

	// Draw the sprite with texture
	const uint32_t			*pixels = (uint32_t *) sprite->texture->pixels;
	const double 			stepX = (float) sprite->texture->width  / spriteWidth;
	const double			stepY = (float) sprite->texture->height / spriteHeight;

	for (int x = drawStartX; x < drawEndX; x++)
	{
		// Check if a wall is in front of the sprite and if the sprite is on the screen
		if (transformY > 0 && transformY < rays[x][0].distance)
		{
			const int		texX = (x - (spriteScreenX - spriteWidth / 2)) * stepX;

			for (int y = drawStartY; y < drawEndY; y++)
			{
				const int		texY = (y - (data->mid - spriteHeight / 2)) * stepY;

				const uint32_t	color = pixels[texY * sprite->texture->width + texX];

				if ((color & 0x000000FF) != 0)
				mlx_put_pixel(data->screen, x, y, color);
			}
		}
	}
}

#include <stdio.h>

// Something is wrong with the calculations
void	transform_sprite_location(t_data *data, t_sprite *sprite, t_ray_data **rays)
{
	// Variables for readability
	const t_vector		player = data->player.dir;
	const t_vector		cam = data->player.cam;
	const double		distX = sprite->x - data->player.x;
	const double		distY = sprite->y - data->player.y;

	// [ transformX ]              [ dirY      -dirX ]   [ distX ]                                         [ dirY      -dirX ]   [ spriteX-playerX ]
	// [            ]    =    -1 * [                 ]   [       ]    =    1 / (planeX*dirY-dirX*planeY) * [                 ] * [                 ]
	// [ transformY ]              [ -planeY  planeX ]   [ distY ]                ^ always -1 ^            [ -planeY  planeX ]   [ spriteY-playerY ]

	// Multiplying our matrix by the Inverse Determinant (always -1 for unit vectors) is the same as dividing by the determinant
	const double		transformX = -1 * ((player.y * distX) - (player.x * distY));
	const double		transformY = -1 * (( -cam.y  * distX) + (  cam.x  * distY));

	// Calculate sprite screen position
	const int			spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));

	// Draw the sprite
	draw_sprite(data, sprite, rays, spriteScreenX, transformY);
}

void		sprites(t_data *data, t_ray_data **rays)
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

		transform_sprite_location(data, sprite, rays);

		sprite = sprite->next;
	}
}
