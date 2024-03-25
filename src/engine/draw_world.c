/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:30:41 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 23:23:43 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"

/**
 * @brief	Draw the floor
 * 
 * @param	data		Pointer to the main data structure
 * @param	end_wall	End position of the wall
 * @param	x			Current position on the x axis
*/
static void	draw_floor(t_data *data, int end_wall, int x)
{
	size_t	i;

	i = end_wall;
	while (i < WIN_HEIGHT)
	{
		mlx_put_pixel(data->screen, x, i, data->elements.floor);
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
static void	draw_wall(t_data *data, t_draw_data *draw_data, int x)
{
	const int		*pixels = (int *) draw_data->texture->pixels;
	const int		wall_start = draw_data->wall_start;
	uint32_t		color;
	double			tex_y;
	int				y;

	tex_y = (wall_start - \
				(data->wall_middle) + (draw_data->line_height / 2)) \
			* draw_data->step;

	y = wall_start;
	while (y < draw_data->wall_end)
	{
		color = pixels[((int) tex_y * draw_data->texture->width) \
						+ draw_data->tex_x];

		mlx_put_pixel(data->screen, x, y, color);

		tex_y += draw_data->step;
		y++;
	}
}

/**
 * @brief	Draw the ceiling
 * 
 * @param	data		Pointer to the main data structure
 * @param	start_wall	Start position of the wall
 * @param	x			Current position on the x axis
*/
static void	draw_ceiling(t_data *data, int start_wall, int x)
{
	int	i;

	i = 0;
	while (i < start_wall)
	{
		mlx_put_pixel(data->screen, x, i, data->elements.ceiling);
		i++;
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
	const double		wall_hit = ray_data->wall_hit;
	t_draw_data			draw_data;
	int					wall_height;

	wall_height = (WIN_HEIGHT / ray_data->distance);
	if (wall_height < 0)
		wall_height = 0;

	draw_data.line_height = wall_height;

	draw_data.wall_start = data->wall_middle - wall_height / 2;
	if (draw_data.wall_start < 0)
		draw_data.wall_start = 0;
	if (draw_data.wall_start > WIN_HEIGHT)
		draw_data.wall_start = WIN_HEIGHT;

	draw_data.wall_end = data->wall_middle + wall_height / 2;
	if (draw_data.wall_end < 0)
		draw_data.wall_end = 0;
	if (draw_data.wall_end > WIN_HEIGHT)
		draw_data.wall_end = WIN_HEIGHT;

	draw_data.texture = get_texture(&data->elements, ray_data);

	draw_data.tex_x = (wall_hit - (int) wall_hit) * draw_data.texture->width;

	draw_data.step = 1.0 * draw_data.texture->height / draw_data.line_height;

	return (draw_data);
}

/**
 * @brief	Draw the world
 * 
 * @param	data	Pointer to the main data structure
*/
void	draw_world(t_data *data)
{
	t_draw_data		draw_data;
	t_ray_data		ray_data;
	int				x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_data = cast_ray(data, x);
		draw_data = set_draw_data(data, &ray_data);

		draw_ceiling(data, draw_data.wall_start, x);

		draw_wall(data, &draw_data, x);

		draw_floor(data, draw_data.wall_end, x);

		x++;
	}
}
