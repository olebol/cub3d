/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:40:41 by opelser           #+#    #+#             */
/*   Updated: 2024/03/01 17:01:44 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASTING_H
# define CASTING_H

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

/**
 * @brief	Structure to store the ray data
 * 
 * @param	vector 			Vector of the ray
 * @param	dda 			Values for the ray used by the DDA algorithm
 * @param	side 			Side of the last wall hit by the ray
 * @param	distance 		Distance to the wall hit by the ray
*/
typedef struct s_ray_data
{
	t_vector		vector;
	t_dda_values	dda;

	enum e_side		side;
	double			distance;
}					t_ray_data;

/**
 * @brief		Cast a ray and return the ray data
 * 
 * @param		data		Pointer to the main data structure
 * @param		angle		Angle of the ray
 * 
 * @return		t_ray_data	Structure containing the ray data
*/
t_ray_data		cast_ray(t_data *data, double angle);


#endif