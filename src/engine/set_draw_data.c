/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_draw_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:59:27 by opelser           #+#    #+#             */
/*   Updated: 2024/05/31 17:00:24 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"

/**
 * @brief	Determine the texture to use for the wall
 * 
 * @param	ray			Pointer to the ray data
 * 
 * @return	t_texture	Enum value of the texture to use for the wall
*/
static mlx_texture_t	*get_texture(t_elements *elements, t_ray_data *ray)
{
	t_texture		texture;

	if (ray->side == VERTICAL)
	{
		if (ray->dir.y < 0)
			texture = NORTH;
		else
			texture = SOUTH;
	}
	else
	{
		if (ray->dir.x < 0)
			texture = WEST;
		else
			texture = EAST;
	}
	return (elements->textures[texture]);
}

int		get_texture_x(t_ray_data *ray, double tex_width)
{
	double			wall_hit;
	int				tex_x;

	if (ray->side == HORIZONTAL)
		wall_hit = ray->hit_y - (int) ray->hit_y;
	else
		wall_hit = ray->hit_x - (int) ray->hit_x;

	tex_x = wall_hit * tex_width;

	if ((ray->side == VERTICAL && ray->dir.y > 0)
		|| (ray->side == HORIZONTAL && ray->dir.x < 0))
		tex_x = tex_width - tex_x - 1;

	return (tex_x);
}

/**
 * @brief	Set the data needed for drawing the wall
 * 
 * @param	data		Pointer to the main data structure
 * @param	ray			Pointer to the ray data
 * @param	draw_data	Pointer to the draw data
*/
t_draw_data	set_draw_data(t_data *data, t_ray_data *ray)
{
	t_draw_data			draw;
	int					wall_height;

	wall_height = (HEIGHT / ray->distance);
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

	draw.texture = get_texture(&data->elements, ray);

	draw.tex_x = get_texture_x(ray, draw.texture->width);

	draw.step = (double) draw.texture->height / draw.length;

	return (draw);
}
