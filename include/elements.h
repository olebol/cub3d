/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:46:05 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 15:44:30 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "MLX42.h"

typedef struct s_elements
{
	mlx_texture_t	*textures[4];
	uint32_t		floor;
	uint32_t		ceiling;
}					t_elements;

size_t		parse_elementss(t_elements *elements, char *str);


#endif