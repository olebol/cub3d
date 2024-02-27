/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2024/02/27 14:19:21 by evalieve      ########   odam.nl         */
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

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		fatal();
		return (NULL);
	}
	return (ptr);
}

int	init_mlx_struct(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, GAME_NAME, false);
	if (!data->mlx)
		return (set_error(data, E_MLX_INIT));//, R_MLX_INIT));
	data->screen = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->minimap = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) || \
		!data->screen || !data->minimap)
		return (set_error(data, E_MLX_INIT));//, R_MLX_INIT));
	return (R_SUCCESS);
}

void	init_data_struct(t_data *data)
{
	data->mlx = NULL;
	data->screen = NULL;
	// data->map = (t_map)ft_malloc(sizeof(t_map));
	// data->textures = NULL;
	data->e_code = E_SUCCESS;
	// data->e_message = NULL;
	data->elements = (t_elements *)ft_malloc(sizeof(t_elements));
}

int	cubed(const char *file)
{
	t_data	data;

	init_data_struct(&data);
	if (init_mlx_struct(&data) != R_SUCCESS)
		return (error(&data));
	if (parse_file(file, &data) != R_SUCCESS)
		return (error(&data));
	init_player(&data); // ??
	print_map(data.map.map);

	// not sure which is needed for mlx hooks and loops etc
	// mlx_key_hook(data.mlx, &captainhook, (void *) &data);
	mlx_loop_hook(data.mlx, &captainhook, (void *) &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (data.e_code);
}

int	main(int argc, char *argv[])
{
	// t_data		data;
	
	// init_data(&data, argv[1]);
	if (argc != 2)
	{
		ft_putstr_fd("CUB3D: ", STDERR_FILENO);
		ft_putstr_fd((char *)error_messages(E_ARGC), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (E_ARGC);
	}
	return (cubed(argv[1]));
	
	// code from earlier:
	
	// mlx_loop_hook(data.mlx, &captainhook, (void *) &data);
	// mlx_loop(data.mlx);
	// mlx_terminate(data.mlx);

	// ft_free_str_arr(data.map->map);
	// return (0);
}
