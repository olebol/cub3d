/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:39:11 by evalieve          #+#    #+#             */
/*   Updated: 2024/03/26 15:28:51 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

/**
 * @brief	Shifts the texture pixels from ABGR to RGBA format, why does LODEPNG do this?
 * 
 * @param	texture 	Pointer to the texture to shift
 */
void		argb_to_rgba(mlx_texture_t *texture)
{
	const uint32_t		total_pixels = texture->width * texture->height;
	uint32_t			*pixels;
	size_t				i;

	pixels = (uint32_t *) texture->pixels;

	i = 0;
	while (i < total_pixels)
	{
		// Shift the pixels from ABGR to RGBA format
		pixels[i] = ((pixels[i] & 0xFF000000) >> 24) | \
					((pixels[i] & 0x00FF0000) >> 8)  | \
					((pixels[i] & 0x0000FF00) << 8)  | \
					((pixels[i] & 0x000000FF) << 24);
		i++;
	}
}
