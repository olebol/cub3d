/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:27 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 16:08:36 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Set player position and direction
static void		init_player(t_data *data)
{
	// Set player pos to middle of top left tile (excl. wall layer)
	data->player.x = 1.5;
	data->player.y = 1.5;

	// Set player vector direction to 0 degrees (right)
	data->player.vec = get_vector(0);
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
	const uint32_t		minimap_size = (data->screen->width / 8 \
										+ data->screen->height / 8) / 2;

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

// Initialize MLX, screen and minimap
static bool		init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", false);
	if (!data->mlx)
		return (false);
	return (true);
}

// Initialize all data
void	init(t_data *data)
{
	if (!init_mlx(data))
		error(E_MLX_INIT);
	if (!init_screen(data))
		error(E_IMAGE_INIT);
	if (!init_minimap(data))
		error(E_IMAGE_INIT);
}
