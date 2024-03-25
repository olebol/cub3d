/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:47:55 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 23:25:45 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void		left_right(t_data *data, double x)
{
	double		angle;

	angle = data->player.dir.direction - x * 0.001;
	if (angle > M_PI * 2)
		angle -= M_PI * 2;
	if (angle < 0)
		angle += M_PI * 2;

	data->player.dir = get_vector(angle);
	data->player.cam = get_vector(angle + (M_PI / 2));
}

static void		up_down(t_data *data, double y)
{
	int		wall_middle;

	wall_middle = data->wall_middle - WIN_HEIGHT / 2 + y;

	if (wall_middle > 200)
		wall_middle = 200;
	if (wall_middle < -200)
		wall_middle = -200;

	data->wall_middle = wall_middle + WIN_HEIGHT / 2;
}

void	mouse_hook(double x, double y, void *dataPointer)
{
	t_data			*data;
	static double	old_x;
	static double	old_y;

	data = (t_data *) dataPointer;

	left_right(data, old_x - x);
	up_down(data, old_y - y);

	old_x = x;
	old_y = y;
}

void	view_hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == true)
		left_right(data, 50);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == true)
		left_right(data, -50);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP) == true)
		up_down(data, 25);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) == true)
		up_down(data, -25);
}
