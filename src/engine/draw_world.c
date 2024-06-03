/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:30:41 by opelser           #+#    #+#             */
/*   Updated: 2024/06/03 18:02:05 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "cub3d.h"
#include "casting.h"
#include "sprite.h"

static void	draw_background(t_data *data)
{
	uint32_t			*screen;
	int					i;

	screen = (uint32_t *) data->screen->pixels;
	i = 0;
	while (i < data->mid * WIDTH)
	{
		screen[i] = data->elements.ceiling;
		i++;
	}
	while (i < WIDTH * HEIGHT)
	{
		screen[i] = data->elements.floor;
		i++;
	}
}

/**
 * @brief	Draw the wall
 * 
 * @param	data		Pointer to the main data structure
 * @param	draw_data	Pointer to the draw data
 * @param	x			Current position on the x axis
*/
static void	draw_wall(t_data *data, t_draw_data *draw, int x)
{
	const int		*pixels = (int *) draw->texture->pixels;
	uint32_t		color;
	double			tex_y;
	int				y;

	y = draw->start;
	while (y < draw->end)
	{
		tex_y = (y - (data->mid - draw->length / 2)) * draw->step;
		color = pixels[((int) tex_y * draw->texture->width) \
						+ draw->tex_x];
		if (color != 0x000000) 
			mlx_put_pixel(data->screen, x, y, color);
		y++;
	}
}

void	free_ray_data(t_ray_data **rays)
{
	t_ray_data		*current;
	t_ray_data		*next;
	int				i;

	i = 0;
	while (i < WIDTH)
	{
		current = rays[i];
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
		}
		i++;
	}
}


/**
 * @brief	Draw the world
 * 
 * @param	data	Pointer to the main data structure
*/
void	draw_world(t_data *data)
{
	t_draw_data		draw_data;
	t_ray_data		*rays[WIDTH];
	t_ray_data		*current;
	int				x;

	x = 0;
	draw_background(data);
	while (x < WIDTH)
	{
		rays[x] = cast_ray(data, x, false);

		current = rays[x];
		while (current != NULL)
		{
			draw_data = set_draw_data(data, current);
			draw_wall(data, &draw_data, x);
			current = current->next;
		}

		x++;
	}
	sprites(data, rays);
	free_ray_data(rays);
}
