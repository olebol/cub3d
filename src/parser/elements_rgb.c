/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements_rgb.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:44:59 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 15:32:04 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	validate_rgb_format(t_data *data, unsigned int *color)
{
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		return (set_error(data, E_RGB));
	data->elements->rgb_f = (color[0] << 16) | (color[1] << 8) | color[2];
	return (E_SUCCESS);
}

unsigned int	set_rgb_component(char *str, size_t len)
{
	unsigned int	num;
	size_t			i;

	i = 0;
	num = 0;
	while (i < len)
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int	check_element_rgb(char *str, t_data *data)
{
	size_t	i;
	size_t	len;
	size_t	comps;
	unsigned int	color[3];

	i = 0;
	len = 0;
	comps = 0;
	while (str[i])
	{
		while (str[len + i] && ft_isdigit(str[len + i]))
			len++;
		if (len > 3 || (str[len + i] != ',' && str[len + i] != '\0') || len == 0)
			return (set_error(data, E_RGB));
		color[comps] = set_rgb_component(&str[i], len);
		comps++;
		i += len + 1;
		len = 0;
	}
	if (comps != 3)
		return (set_error(data, E_RGB));
	if (validate_rgb_format(data, color) != E_SUCCESS)
		return (data->e_code);
	return (E_SUCCESS);
}
