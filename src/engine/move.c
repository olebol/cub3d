/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:45:52 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 18:19:03 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		move_hook(t_data *data)
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
