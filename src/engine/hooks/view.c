/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:47:55 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 23:00:44 by opelser          ###   ########.fr       */
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
	int		mid;

	mid = data->mid - WIN_HEIGHT / 2 + y;

	if (mid > 200)
		mid = 200;
	if (mid < -200)
		mid = -200;

	data->mid = mid + WIN_HEIGHT / 2;
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
