/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:47:24 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 17:24:07 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include <stdint.h>

uint32_t	flip_color(uint32_t color)
{
	return ((color & 0xFF000000) >> 24 | \
			(color & 0x00FF0000) >> 8 | \
			(color & 0x0000FF00) << 8 | \
			(color & 0x000000FF) << 24);
}

void		flip_texture(mlx_texture_t *texture)
{
	const int		size = texture->width * texture->height;
	uint32_t		*pixels;
	int				i;

	pixels = (uint32_t *) texture->pixels;
	i = 0;
	while (i < size)
	{
		pixels[i] = flip_color(pixels[i]);
		i++;
	}
}
