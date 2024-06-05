/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:45:52 by opelser           #+#    #+#             */
/*   Updated: 2024/06/03 17:49:04 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h"

void	move_player(t_map *map, t_player *player, double move_x, double move_y)
{
	if (get_tile_type(map, move_x * 2 + player->x, player->y) == FLOOR)
		player->x += move_x;
	if (get_tile_type(map, player->x, move_y * 3 + player->y) == FLOOR)
		player->y += move_y;
}

void	left_right(t_data *data, double *move_x, double *move_y, double scalar)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) == true)
	{
		*move_x += data->player.dir.y * scalar;
		*move_y -= data->player.dir.x * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) == true)
	{
		*move_x -= data->player.dir.y * scalar;
		*move_y += data->player.dir.x * scalar;
	}
}

void	up_down(t_data *data, double *move_x, double *move_y, double scalar)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) == true)
	{
		*move_x += data->player.dir.x * scalar;
		*move_y += data->player.dir.y * scalar;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) == true)
	{
		*move_x -= data->player.dir.x * scalar;
		*move_y -= data->player.dir.y * scalar;
	}
}

void	move_hook(t_data *data)
{
	double				move_x;
	double				move_y;
	const double		scalar = 3 * data->mlx->delta_time;

	move_x = 0;
	move_y = 0;
	up_down(data, &move_x, &move_y, scalar);
	left_right(data, &move_x, &move_y, scalar);
	move_player(&data->map, &data->player, move_x, move_y);
}
