/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:58:39 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/19 21:33:12 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotation_hook(t_data *data)
{
	double	angle = data->player.angle;

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
	double				move_x;
	double				move_y;
	const double		scalar = 0.1;

	move_x = 0;
	move_y = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) == true)
	{
		move_x += data->player.delta_x * scalar;
		move_y += data->player.delta_y * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) == true)
	{
		move_x -= data->player.delta_x * scalar;
		move_y -= data->player.delta_y * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) == true)
	{
		move_x += data->player.delta_y * scalar;
		move_y -= data->player.delta_x * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) == true)
	{
		move_x -= data->player.delta_y * scalar;
		move_y += data->player.delta_x * scalar;
	}

	if (is_wall(data, move_x + data->player.x, data->player.y) == false)
		data->player.x += move_x;
	if (is_wall(data, data->player.x, move_y + data->player.y) == false)
		data->player.y += move_y;
}



void		captainhook(void *dataPointer)
{
	t_data				*data;

	data = (t_data *) dataPointer;

	rotation_hook(data);
	move_hook(data);
	exit_hook(data);
	cast_all_rays(data);
	draw_map(data);
}
