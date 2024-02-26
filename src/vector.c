/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:37:50 by opelser           #+#    #+#             */
/*   Updated: 2024/02/26 22:39:58 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

void	set_vector(t_vector *vector, double angle)
{
	vector->direction = angle;
	vector->x = cos(angle);
	vector->y = sin(angle);
}
