/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:30:41 by opelser           #+#    #+#             */
/*   Updated: 2024/05/31 17:04:06 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"

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
		mlx_put_pixel(data->screen, x, y, color);
		y++;
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
	t_ray_data		ray;
	int				x;

	x = 0;
	draw_background(data);
	while (x < WIDTH)
	{
		ray = cast_ray(data, x);
		draw_data = set_draw_data(data, &ray);
		draw_wall(data, &draw_data, x);
		x++;
	}
}
