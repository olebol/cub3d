/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:37:50 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 23:57:15 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

t_vector	get_vector(double angle)
{
	t_vector	vector;

	vector.direction = angle;
	vector.x = cos(angle);
	vector.y = sin(angle);

	return (vector);
}
