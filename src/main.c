/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:46 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 16:04:37 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_data(t_data *data)
{
	ft_free_str_arr(data->map.map);
	mlx_delete_texture(data->elements.textures[NORTH]);
	mlx_delete_texture(data->elements.textures[SOUTH]);
	mlx_delete_texture(data->elements.textures[WEST]);
	mlx_delete_texture(data->elements.textures[EAST]);
}

void	cubed(const char *filename)
{
	t_data	data;

	init(&data, filename);
	mlx_loop_hook(data.mlx, &captainhook, (void *) &data);
	mlx_cursor_hook(data.mlx, &mouse_hook, (void *) &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_data(&data);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error(E_ARGC);
	cubed(argv[1]);
	return (0);
}
