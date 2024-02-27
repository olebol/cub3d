/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:42:11 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 14:49:29 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_information_elements(t_elements *elements, t_data *data)
{
	if (elements->no == NULL || elements->so == NULL || elements->we == NULL || \
			elements->ea == NULL || elements->f == NULL || elements->c == NULL)
				return (set_error(data, E_ELEM_VALUE));//, R_ELEM_VALUE));
	if (check_element_path(elements->no, data) != R_SUCCESS || \
			check_element_path(elements->so, data) != R_SUCCESS || \
			check_element_path(elements->we, data) != R_SUCCESS || \
			check_element_path(elements->ea, data) != R_SUCCESS)
		return (set_error(data, E_ELEM_VALUE));//, R_ELEM_VALUE));
	if (check_element_rgb(elements->f, data) != R_SUCCESS || \
			check_element_rgb(elements->c, data) != R_SUCCESS)
			return (set_error(data, E_RGB));//, R_RGB));
	return (R_SUCCESS);
}

size_t set_element(char *content, t_elements *elements, char *id)
{
	char	*path;
	int		id_len;

	id_len = ft_strlen(id);
	path = strip_path(content, id_len);
	if (ft_strcmp("NO", id) == E_SUCCESS)
		elements->no = path;
	else if (ft_strcmp("SO", id) == E_SUCCESS)
		elements->so = path;
	else if (ft_strcmp("WE", id) == E_SUCCESS)
		elements->we = path;
	else if (ft_strcmp("EA", id) == E_SUCCESS)
		elements->ea = path;
	else if (ft_strcmp("F", id) == E_SUCCESS)
		elements->f = path;
	else if (ft_strcmp("C", id) == E_SUCCESS)
		elements->c = path;
	return (ft_strlen(path) + id_len + 1);
}

int	search_elements(t_elements *elements, t_data *data, \
							char *content, int *tracker, size_t *pos)
{
	size_t	i;
	char	*id[] = {"NO", "SO", "WE", "EA", "F", "C"};

	while (content[*pos])
	{
		i = 0;
		*pos = skip_empty(content, *pos);
		while (i < ELEM_COUNT && content[*pos])
		{
			// printf("i: %zu\n", i);
			// printf("id: %s\n", id[i]);
			if (compare_ids(&content[*pos], id[i]))
			{
				if (tracker[i] == true)
					return (set_error(data, E_ELEM_DUP));//, R_ELEM_DUP));
				tracker[i] = true;
				*pos += set_element(&content[*pos], elements, id[i]);
				break ;
			}
			i++;
		}
		if (!elements_missing(tracker))
			break ;
		if (i == ELEM_COUNT)
		{
			// printf("search_elements\n");
				return (set_error(data, E_ELEM_WRONG));//, R_ELEM_WRONG));

		}	
	}
	return (R_SUCCESS);
}

int	verify_elements(char *content, t_data *data, size_t *pos)
{
	t_elements	*elements;
	int			tracker[] = {false, false, false, false, false, false};
	
	elements = data->elements;
	if (search_elements(elements, data, content, tracker, pos) != R_SUCCESS)
		return (data->e_code);
	printf("verify_elements\n");
	if (elements_missing(tracker)) // deze nog nodig want ook in functie hiervoor
		return (set_error(data, E_ELEM_MISS));//, R_ELEM_MISS));
	if (check_information_elements(elements, data) != R_SUCCESS)
	{
		free_elems(elements);
		return (data->e_code);
	}
	return (R_SUCCESS);
}
