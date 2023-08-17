/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/17 14:19:35 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(char **map)
{
	int i = 0;
	int j = 0;

	while (map[i])
	{
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

static void	draw_guidelines(t_data *data)
{
	// Draw map guidelines
	for (int i = 0; i <= data->map.minimapSize; i++)
	{
		if (i % data->map.tileSize == 0)
		{
			for (int j = 0; j < data->map.minimapSize; j++)
				mlx_put_pixel(data->screen, i, j, 0x00FF00FF);
		}
	}

	for (int i = 0; i <= data->map.minimapSize; i++)
	{
		if (i % data->map.tileSize == 0)
		{
			for (int j = 0; j < data->map.minimapSize; j++)
				mlx_put_pixel(data->screen, j, i, 0x00FF00FF);
		}
	}
}


int	main(int argc, char *argv[])
{
	t_data		data;

	if (argc != 2)
		ft_error("Invalid number of arguments");

	if (init_mlx_data(&data))
		ft_error("Failed to initialize MLX data");

	parse_map(argv[1], &data.map);
	init_player(&data);
	print_map(data.map.map);

	draw_guidelines(&data);
	draw_map(&data);

	// mlx_key_hook(data.mlx, &captainhook, (void *) &data);
	mlx_loop_hook(data.mlx, &captainhook, (void *) &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
