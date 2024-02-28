/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:42:11 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/28 18:19:26 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool			check_element_path(char *path) // we strip the path so this should never happen right?
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] == ' ' || path[i] == '\t')
			return (false);
		i++;
	}
	return (true);
}

static void		check_information_elements(t_elements *elements)
{
	if (elements->no == NULL || elements->so == NULL || elements->we == NULL ||
		elements->ea == NULL || elements->f == NULL || elements->c == NULL)
	{
		error(E_ELEM_VALUE);
	}

	if (check_element_path(elements->no) == false ||
		check_element_path(elements->so) == false ||
		check_element_path(elements->we) == false ||
		check_element_path(elements->ea) == false)
	{
		error(E_ELEM_VALUE);
	}

	if (check_element_rgb(elements->f) == false ||
		check_element_rgb(elements->c) == false)
	{
		error(E_ELEM_RGB);
	}
}

static bool		elements_missing(int *tracker)
{
	int	i;

	i = 0;
	while (i < ELEM_COUNT)
	{
		if (tracker[i] == false)
			return (true);
		i++;
	}

	return (false);
}

void		verify_elements(char *content, t_data *data, size_t *pos)
{
	t_elements	*elements;
	int			tracker[] = {false, false, false, false, false, false};

	elements = data->elements;
	search_elements(elements, content, tracker, pos);

	if (elements_missing(tracker) == true) // deze nog nodig want ook in functie hiervoor?
		error(E_ELEM_MISS);

	check_information_elements(elements);
}
