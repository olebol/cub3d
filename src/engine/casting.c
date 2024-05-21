/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   casting.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 15:41:25 by opelser       #+#    #+#                 */
/*   Updated: 2024/04/24 14:49:59 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "casting.h"
#include <math.h>

// set the distance to the next horizontal intersection to the left and define the direction to take on the map
void		set_distances_and_map_steps(t_dda_values *dda, \
										t_ray_data *ray, double x, double y)
{
	// ray pointed left
	if (ray->dir.x < 0)
	{
		dda->distance_x = dda->delta_x * (x - dda->map_x);
		dda->map_step_x = -1;
	}
	// ray pointed right
	else
	{
		dda->distance_x = dda->delta_x * (dda->map_x + 1 - x);
		dda->map_step_x = 1;
	}

	// ray pointed upwards
	if (ray->dir.y < 0)
	{
		dda->distance_y = dda->delta_y * (y - dda->map_y);
		dda->map_step_y = -1;
	}
	// ray pointed downwards
	else
	{
		dda->distance_y = dda->delta_y * (dda->map_y + 1 - y);
		dda->map_step_y = 1;
	}
}

t_dda_values	get_dda_values(t_ray_data *ray, double x, double y)
{
	t_dda_values	dda;

	// Set the distance between two intersections
	if (ray->dir.x == 0) // parallel
		dda.delta_x = INFINITY;
	else
		dda.delta_x = fabs(1 / ray->dir.x);
	
	if (ray->dir.y == 0) // parallel
		dda.delta_y = INFINITY;
	else
		dda.delta_y = fabs(1 / ray->dir.y);

	// Set the current map position to the player's position
	dda.map_x = (int) x;
	dda.map_y = (int) y;

	set_distances_and_map_steps(&dda, ray, x, y);

	return (dda);
}

// Move to the next horizontal or vertical intersection
void		go_to_next_intersection(t_ray_data *ray, t_dda_values *dda)
{
	if (dda->distance_x < dda->distance_y) // Move to the next horizontal intersection
	{
		dda->distance_x += dda->delta_x;
		dda->map_x += dda->map_step_x;

		ray->side = HORIZONTAL;
	}
	else // Move to the next vertical intersection
	{
		dda->distance_y += dda->delta_y;
		dda->map_y += dda->map_step_y;

		ray->side = VERTICAL;
	}
}

// Calculate the exact position of the wall hit and the distance to the wall hit
void		calculate_hit(t_data *data, t_ray_data *ray, t_dda_values *dda)
{
	if (ray->side == HORIZONTAL)
	{
		// if (ray->tile_hit == CLOSED_DOOR)
			// ray->distance = (dda->distance_x + 0.5) - dda->delta_x;
		// else
			ray->distance = (dda->distance_x - dda->delta_x);

		ray->hit_x = dda->map_x;
		ray->hit_y = data->player.y + (ray->distance * ray->dir.y);
	}
	else
	{
		// if (ray->tile_hit == CLOSED_DOOR)
			// ray->distance = (dda->distance_y + 0.5) - dda->delta_y;
		// else
			ray->distance = (dda->distance_y - dda->delta_y);

		ray->hit_x = data->player.x + (ray->distance * ray->dir.x);
		ray->hit_y = dda->map_y;
	}
}

void	calculate_hit_door(t_data *data, t_ray_data *ray, t_dda_values *dda)
{
	if (ray->side == HORIZONTAL)
	{

		// ray->distance = (dda->distance_x - dda->delta_x) + 0.5;

		// ray->hit_x = dda->map_x + 0.5;

		ray->hit_x = dda->map_x;
		ray->distance = (dda->distance_x - dda->delta_x);

		ray->hit_y = data->player.y + (ray->distance * ray->dir.y);
	}
	else
	{
		ray->distance = (dda->distance_y - dda->delta_y);

		ray->hit_x = data->player.x + (ray->distance * ray->dir.x) + 0.5;
		ray->hit_y = dda->map_y + 0.5;
	}
}

#include <stdio.h>
t_ray_data 	*set_ray_door_hit(t_ray_data **head, t_ray_data *ray)
{
	t_ray_data *new_node = (t_ray_data *)ft_malloc(sizeof(t_ray_data));
	// *new_node = *ray; // Copies data from ray to new_node
	new_node->dir.direction = ray->dir.direction;
	new_node->dir.x = ray->dir.x;
	new_node->dir.y = ray->dir.y;
	new_node->side = ray->side;
	new_node->distance = ray->distance;
	// printf("ray->distance: %f\n", ray->distance);
	new_node->hit_x = ray->hit_x;
	new_node->hit_y = ray->hit_y;
	new_node->tile_hit = ray->tile_hit;
    new_node->next = *head; // Insert new_node at the beginning of the list
    
	
	*head = new_node; // Update head to point to the new_node
	
	return (*head);
}

// DDA algorithm to calculate the distance to the next wall hit
void	dda_door_interaction(t_data *data, t_ray_data *ray)
{
	t_dda_values	dda;

	dda = get_dda_values(ray, data->player.x, data->player.y);

	while (true)
	{
		// Save the tile type of the current position
		ray->tile_hit = get_tile_type(&data->map, dda.map_x, dda.map_y);

		// Stop the DDA algorithm
		if (ray->tile_hit == WALL || ray->tile_hit == CLOSED_DOOR || ray->tile_hit == OPEN_DOOR)
			break ;
		// Move to the next tile depending on the distance to the next intersection
		go_to_next_intersection(ray, &dda);
	}
	calculate_hit(data, ray, &dda);
}

// DDA algorithm to calculate the distance to the next wall hit
void	dda(t_data *data, t_ray_data **head, t_ray_data *ray)
{
	t_dda_values	dda;

	dda = get_dda_values(ray, data->player.x, data->player.y);

	while (true)
	{
		// Save the tile type of the current position
		ray->tile_hit = get_tile_type(&data->map, dda.map_x, dda.map_y);

		// Stop the DDA algorithm
		if (ray->tile_hit == WALL )
			break ;
			
		if (ray->tile_hit == CLOSED_DOOR || ray->tile_hit == OPEN_DOOR)
		{
			calculate_hit_door(data, ray, &dda);
			ray = set_ray_door_hit(head, ray);
		}

		// Move to the next tile depending on the distance to the next intersection
		go_to_next_intersection(ray, &dda);
	}
	calculate_hit(data, ray, &dda);
}

t_ray_data		*cast_ray(t_data *data, int x, bool door_interaction)
{
	t_ray_data		*ray;
	t_ray_data		*head;
	const double	camera_plane_x = 2 * x / (double) WIN_WIDTH - 1; // value between -1 and 1 representing the x-coordinate on the camera plane

	ray = (t_ray_data *)ft_malloc(sizeof(t_ray_data));
	ray->next = NULL;
	// Calculate the direction of the ray
	ray->dir.x = data->player.dir.x + (data->player.cam.x * camera_plane_x);
	ray->dir.y = data->player.dir.y + (data->player.cam.y * camera_plane_x);

	// Set all fields to 0
	ray->side = NO_SIDE;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->tile_hit = EMPTY;
	ray->distance = 0;

	head = ray;

	if (door_interaction)
		dda_door_interaction(data, ray);
	else
		dda(data, &head, ray);

	return (head);
}
