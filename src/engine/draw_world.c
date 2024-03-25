/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:30:41 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 16:44:14 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include <math.h>

/**
 * @brief	Determine the texture to use for the wall
 * 
 * @param	ray_data	Pointer to the ray data
 * 
 * @return	t_texture	Enum value of the texture to use for the wall
*/
static t_texture	determine_texture(t_ray_data *ray_data)
{
	if (ray_data->side == VERTICAL)
	{
		if (ray_data->dir.y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (ray_data->dir.x < 0)
			return (WEST);
		else
			return (EAST);
	}
}

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
	size_t	y;
	size_t	end_wall;
	double	tex_y;
	int		color;	

	y = draw_data->wall_start;
	end_wall = draw_data->wall_end;
	tex_y= (draw_data->wall_start - WIN_HEIGHT / 2 + draw_data->line_height / 2) * draw_data->step;
	while (y < end_wall)
	{
		color = ((int *) draw_data->texture->pixels)[(int) tex_y * draw_data->texture->width + draw_data->tex_x];
		
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
 * @brief	Set the data needed for drawing the wall
 * 
 * @param	data		Pointer to the main data structure
 * @param	ray_data	Pointer to the ray data
 * @param	draw_data	Pointer to the draw data
*/
static void	set_draw_data(t_data *data, t_ray_data *ray_data, t_draw_data *draw_data)
{
	draw_data->texture = data->elements.textures[determine_texture(ray_data)];

	draw_data->wall_height = (WIN_HEIGHT / ray_data->distance);

	if (draw_data->wall_height < 0)
		draw_data->wall_height = 0;

	draw_data->line_height = draw_data->wall_height;

	if (draw_data->wall_height > WIN_HEIGHT)
		draw_data->wall_height = WIN_HEIGHT;

	draw_data->wall_start = WIN_HEIGHT / 2 - draw_data->wall_height / 2;

	if (draw_data->wall_start < 0)
		draw_data->wall_start = 0;

	draw_data->wall_end = WIN_HEIGHT / 2 + draw_data->wall_height / 2;

	if (draw_data->wall_end > WIN_HEIGHT)
		draw_data->wall_end = WIN_HEIGHT;

	draw_data->wall_hit = ray_data->wall_hit - floor(ray_data->wall_hit);

	draw_data->tex_x = (int)(draw_data->wall_hit * (double)draw_data->texture->width);

	draw_data->step = 1.0 * draw_data->texture->height / draw_data->line_height;
}

/**
 * @brief	Draw the world
 * 
 * @param	data	Pointer to the main data structure
*/
void	draw_world(t_data *data)
{
	const double	fov = data->player.fov;
	t_draw_data		draw_data;
	t_ray_data		ray_data;
	double			camera_plane_x;
	int				x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_plane_x = fov * (x / (double) WIN_WIDTH) - (fov / 2);

		ray_data = cast_ray(data, camera_plane_x);

		set_draw_data(data, &ray_data, &draw_data);

		draw_ceiling(data, draw_data.wall_start, x);

		draw_wall(data, &draw_data, x);

		draw_floor(data, draw_data.wall_end, x);		

		x++;
	}
}
