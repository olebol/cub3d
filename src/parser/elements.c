/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:47:57 by opelser           #+#    #+#             */
/*   Updated: 2024/05/21 14:54:18 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "errors.h"
#include "utils.h"
#include "libft.h"

static void		set_color(uint32_t *color, const char *value)
{
	const char		**rgb = (const char **) ft_split(value, ',');
	int				channel;
	int				i;

	if (rgb == NULL)
		error(E_MALLOC);

	if (*color != 0x00000000)
		error(E_ELEM_DUPLICATE);

	i = 0;
	while (rgb[i])
	{
		channel = 0;

		if (ft_strlen(rgb[i]) > 3)
			error(E_ELEM_RGB);

		if (ft_err_atoi(rgb[i], &channel) != 0)
			error(E_ELEM_RGB);

		if (channel > 255)
			error(E_ELEM_RGB);

		// Add the current number to the color
		*color = (*color << 8) | channel;

		i++;
	}

	// Add the alpha channel
	*color = (*color << 8) | 0xFF;

	if (i != 3)
		error(E_ELEM_RGB);

	*color = flip_color(*color);

	ft_free_str_arr((char **) rgb);
}

static void		set_texture(t_elements *elements, t_texture id, char *value)
{
	// Check the value
	if (value == NULL)
		error(E_ELEM_VALUE);

	// Check if the texture is already set
	if (elements->textures[id] != NULL)
		error(E_ELEM_DUPLICATE);

	// Check file extension
	if (is_valid_extension(value, TEXTURE_FILE_EXTENSION) == false)
		error(E_FILE_EXTENSION);

	// Load the texture
	elements->textures[id] = mlx_load_png(value);
	
	if (elements->textures[id] == NULL)
		error(E_ELEM_VALUE);

	// Shift the texture pixels from ARGB to RGBA format
	flip_texture(elements->textures[id]);
}

static void		set_element(t_elements *elements, char *id, char *value)
{
	if (id == NULL || ft_strlen(id) == 0)
		error(E_ELEM_ID);

	if (value == NULL || ft_strlen(value) == 0)
		error(E_ELEM_VALUE);

	if (ft_strcmp(id, "NO") == 0)
		set_texture(elements, NORTH, value);
	else if (ft_strcmp(id, "SO") == 0)
		set_texture(elements, SOUTH, value);
	else if (ft_strcmp(id, "WE") == 0)
		set_texture(elements, WEST, value);
	else if (ft_strcmp(id, "EA") == 0)
		set_texture(elements, EAST, value);
	else if (ft_strcmp(id, "DC") == 0)
		set_texture(elements, DOOR_CLOSED, value);
	else if (ft_strcmp(id, "DO") == 0)
		set_texture(elements, DOOR_OPEN, value);
	else if (ft_strcmp(id, "S") == 0)
		set_texture(elements, SPRITE, value);
	else if (ft_strcmp(id, "F") == 0)
		set_color(&elements->floor, value);
	else if (ft_strcmp(id, "C") == 0)
		set_color(&elements->ceiling, value);
	else
		error(E_ELEM_ID);
}

static char	*get_next_string(char *str, size_t *i)
{
	char		*sub;
	size_t		start;
	size_t		end;

	// Skip spaces
	start = *i;
	while (str[start] && ft_isspace(str[start]))
		start++;

	// Get the length of the str
	end = start;
	while (str[end] && !(ft_isspace(str[end]) || str[end] == '\n'))
		end++;

	// Get the substring
	sub = ft_substr(str, start, end - start);
	if (sub == NULL)
		error(E_MALLOC);

	// Go to the end of the line or the start of the next element
	while (str[end] && ft_isspace(str[end]) && str[end] != '\n')
		end++;

	*i = end;
	return (sub);
}

size_t	parse_elements(t_elements *elements, char *str)
{
	char		*id;
	char		*value;
	size_t		loops;
	size_t		i;

	i = 0;
	loops = 0;
	while (str[i] && loops < ELEMENTS_AMOUNT)
	{
		// Get the id
		id = get_next_string(str, &i);

		// Get the value
		value = get_next_string(str, &i);

		// Check if the line is finished
		if (str[i] != '\n' && str[i] != '\0')
			error(E_ELEM_VALUE);

		// Get the substring and process the element
		set_element(elements, id, value);

		// Free the id and value
		free(id);
		free(value);

		i++;
		loops++;
	}

	// Check if all elements are loaded
	if (loops < ELEMENTS_AMOUNT)
		error(E_ELEM_MISSING);

	loops = 0;
	while (loops < TEXTURE_AMOUNT)
	{
		if (elements->textures[loops] == NULL)
			error(E_ELEM_MISSING);
		loops++;
	}

	return (i);
}
