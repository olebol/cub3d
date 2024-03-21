/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 18:39:11 by evalieve      #+#    #+#                 */
/*   Updated: 2024/03/21 18:17:32 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief	Shifts the texture pixels from RGBA to ARGB format
 * 
 * @param	texture	Pointer to the texture to shift
 */
static void	shift_texture(mlx_texture_t *texture)
{
	uint32_t	total_pixels;
	uint32_t	*pixel;
	uint8_t		rgba[4];
	size_t		i;
	
	total_pixels = texture->width * texture->height;

	i = 0;
    while (i < total_pixels)
	{
        pixel = (uint32_t *)(texture->pixels + i * texture->bytes_per_pixel);

        // Extracting each channel from the RGBA pixel
       	rgba[R] = (*pixel >> 24) & 0xFF; // Red
        rgba[G] = (*pixel >> 16) & 0xFF; // Green
        rgba[B] = (*pixel >> 8) & 0xFF;  // Blue
        rgba[A] = (*pixel) & 0xFF;       // Alpha

        // Assembling the pixel in ARGB format
        *pixel = (rgba[A] << 24) | (rgba[B] << 16) | (rgba[G] << 8) | rgba[R];
		i++;
    }
}

/**
 * @brief	Parses the textures from the elements struct
 * 
 * @param	data	Pointer to the main data structure
 */
void	parse_texture(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < TEXTURE_TOTAL)
	{
		shift_texture(data->elements.textures[i]);
		i++;
	}
}