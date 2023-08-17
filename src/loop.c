/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:58:39 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/17 18:56:55 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		is_wall(t_data *data, float x, float y)
{
	const int		tile_size = data->map.tileSize;
	
	if (data->map.map[(int) y / tile_size][(int) x / tile_size] == '1')
		return (true);
	return (false);
}

static void	rotation_hook(t_data *data)
{
	float	angle = data->player.angle;

	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == true)
	{
		angle -= 0.1;
		if (angle < 0)
			angle += M_PI * 2;

		data->player.delta_x = cos(angle);
		data->player.delta_y = sin(angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == true)
	{
		angle += 0.1;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;

		data->player.delta_x = cos(angle);
		data->player.delta_y = sin(angle);
	}
	data->player.angle = angle;
}

static void		exit_hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == true)
		mlx_close_window(data->mlx);
}

static void		move_hook(t_data *data)
{
	float		move_x;
	float		move_y;

	move_x = 0;
	move_y = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) == true)
	{
		move_x += data->player.delta_x * 2;
		move_y += data->player.delta_y * 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) == true)
	{
		move_x -= data->player.delta_x * 2;
		move_y -= data->player.delta_y * 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) == true)
	{
		move_x += data->player.delta_y * 2;
		move_y -= data->player.delta_x * 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) == true)
	{
		move_x -= data->player.delta_y * 2;
		move_y += data->player.delta_x * 2;
	}

	if (is_wall(data, move_x + data->player.x, data->player.y) == false)
		data->player.x += move_x;
	if (is_wall(data, data->player.x, move_y + data->player.y) == false)
		data->player.y += move_y;
}

void		clear_screen(mlx_image_t *img)
{
	for (int i = 0; i < WIN_WIDTH; i++)
		for (int j = 0; j < WIN_HEIGHT; j++)
			mlx_put_pixel(img, i, j, 0x00000000);
}

void		captainhook(void *dataPointer)
{
	t_data				*data;

	data = (t_data *) dataPointer;

	clear_screen(data->screen);
	rotation_hook(data);
	move_hook(data);
	exit_hook(data);
	cast_all_rays(data);
	draw_map(data);
}
