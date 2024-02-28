/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:44:59 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/27 22:25:59 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool		is_valid_rgb_format(unsigned int *color)
{
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		return (false);

	return (true);
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

bool		check_element_rgb(char *str)
{
	unsigned int	color[3];
	size_t			i;
	size_t			len;
	size_t			component;

	i = 0;
	component = 0;
	while (str[i])
	{
		len = 0;
		while (str[len + i] && ft_isdigit(str[len + i]))
			len++;

		if (len > 3 || (str[len + i] != ',' && str[len + i] != '\0') || len == 0)
			return (false);

		color[component] = set_rgb_component(&str[i], len);

		component++;
		i += len + 1;
	}

	if (component != 3)
		return (false);

	if (is_valid_rgb_format(color) == false)
		return (false);

	return (true);
}
