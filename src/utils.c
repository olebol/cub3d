/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 16:07:30 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/18 16:07:41 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		is_wall(t_data *data, double x, double y)
{
	if (data->map.map[(int) y][(int) x] == '1')
		return (true);
	return (false);
}
