/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:46 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 21:37:54 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_data(t_data *data)
{
	ft_free_str_arr(data->map.map);
	free(data->elements.textures[NORTH]);
	free(data->elements.textures[SOUTH]);
	free(data->elements.textures[WEST]);
	free(data->elements.textures[EAST]);
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
