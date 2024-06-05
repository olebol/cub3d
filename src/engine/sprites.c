/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:18:28 by opelser           #+#    #+#             */
/*   Updated: 2024/06/05 23:50:37 by opelser          ###   ########.fr       */
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

static void	sort_sprites(t_sprite **sprites)
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

static void	update_frames(t_sprite *sprites)
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
static void	transform_sprite_location(t_sprite *sprite, \
					const t_vector player, const t_vector cam)
{
	const double	dist_x = sprite->distance_x;
	const double	dist_y = sprite->distance_y;
	double			transform_x;
	double			transform_y;

	transform_x = -1 * ((player.y * dist_x) - (player.x * dist_y));
	transform_y = -1 * ((-cam.y * dist_x) + (cam.x * dist_y));
	sprite->distance = transform_y;
	sprite->screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
}

void	sprites(t_data *data, t_ray_data **rays)
{
	t_sprite	*sprite;

	sprite = data->sprites;
	while (sprite)
	{
		sprite->distance_x = sprite->x - data->player.x;
		sprite->distance_y = sprite->y - data->player.y;
		sprite = sprite->next;
	}
	sort_sprites(&data->sprites);
	update_frames(data->sprites);
	sprite = data->sprites;
	while (sprite)
	{
		transform_sprite_location(sprite, data->player.dir, data->player.cam);
		draw_sprite(data, rays, sprite);
		sprite = sprite->next;
	}
}
