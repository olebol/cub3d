/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:32:27 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/15 16:45:29 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_player(t_data *data)
{
	const int		tileSize = data->map.tileSize;
	data->player.img = mlx_new_image(data->mlx, 5, 5);
	if (!data->player.img)
		return (1);

	// Draw player dot to image
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			mlx_put_pixel(data->player.img, i, j, 0xFF6961FF);

	// Set player pos to middle of the screen
	data->player.posX = ((data->map.width / 2) * tileSize) + tileSize / 2;
	data->player.posY = ((data->map.height / 2) * tileSize) + tileSize / 2;
	return (0);
}

int		init_mlx_data(t_data *data)
{
	int		fail = 0;
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (1);
	data->screen = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fail && !data->screen)
		fail = 1;
	if (!fail && mlx_image_to_window(data->mlx, data->screen, 0, 0) == -1)
		fail = 2;
	data->map.minimap = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fail && !data->map.minimap)
		fail = 3;
	if (fail)
		mlx_terminate(data->mlx);
	return (fail);
}
