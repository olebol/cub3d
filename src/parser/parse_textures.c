/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:39:11 by evalieve          #+#    #+#             */
/*   Updated: 2024/03/25 19:13:33 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"

/**
 * @brief	Shifts the texture pixels from ARGB to RGBA format
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
		// Shifting the pixel from RGBA to ARGB format
		pixels[i] = (pixels[i] & 0x00FFFFFF) << 8 | (pixels[i] & 0xFF000000) >> 24;

		i++;
	}
}
