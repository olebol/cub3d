/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:07:30 by opelser           #+#    #+#             */
/*   Updated: 2024/02/20 17:21:17 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		is_wall(t_data *data, double x, double y)
{
	if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
		return (true);

	return (data->map.map[(int) y][(int) x] == '1');
}
