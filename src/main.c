/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:46 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 17:43:52 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cubed(const char *file)
{
	t_data	data;

	parse_file(&data, file);

	init(&data);

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
