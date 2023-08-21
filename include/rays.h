/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 15:40:41 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/21 16:04:14 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "vector.h"

enum e_side
{
	HORIZONTAL,
	VERTICAL
};

/** 
 * @brief		Structure to store the values needed for the DDA algorithm
 * @param		delta_x			Distance between two horizontal intersections
 * @param		delta_y			Distance between two vertical intersections
 * @param		distance_x		Distance traveled in the x axis
 * @param		distance_y		Distance traveled in the y axis
 * @param		map_step_x		Direction to take on the map x_axis
 * @param		map_step_y		Direction to take on the map y_axis
 */
typedef struct s_dda_values
{
	double			delta_x;
	double			delta_y;

	double			distance_x;
	double			distance_y;

	int				map_step_x;
	int				map_step_y;
}					t_dda_values;

typedef struct s_ray_data
{
	t_vector		vector;
	t_dda_values	dda;

	enum e_side		side;
	double			distance;
}					t_ray_data;

void	set_ray_data(t_data *data, t_ray_data *ray_data, double angle);

#endif