/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:14:46 by opelser           #+#    #+#             */
/*   Updated: 2024/06/03 18:40:07 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"
#include "sprite.h"

static void	free_data(t_data *data)
{
	t_sprite	*sprite;
	int			i;

	ft_free_str_arr(data->map.map);
	sprite = data->sprites;
	while (sprite)
	{
		data->sprites = sprite->next;
		free(sprite);
		sprite = data->sprites;
	}
	i = 0;
	while (i < TEXTURE_AMOUNT)
	{
		mlx_delete_texture(data->elements.textures[i]);
		i++;
	}
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
