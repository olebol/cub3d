/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:32:27 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/18 23:58:18 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_player(t_data *data)
{
	// Set player pos to middle of top left tile (excl. wall layer)
	data->player.x = 1.5;
	data->player.y = 1.5;

	// Set player vector direction to 0 degrees (right)
	data->player.angle = 0;

	// Set player vector magnitude values
	data->player.delta_x = cos(data->player.angle) / data->map.tileSize;
	data->player.delta_y = sin(data->player.angle) / data->map.tileSize;

	return (0);
}

int		init_mlx_data(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (1);
	data->screen = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->screen)
	{
		mlx_terminate(data->mlx);
		return (1);
	}
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) == -1)
	{
		mlx_terminate(data->mlx);
		return (2);
	}

	data->map.tileSize = 32;
	data->map.minimapSize = WIN_WIDTH / 8;
	return (0);
}
