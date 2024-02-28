/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:46 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 15:14:20 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
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

void	cubed(const char *file)
{
	t_data	data;

	parse_file(&data, file);

	init(&data);

	printf("player.x: %f\n", data.player.x);
	printf("player.y: %f\n", data.player.y);

	print_map(data.map.map);

	mlx_loop_hook(data.mlx, &captainhook, (void *) &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error(E_ARGC);

	cubed(argv[1]);

	return (0);
}
