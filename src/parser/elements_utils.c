/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:42:17 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 15:25:46 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

size_t	skip_empty(const char *content, size_t i)
{
	while (content[i] && (content[i] == ' ' || content[i] == '\t' || \
			content[i] == '\n'))
		i++;
	return (i);
}

int	check_element_path(char *path, t_data *data)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == ' ' || path[i] == '\t')
			return (set_error(data, E_ELEM_VALUE));//, R_ELEM_VALUE));
		i++;
	}
	return (E_SUCCESS);
}

char	*strip_path(char *line, int start)
{
	char	*path;
	int	len;

	while (line[start] && (line[start] == ' ' || line[start] == '\t'))
		start++;
	len = start;
	while (line[len] && line[len] != '\n')
		len++;
	while (len > start && (line[len] == ' ' || line[len] == '\t'))
		len--;
	path = (char *)ft_malloc((len - start + 1) * sizeof(char));
	ft_strlcpy(path, &line[start], len - start + 1);
	if (!path) // ? -> controleren als map een leeg is
		return (NULL);
	return (path);
}

bool compare_ids(char *str, char *id)
{
	int	id_len;

	id_len = ft_strlen(id);
	if (ft_strncmp(str, id, id_len) == E_SUCCESS)
	{
		if (str[id_len] == ' ' || str[id_len] == '\t' || \
				str[id_len] == '\n' || str[id_len] == '\0')
			return (true);
	}
	return (false);
}

bool	elements_missing(int *tracker)
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
