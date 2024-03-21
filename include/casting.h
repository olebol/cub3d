/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   casting.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 15:40:41 by opelser       #+#    #+#                 */
/*   Updated: 2024/03/21 18:07:47 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASTING_H
# define CASTING_H

# include "vector.h"

enum e_side
{
	HORIZONTAL,
	VERTICAL,
	NO_SIDE
};

/**
 * @brief		Structure to store the data needed for drawing
 * 
 * @param		texture 		Pointer to the texture
 * @param		line_height 	The original height of the wall
 * @param		wall_height 	Height of the wall including window width scaling
 * @param		wall_start 		Starting position of the wall
 * @param		wall_end 		Ending position of the wall
 * @param		wall_hit 		Position of the wall hit by the ray
 * @param		tex_x 			Position of the texture on the x axis
 * @param		step 			Step to take on the texture
*/
typedef struct s_draw_data
{
	mlx_texture_t	*texture;

	int				line_height;
	int				wall_height;

	int				wall_start;
	int				wall_end;
	
	double			wall_hit;
	int				tex_x;
	
	double			step;
	
}			t_draw_data;

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
*/
typedef struct s_ray_data
{
	t_vector		dir;

	enum e_side		side;
	double			distance;

	double			wall_hit;
}					t_ray_data;

/**
 * @brief		Cast a ray and return the ray data
 * 
 * @param		data 			Pointer to the main data structure
 * @param		camera_plane_x 	Position on the camera plane
 * 
 * @return		t_ray_data	Structure containing the ray data
*/
t_ray_data		cast_ray(t_data *data, double camera_plane_x);

#endif