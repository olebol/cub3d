/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:47:55 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 21:31:39 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void		keys(t_data *data)
{
	double				angle;

	// The scalar is used to make the rotation speed stay constant regardless of the frame rate
	const double		scalar = 25 * data->mlx->delta_time;

	angle = data->player.dir.direction;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == true)
	{
		angle -= 0.1 * scalar;
		if (angle < 0)
			angle += M_PI * 2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == true)
	{
		angle += 0.1 * scalar;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
	}

	// Update the player direction
	data->player.dir = get_vector(angle);
	data->player.cam = get_vector(angle + (M_PI / 2));

}

static void		mouse(t_data *data)
{
	static int		old_x;
	int				x;
	int				y;

	double				angle;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	(void) y;

	angle = data->player.dir.direction + (x - old_x) * 0.001;
	if (angle > M_PI * 2)
			angle -= M_PI * 2;
	if (angle < 0)
			angle += M_PI * 2;

	data->player.dir = get_vector(angle);

	old_x = x;
}

void	rotate_hook(t_data *data)
{
	keys(data);
	mouse(data);
}
