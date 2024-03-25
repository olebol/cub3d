/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:47:55 by opelser           #+#    #+#             */
/*   Updated: 2024/03/25 18:19:04 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	rotate_hook(t_data *data)
{
	double				angle;

	// The scalar is used to make the rotation speed stay constant regardless of the frame rate
	const double		scalar = 20 * data->mlx->delta_time;

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
