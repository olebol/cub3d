/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:58:39 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 16:27:59 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_hook(t_data *data)
{
	static bool		mouse_on = false;

	if (mlx_is_key_down(data->mlx, MLX_KEY_TAB) == true)
	{
		if (mouse_on == true)
		{
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
			mouse_on = false;
		}
		else
		{
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
			mouse_on = true;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == true)
		mlx_close_window(data->mlx);
}

void	fps_hook(t_data *data)
{
	static mlx_image_t	*fps_image = NULL;
	static double		last_time = 0;
	const double		current_time = mlx_get_time();
	static int			frames = 0;
	char				*fps_text;

	fps_text = NULL;
	frames++;
	if (current_time - last_time > 0.5)
	{
		if (fps_image != NULL)
			mlx_delete_image(data->mlx, fps_image);
		fps_text = ft_itoa(frames / (current_time - last_time));
		fps_image = mlx_put_string(data->mlx, fps_text, \
									10, data->minimap->height + 10);
		free(fps_text);
		frames = 0;
		last_time = current_time;
	}
}

void	captainhook(void *dataPointer)
{
	t_data				*data;

	data = (t_data *) dataPointer;
	exit_hook(data);
	view_hook(data);
	move_hook(data);
	draw_world(data);
	draw_minimap(data);
	fps_hook(data);
}
