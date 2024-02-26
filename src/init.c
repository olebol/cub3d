/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:27 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 22:32:11 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_player(t_data *data)
{
	// Set player pos to middle of top left tile (excl. wall layer)
	data->player.x = 1.5;
	data->player.y = 1.5;

	// Set player vector direction to 0 degrees (right)
	data->player.vec.direction = 0;

	// Set player vector magnitude values
	data->player.vec.x = cos(data->player.vec.direction);
	data->player.vec.y = sin(data->player.vec.direction);

	return (0);
}

static bool		init_screen(t_data *data)
{
	data->screen = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->screen)
	{
		mlx_terminate(data->mlx);
		return (false);
	}
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) == -1)
	{
		mlx_delete_image(data->mlx, data->screen);
		mlx_terminate(data->mlx);
		return (false);
	}
	return (true);
}

static bool		init_minimap(t_data *data)
{
	const uint32_t		minimap_size = (data->screen->width / 8 + data->screen->height / 8) / 2;

	data->minimap = mlx_new_image(data->mlx, minimap_size, minimap_size);
	if (!data->minimap)
	{
		mlx_delete_image(data->mlx, data->screen);
		mlx_terminate(data->mlx);
		return (false);
	}
	if (mlx_image_to_window(data->mlx, data->minimap, 10, 10) == -1)
	{
		mlx_delete_image(data->mlx, data->screen);
		mlx_delete_image(data->mlx, data->minimap);
		mlx_terminate(data->mlx);
		return (false);
	}
	return (true);
}

int		init_mlx_data(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		ft_error("MLX failed to initialize");
	if (!init_screen(data))
		ft_error("Screen failed to initialize");
	if (!init_minimap(data))
		ft_error("Minimap failed to initialize");

	return (0);
}
