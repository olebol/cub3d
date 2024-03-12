/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:30:41 by opelser           #+#    #+#             */
/*   Updated: 2024/03/12 17:34:45 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"

void	draw_background(t_data *data)
{
	const size_t	screen_size = data->screen->width * data->screen->height;
	int				*screen;
	size_t			i;

	screen = (int *) data->screen->pixels;

	// // Draw the sky
	i = 0;
	while (i < screen_size / 2)
	{
		screen[i] = data->elements.ceiling;
		i++;
	}

	// // Draw the ground
	while (i < screen_size)
	{
		screen[i] = data->elements.floor;
		i++;
	}

	// Clear the screen
	// ft_bzero(screen, screen_size * sizeof(int));
}

static void		draw_wall_segment(t_data *data, int x, t_ray_data *ray_data)
{
	unsigned int			colour;
	size_t					lineheight;
	size_t					start_y;
	size_t					y;

	// Set the colour of the line
	colour = 0xFFFFFFFF;
	if (ray_data->side == VERTICAL)
		colour -= 0x00000005;

	// Calculate the height of the line to draw
	lineheight = (WIN_HEIGHT / ray_data->distance) * 2;
	if (lineheight > WIN_HEIGHT)
		lineheight = WIN_HEIGHT;

	// Set the start position of the line to draw to have the middle point of the line be the middle of the screen
	start_y = WIN_HEIGHT / 2 - lineheight / 2;

	// Draw the line
	y = 0;
	while (y < lineheight)
	{
		mlx_put_pixel(data->screen, x, start_y + y, colour);
		y++;
	}
}

static void		draw_walls(t_data *data)
{
	const double		fov = data->player.fov;
	t_ray_data			ray;
	double				camera_plane_x;
	size_t				x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_plane_x = fov * (x / (double) WIN_WIDTH) - (fov / 2);

		ray = cast_ray(data, camera_plane_x);

		draw_wall_segment(data, x, &ray);

		x++;
	}
}

void	draw_world(t_data *data)
{
	// Draw the ceiling and the floor
	draw_background(data);

	// Draw the	3D world
	draw_walls(data);

	// Draw the minimap
	draw_minimap(data);
}