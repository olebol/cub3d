/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:51:41 by opelser           #+#    #+#             */
/*   Updated: 2024/06/04 23:12:36 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"
#include "casting.h"

static void	draw_to_screen(t_data *data, t_ray_data **rays, t_sprite *sprite, \
							t_sprite_draw_data *draw)
{
	uint32_t	color;
	int			tex_x;
	int			tex_y;
	int			x;
	int			y;

	x = draw->start_x;
	while (x < draw->end_x)
	{
		if (sprite->distance > 0 && sprite->distance < rays[x][0].distance)
		{
			tex_x = (x - (sprite->screen_x - draw->width / 2)) * draw->step;

			y = draw->start_y;
			while (y < draw->end_y)
			{
				tex_y = (y - (data->mid - draw->height / 2)) * draw->step;

				color = draw->pixels[tex_y * sprite->texture->width + tex_x];

				if ((color & 0x000000FF) != 0)
					mlx_put_pixel(data->screen, x, y, color);

				y++;
			}
		}
		x++;
	}
}

static void	set_sprite_draw_data(t_data *data, t_sprite *sprite, \
								t_sprite_draw_data *draw)
{
	draw->height = abs((int) (HEIGHT / sprite->distance));
	draw->width = abs((int) (HEIGHT / sprite->distance));

	draw->pixels = (uint32_t *) sprite->texture->pixels + \
					(sprite->current_frame * sprite->width);
	draw->step = (double) sprite->width / draw->width;

	draw->start_x = sprite->screen_x - draw->width / 2;
	if (draw->start_x < 0)
		draw->start_x = 0;
	draw->end_x = sprite->screen_x + draw->width / 2;
	if (draw->end_x >= WIDTH)
		draw->end_x = WIDTH - 1;

	draw->start_y = data->mid - draw->height / 2;
	if (draw->start_y < 0)
		draw->start_y = 0;
	draw->end_y = data->mid + draw->height / 2;
	if (draw->end_y >= HEIGHT)
		draw->end_y = HEIGHT - 1;
}

void	draw_sprite(t_data *data, t_ray_data **rays, t_sprite *sprite)
{
	t_sprite_draw_data	draw;

	set_sprite_draw_data(data, sprite, &draw);

	draw_to_screen(data, rays, sprite, &draw);
}
