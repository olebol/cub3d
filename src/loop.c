/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:58:39 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/15 20:08:55 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool		isWall(t_data *data, int offsetX, int offsetY)
{
	int		mapX;
	int		mapY;

	mapX = (data->player.posX + offsetX) / data->map.tileSize;
	mapY = (data->player.posY + offsetY) / data->map.tileSize;
	if (data->map.map[mapY][mapX] == '1')
		return (true);
	return (false);
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
		if (isWall(data, 0, -2) == false)
		{
			data->player.img->instances[0].y -= 2;
			data->player.posY -= 2;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) == true)
	{
		if (isWall(data, 0, 2 + data->player.img->height) == false)
		{
			data->player.img->instances[0].y += 2;
			data->player.posY += 2;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) == true)
	{
		if (isWall(data, -2, 0) == false)
		{
			data->player.img->instances[0].x -= 2;
			data->player.posX -= 2;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D) == true)
	{
		if (isWall(data, 2 + data->player.img->width, 0) == false)
		{
			data->player.img->instances[0].x += 2;
			data->player.posX += 2;
		}
	}
}

void		captainhook(mlx_key_data_t keydata, void *dataPointer)
{
	t_data				*data;

	(void) keydata;
	data = (t_data *) dataPointer;

	move_hook(data);
	exit_hook(data);

	draw_map(data);
}
