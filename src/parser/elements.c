/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:47:57 by opelser           #+#    #+#             */
/*   Updated: 2024/05/24 16:13:37 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "errors.h"
#include "utils.h"
#include "libft.h"

static void	set_colour(uint32_t *colour, const char *value)
{
	const char		**rgb = (const char **) ft_split(value, ',');
	int				channel;
	int				i;

	if (rgb == NULL)
		error(E_MALLOC);
	if (*colour != 0x00000000)
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
		*colour = (*colour << 8) | channel;
		i++;
	}
	*colour = (*colour << 8) | 0xFF;
	if (i != 3)
		error(E_ELEM_RGB);
	ft_free_str_arr((char **) rgb);
}

static void	set_texture(t_elements *elements, t_texture id, char *value)
{
	if (value == NULL)
		error(E_ELEM_VALUE);
	if (elements->textures[id] != NULL)
		error(E_ELEM_DUPLICATE);
	if (is_valid_extension(value, TEXTURE_FILE_EXTENSION) == false)
		error(E_FILE_EXTENSION);
	elements->textures[id] = mlx_load_png(value);
	if (elements->textures[id] == NULL)
		error(E_ELEM_VALUE);
	argb_to_rgba(elements->textures[id]);
}

static void	set_element(t_elements *elements, char *id, char *value)
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
	else if (ft_strcmp(id, "F") == 0)
		set_colour(&elements->floor, value);
	else if (ft_strcmp(id, "C") == 0)
		set_colour(&elements->ceiling, value);
	else
		error(E_ELEM_ID);
}

static char	*get_next_string(char *str, size_t *i)
{
	char		*sub;
	size_t		start;
	size_t		end;

	start = *i;
	while (str[start] && ft_isspace(str[start]))
		start++;
	end = start;
	while (str[end] && !(ft_isspace(str[end]) || str[end] == '\n'))
		end++;
	sub = ft_substr(str, start, end - start);
	if (sub == NULL)
		error(E_MALLOC);
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
	while (str[i] && loops < 6)
	{
		id = get_next_string(str, &i);
		value = get_next_string(str, &i);
		if (str[i] != '\n' && str[i] != '\0')
			error(E_ELEM_VALUE);
		set_element(elements, id, value);
		free(id);
		free(value);
		i++;
		loops++;
	}
	if (loops < 6)
		error(E_ELEM_MISSING);
	if (elements->textures[NORTH] == NULL || elements->textures[SOUTH] == NULL
		|| elements->textures[WEST] == NULL || elements->textures[EAST] == NULL)
		error(E_ELEM_MISSING);
	return (i);
}
