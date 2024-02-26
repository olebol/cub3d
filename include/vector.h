/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:00:40 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 23:57:43 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	double			x;
	double			y;
	double			direction;
}					t_vector;

/**
 * @brief Calculate the vector with the given angle.
*/
t_vector	get_vector(double angle);

#endif