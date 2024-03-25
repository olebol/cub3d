/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:58:39 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 21:16:29 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		exit_hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == true)
		mlx_close_window(data->mlx);
}

void		fps_hook(t_data *data)
{
	static mlx_image_t	*fps = NULL;
	char				*fps_text;

	static double		last_time = 0;
	const double 		current_time = mlx_get_time();

	static int			frames = 0;

	fps_text = NULL;

	frames++;

	if (current_time - last_time > 0.5)
	{
		if (fps != NULL)
			mlx_delete_image(data->mlx, fps);

		fps_text = ft_itoa(frames / (current_time - last_time));
		fps = mlx_put_string(data->mlx, fps_text, 10, data->minimap->height + 10);
		free(fps_text);

		frames = 0;

		last_time = current_time;
	}
}

void		captainhook(void *dataPointer)
{
	t_data				*data;

	data = (t_data *) dataPointer;

	exit_hook(data);

	rotate_hook(data);

	move_hook(data);

	draw_world(data);

	draw_minimap(data);

	fps_hook(data);
}
