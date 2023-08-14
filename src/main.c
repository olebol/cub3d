/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 21:08:08 by opelser       ########   odam.nl         */
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

int		init_mlx_data(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (1);
	data->screen = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->screen)
	{
		mlx_terminate(data->mlx);
		return (2);
	}
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0))
	{
		mlx_terminate(data->mlx);
		return (3);
	}

	data->map.minimap = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->map.minimap)
	{
		mlx_terminate(data->mlx);
		return (4);
	}
	return (0);
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

	parse_map(argv[1], &data.map);
	print_map(data.map.map);

	draw_map(&data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
