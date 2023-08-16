/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/16 16:36:31 by opelser       ########   odam.nl         */
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

int	main(int argc, char *argv[])
{
	t_data		data;

	if (argc != 2)
		ft_error("Invalid number of arguments");

	if (init_mlx_data(&data))
		ft_error("Failed to initialize MLX data");



	parse_map(argv[1], &data.map);

	// Draw minimap
	draw_map(&data);
	print_map(data.map.map);

	if (init_player(&data))
	{
		mlx_terminate(data.mlx);
		ft_error("Failed to initialize player");
	}

	// Move image to center player position
	data.map.minimap->instances[0].x = 0 - data.player.x + data.map.minimapSize / 2;
	data.map.minimap->instances[0].y = 0 - data.player.y + data.map.minimapSize / 2;

	for (int i = 0; i < data.map.minimapSize; i++)
		mlx_put_pixel(data.screen, data.map.minimapSize, i, 0x00FF00FF);
	
	for (int i = 0; i < data.map.minimapSize; i++)
		mlx_put_pixel(data.screen, i, data.map.minimapSize, 0x00FF00FF);

	mlx_key_hook(data.mlx, &captainhook, (void *) &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
