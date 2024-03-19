/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/18 11:00:33 by evalieve      #+#    #+#                 */
/*   Updated: 2024/03/19 18:32:03 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include <math.h>

// calculation which wall face is hit and which texture to use
// also calculates the x coordinate of the texture

t_texture	determine_texture(t_ray_data *ray_data)
{
	if (ray_data->side == HORIZONTAL)
	{
		if (ray_data->dir.y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	else // if (ray_data->side == VERTICAL)
	{
		if (ray_data->dir.x < 0)
			return (WEST);
		else
			return (EAST);
	}
}

#include <fcntl.h>

void	draw_wall_segment_texture(t_data *data, int x, t_ray_data *ray_data)
{
	mlx_texture_t	*texture;
	size_t			lineheight;
	size_t			start_y;
	size_t			y;

	double			wallhit;
	int				tex_x;
	int				tex_y;
	int 			color;

	// Set the texture to use for the wall
	texture = data->elements.textures[determine_texture(ray_data)];

	// Calculate the height of the line to draw
	lineheight = (WIN_HEIGHT / ray_data->distance) * 2;

	if (lineheight > WIN_HEIGHT)
		lineheight = WIN_HEIGHT;

	// Set the start position of the line to draw to have the middle point of the line be the middle of the screen
	start_y = WIN_HEIGHT / 2 - lineheight / 2;
	
	// Set the exact coordinates of the hit point on the wall scaled between 0 and 1 to use as the x coordinate of the texture
	if (ray_data->side == VERTICAL)
		wallhit = ray_data->hit_x - floor(ray_data->hit_x);
	else
		wallhit = ray_data->hit_y - floor(ray_data->hit_y);

	// Calculate the x coordinate of the texture
	tex_x = (int)(wallhit * (double)texture->width);

	// Draw the line
	y = 0;
	while (y < lineheight)
	{
		tex_y = (int) (y  * ((double)texture->height / lineheight));
		// tex_y = ((y - start_y) * texture->height / lineheight); // segfaults
		color = ((int *)texture->pixels)[tex_y * texture->width + tex_x];
		color = ((color >> 24) & 0xFF) | ((color & 0xFFFFFF) << 8);
		// color = ((color & 0xFF) << 24) | (color >> 8);
		mlx_put_pixel(data->screen, x, start_y + y, color);
		y++;
	}
}
