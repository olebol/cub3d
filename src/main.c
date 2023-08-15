/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/15 19:50:59 by opelser       ########   odam.nl         */
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

void	ft_error(char *message)
{
	printf("%s%s", C_LRED, C_BOLD);
	printf("Error\n%s\n", message);
	printf("%s", C_RESET);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_data		data;

	if (argc != 2)
		ft_error("Invalid number of arguments");

	if (init_mlx_data(&data))
		ft_error("Failed to initialize MLX data");

	for (int i = 0; i < 128; i++)
		mlx_put_pixel(data.screen, 128, i, 0x00FF00FF);
	
	for (int i = 0; i < 128; i++)
		mlx_put_pixel(data.screen, i, 128, 0x00FF00FF);

	parse_map(argv[1], &data.map);
	print_map(data.map.map);
	if (init_player(&data))
	{
		mlx_terminate(data.mlx);
		ft_error("Failed to initialize player");
	}


	// Draw minimap
	draw_map(&data);
	mlx_image_to_window(data.mlx, data.map.minimap, 0, 0);
	mlx_image_to_window(data.mlx, data.player.img, data.player.posX, data.player.posY);

	mlx_key_hook(data.mlx, &captainhook, (void *) &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
