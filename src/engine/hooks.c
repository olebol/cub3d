/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:58:39 by opelser           #+#    #+#             */
/*   Updated: 2024/03/05 16:12:45 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <math.h>

static void	rotation_hook(t_data *data)
{
	double				angle;

	// The scalar is used to make the rotation speed stay constant regardless of the frame rate
	const double		scalar = 20 * data->mlx->delta_time;

	angle = data->player.dir.direction;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == true)
	{
		angle -= 0.1 * data->player.fov * scalar;
		if (angle < 0)
			angle += M_PI * 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == true)
	{
		angle += 0.1 * data->player.fov * scalar;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
	}

	// Update the player direction
	data->player.dir = get_vector(angle);
	data->player.cam = get_vector(angle + (M_PI / 2));
}

static void		fov_hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) == true)
	{
		data->player.fov += 0.1;
		if (data->player.fov > M_PI / 2)
			data->player.fov = M_PI / 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) == true)
	{
		data->player.fov -= 0.1;
		if (data->player.fov < 0.1)
			data->player.fov = 0.1;
	}
}

static void		exit_hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == true)
		mlx_close_window(data->mlx);
}

static void		move_hook(t_data *data)
{
	// How far the player will move in the x and y direction
	double				move_x;
	double				move_y;

	// The scalar is used to make the movement speed stay constant regardless of the frame rate
	const double		scalar = 3 * data->mlx->delta_time;

	move_x = 0;
	move_y = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) == true)
	{
		move_x += data->player.dir.x * scalar;
		move_y += data->player.dir.y * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) == true)
	{
		move_x -= data->player.dir.x * scalar;
		move_y -= data->player.dir.y * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) == true)
	{
		move_x += data->player.dir.y * scalar;
		move_y -= data->player.dir.x * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) == true)
	{
		move_x -= data->player.dir.y * scalar;
		move_y += data->player.dir.x * scalar;
	}

	// If the player is not moving, return
	if (move_x == 0 && move_y == 0)
		return ;

	// If the player is moving, check collision seperately for gliding feeling and update the player position
	if (get_tile_type(&data->map, move_x * 2 + data->player.x, data->player.y) == FLOOR)
		data->player.x += move_x;
	if (get_tile_type(&data->map, data->player.x, move_y * 3 + data->player.y) == FLOOR)
		data->player.y += move_y;
}

void		captainhook(void *dataPointer)
{
	t_data				*data;

	data = (t_data *) dataPointer;

	exit_hook(data);

	rotation_hook(data);

	fov_hook(data);

	move_hook(data);

	draw_world(data);

	printf("Fps: %f\n", 1 / data->mlx->delta_time);
}
