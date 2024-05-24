/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:30:41 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 17:21:32 by opelser          ###   ########.fr       */
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
 * @brief	Determine the texture to use for the wall
 * 
 * @param	ray_data	Pointer to the ray data
 * 
 * @return	t_texture	Enum value of the texture to use for the wall
*/
static mlx_texture_t	*get_texture(t_elements *elements, t_ray_data *ray_data)
{
	t_texture		texture;

	if (ray_data->side == VERTICAL)
	{	
		if (ray_data->dir.y < 0)
			texture = NORTH;
		else
			texture = SOUTH;
	}
	else
	{
		if (ray_data->dir.x < 0)
			texture = WEST;
		else
			texture = EAST;
	}

	return (elements->textures[texture]);
}

/**
 * @brief	Set the data needed for drawing the wall
 * 
 * @param	data		Pointer to the main data structure
 * @param	ray_data	Pointer to the ray data
 * @param	draw_data	Pointer to the draw data
*/
static t_draw_data	set_draw_data(t_data *data, t_ray_data *ray_data)
{
	double				wall_hit;
	t_draw_data			draw;
	int					wall_height;
	int					texture_x;

	if (ray_data->side == HORIZONTAL)
		wall_hit = ray_data->hit_y - (int) ray_data->hit_y;
	else
		wall_hit = ray_data->hit_x - (int) ray_data->hit_x;

	wall_height = (HEIGHT / ray_data->distance);
	if (wall_height < 0)
		wall_height = 0;

	draw.length = wall_height;

	draw.start = data->mid - wall_height / 2;
	if (draw.start < 0)
		draw.start = 0;
	if (draw.start > HEIGHT)
		draw.start = HEIGHT;

	draw.end = data->mid + wall_height / 2;
	if (draw.end < 0)
		draw.end = 0;
	if (draw.end > HEIGHT)
		draw.end = HEIGHT;

	draw.texture = get_texture(&data->elements, ray_data);

	texture_x = wall_hit * draw.texture->width;

	if ((ray_data->side == VERTICAL && ray_data->dir.y > 0)			// South wall
		|| (ray_data->side == HORIZONTAL && ray_data->dir.x < 0))	// West wall
		texture_x = draw.texture->width - texture_x - 1;

	draw.tex_x = texture_x;

	draw.step = (double) draw.texture->height / draw.length;

	return (draw);
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