/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:27 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 15:41:59 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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

// Initialize MLX
static bool		init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, GAME_NAME, false);
	if (!data->mlx)
		return (false);
	return (true);
}

static void		init_fields(t_data *data)
{
	data->elements.textures[NORTH] = NULL;
	data->elements.textures[SOUTH] = NULL;
	data->elements.textures[WEST] = NULL;
	data->elements.textures[EAST] = NULL;
	data->elements.floor = 0x00000000;
	data->elements.ceiling = 0x00000000;

	data->player.x = 0;
	data->player.y = 0;
	data->player.dir = get_vector(0);

	data->map.width = 0;
	data->map.height = 0;
	data->map.map = NULL;

	data->wall_middle = WIN_HEIGHT / 2;
}

// Initialize all data
void	init(t_data *data, const char *filename)
{
	init_fields(data);

	parse_file(data, filename);

	if (!init_mlx(data))
		error(E_MLX_INIT);
	if (!init_screen(data))
		error(E_IMAGE_INIT);
	if (!init_minimap(data))
		error(E_IMAGE_INIT);

	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
}
