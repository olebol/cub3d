/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:58:39 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/16 23:42:06 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotation_hook(t_data *data)
{
	float	angle = data->player.angle;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A) == true)
	{
		angle -= 0.1;
		if (angle < 0)
			angle += M_PI * 2;

		data->player.delta_x = cos(angle);
		data->player.delta_y = sin(angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) == true)
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) == true)
	{
		data->player.x += data->player.delta_x * 2;
		data->player.y += data->player.delta_y * 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) == true)
	{
		data->player.x -= data->player.delta_x * 2;
		data->player.y -= data->player.delta_y * 2;
	}
}


void		captainhook(mlx_key_data_t keydata, void *dataPointer)
{
	t_data				*data;

	(void) keydata;
	data = (t_data *) dataPointer;

	rotation_hook(data);
	move_hook(data);
	exit_hook(data);
	draw_map(data);
}
