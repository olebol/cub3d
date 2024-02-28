/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:42:31 by opelser           #+#    #+#             */
/*   Updated: 2024/02/27 21:34:24 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			*strip_path(char *line, int start)
{
	char	*path;
	int		len;

	// can we use ft_strtrim here?
	while (line[start] && (line[start] == ' ' || line[start] == '\t'))
		start++;

	len = start;
	while (line[len] && line[len] != '\n')
		len++;

	while (len > start && (line[len] == ' ' || line[len] == '\t'))
		len--;

	path = (char *) ft_malloc((len - start + 1) * sizeof(char));
	ft_strlcpy(path, &line[start], len - start + 1);

	if (!path) // ? -> controleren als map een leeg is
		return (NULL);

	return (path);
}

static size_t	set_element(char *content, t_elements *elements, char *id)
{
	char	*path;
	int		id_len;

	id_len = ft_strlen(id);
	path = strip_path(content, id_len); // leaks

	if (ft_strcmp("NO", id) == 0)
		elements->no = path;
	else if (ft_strcmp("SO", id) == 0)
		elements->so = path;
	else if (ft_strcmp("WE", id) == 0)
		elements->we = path;
	else if (ft_strcmp("EA", id) == 0)
		elements->ea = path;
	else if (ft_strcmp("F", id) == 0)
		elements->f = path;
	else if (ft_strcmp("C", id) == 0)
		elements->c = path;

	return (ft_strlen(path) + id_len + 1);
}

static bool		compare_ids(char *str, char *id)
{
	const int		id_len = ft_strlen(id);

	if (ft_strncmp(str, id, id_len) == 0)
	{
		if (str[id_len] == ' ' || str[id_len] == '\t' || \
				str[id_len] == '\n' || str[id_len] == '\0')
			return (true);
	}
	return (false);
}

static size_t	skip_empty(const char *content)
{
	size_t	i;

	i = 0;
	while (content[i] &&
			(content[i] == ' ' || content[i] == '\t' || content[i] == '\n'))
	{
		i++;
	}

	return (i);
}

void		search_elements(t_elements *elements, \
							char *content, int *tracker, size_t *pos)
{
	char			*id[] = {"NO", "SO", "WE", "EA", "F", "C"};
	size_t			i;

	while (content[*pos])
	{
		*pos += skip_empty(content + *pos);

		i = 0;
		while (i < ELEM_COUNT && content[*pos])
		{
			if (compare_ids(content + *pos, id[i]))
			{
				write(1, content, 2);
				printf("pos : %zu\n", *pos);

				if (tracker[i] == true)
					error(E_ELEM_DUP);

				tracker[i] = true;

				*pos += set_element(content + *pos, elements, id[i]);

				break ;
			}
			i++;
		}

		if (i == ELEM_COUNT)
			error(E_ELEM_WRONG);
	}
}