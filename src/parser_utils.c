/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:24:58 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/23 16:26:14 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	skip_chars(char *line, int i, char *c)
{
	int j;

	j = 0;
	while (line[i])
	{
		while (c[j])
		{
			if (line[i] == c[j])
			{
				j = 0;
				break ;
			}
			j++;
		}
		if (c[j] == '\0')
			return (i);
		i++;
	}
	return (i);
}

int	skip_empty(char *line, int i)
{
	int nl;

	nl = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
	{
		if (line[i] == '\n')
			nl = i + 1;
		i++;
	}
	if (nl != 0)
		return (nl);
	return (i);
}


int	len_path(char *line) // HELL
{
	int	line_len;
	int	path_len;

	line_len = 0;
	while (line[line_len] && line[line_len] != '\n')
		line_len++;
	path_len = line_len; // ? 
	while (path_len > 0 && (line[path_len] == ' ' || line[path_len] == '\t'))
		path_len--;
	return (path_len);
}

int	get_path_len(char *line)
{
	int	path_len;
	int end;

	path_len = 0;
	while (line[path_len] && line[path_len] != '\n')
	{
		if (line[path_len] == ' ' || line[path_len] == '\t')
			break ;
		path_len++;
	}
	end = path_len;
	while (line[end] && line[end] != '\n')
	{
		if (line[end] != ' ' && line[end] != '\t')
			fatal("Multiple input for one element\n");
		end++;
	}
	return (path_len);
}

char	*strip_path(char *line)
{
	char	*path;
	int		path_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = skip_chars(line, i, " \t");
	path_len = get_path_len(&line[i]);
	path = (char *) malloc((path_len + 1) * sizeof(char));
	if (!path)
		fatal_perror("Malloc failed\n");
	path[path_len] = '\0';
	while (j < path_len)
	{
		path[j] = line[i];
		j++;
		i++;
	}
	return (path);
}


unsigned int	str_to_rgb(char *str)
{
	int	r;
	int	g;
	int	b;
	int i;
	

	i = 0;
	i += parse_rgb_component(str, &r);
	i += parse_rgb_component(&str[i], &g);
	parse_rgb_component(&str[i], &b);
	return (r << 16 | g << 8 | b);
}

int parse_rgb_component(char *str, int *comp)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	printf("str: [%s]\n", str);
	while (str[i] && str[i] != ',')
	{
		if (ft_isdigit(str[i]))
			value = value * 10 + (str[i] - '0');
		else
			fatal("Non digit in RGB value\n");
		i++;
	}
	if (is_valid_rgb(value))
		*comp = value;
	else
		fatal("RGB value is not valid [0-255]\n");
	return (i + 1);
}

bool	is_valid_rgb(int value)
{
	return (value >= 0 && value <= 255);
}

