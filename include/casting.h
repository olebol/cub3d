/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:40:41 by opelser           #+#    #+#             */
/*   Updated: 2024/05/21 15:01:52 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASTING_H
# define CASTING_H

typedef struct s_data	t_data;

enum e_side
{
	HORIZONTAL,
	VERTICAL,
	NO_SIDE
};

/** 
 * @brief		Structure to store the values needed for the DDA algorithm
 * 
 * @param		delta_x 		Distance between two horizontal intersections
 * @param		delta_y 		Distance between two vertical intersections
 * @param		map_step_x 		Direction to take on the map x_axis
 * @param		map_step_y 		Direction to take on the map y_axis
 * @param		distance_x 		Distance traveled in the x axis
 * @param		distance_y 		Distance traveled in the y axis
 * @param		map_x 			Current position on the map x_axis
 * @param		map_y 			Current position on the map y_axis
 */
typedef struct s_dda_values
{
	double			delta_x;
	double			delta_y;

	int				map_step_x;
	int				map_step_y;

	double			distance_x;
	double			distance_y;

	int				map_x;
	int				map_y;
}					t_dda_values;

/**
 * @brief	Structure to store the ray data
 * 
 * @param	dir	 			Vector of the ray
 * @param	side 			Side of the last wall hit by the ray
 * @param	distance 		Distance to the wall hit by the ray
 * @param	hit_x 			X coordinate of the wall hit by the ray
 * @param	hit_y 			Y coordinate of the wall hit by the ray
 * @param	tile_hit 		Type of the tile hit by the ray
*/
typedef struct s_ray_data t_ray_data;
struct s_ray_data
{
	t_vector		dir;

	enum e_side		side;
	double			distance;

	double			hit_x;
	double			hit_y;

	t_tile			tile_hit;

	t_ray_data		*next;
};

/**
 * @brief		Cast a ray and return the ray data
 * 
 * @param		data 			Pointer to the main data structure
 * @param		camera_plane_x 	Position on the camera plane
 * 
 * @return		t_ray_data	Structure containing the ray data
*/
t_ray_data		*cast_ray(t_data *data, int x, bool door_interaction);

#endif