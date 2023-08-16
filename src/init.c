/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:32:27 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/16 16:44:46 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_player(t_data *data)
{
	t_player		*player;

	player = &data->player;
	const int		tileSize = data->map.tileSize;
	player->img = mlx_new_image(data->mlx, 5, 5);
	if (!player->img)
		return (1);

	// Draw player dot to image
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			mlx_put_pixel(player->img, i, j, 0xFF6961FF);

	// Set player pos to middle of the screen
	player->x = (data->map.width / 2) * tileSize + tileSize / 2;
	player->y = (data->map.height / 2) * tileSize - tileSize / 2;

	// Draw player to screen
	mlx_image_to_window(data->mlx, data->player.img, \
						data->map.minimapSize / 2 - 3, \
						data->map.minimapSize / 2 - 3);

	player->fov = 90; // idk what this does
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
	data->map.minimapSize = data->screen->width / 8;
	return (0);
}
