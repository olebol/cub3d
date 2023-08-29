/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_elements.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:23:04 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/29 18:21:43 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


bool	all_elements_found(int *tracker) // bool?
{
	int	i;

	i = 0;
	while (i < ELEM_COUNT)
	{
		if (tracker[i] == false)
			return (false);
		i++;
	}
	return (true);
}


int path_textures_to_struct(char *line, char *surface, t_textures *textures, int id_len)
{
	int		len;
	char	*rgb;
	
	rgb = NULL;
	len = len_path(line);
	printf("path_len = %d\n", len);
	if (line[0] == '\n' || line[0] == '\0')
		fatal("No information for element given in this line\n");
	if (line[0] != ' ' && line[0] != '\t')
		fatal("Element identification is not separated\n"); 
	if (ft_strncmp(surface, elements(NORTH), id_len) == 0)
		textures->no = strip_path(line); // , path_len);
	else if (ft_strncmp(surface, elements(SOUTH), id_len) == 0)
		textures->so = strip_path(line); // , path_len);
	else if (ft_strncmp(surface, elements(WEST), id_len) == 0)
		textures->we = strip_path(line); // , path_len);
	else if (ft_strncmp(surface, elements(EAST), id_len) == 0)
		textures->ea = strip_path(line); // , path_len);
	else if (ft_strncmp(surface, elements(FLOOR), id_len) == 0)
	{
		rgb = strip_path(line); // , path_len);
		textures->f = str_to_rgb(rgb);
	}
	else if (ft_strncmp(surface, elements(CEILING), id_len) == 0)
	{
		rgb = strip_path(line); // , path_len);
		textures->c = str_to_rgb(rgb);
	}
	return (len);
}


int	get_elements(char *line, t_textures *textures) // ff kijken naar als j = 6, want dat heb ik nu veranderd
{
	int	i;
	int	id_len;
	int	j;
	char	*id[] = {"NO", "SO", "WE", "EA", "F", "C"};
	int		tracker[] = {false, false, false, false, false, false};

	i = 0;
	j = 0;
	while (line[i] && line[i + 1] && j < ELEM_COUNT)
	{
		i = skip_chars(line, i, " \t\n");
		while (j < ELEM_COUNT) // vgm hoeft line[i] niet
		{
			id_len = ft_strlen(id[j]);
			printf("j: [%d], id_len: [%d]\n", j, id_len);
			if (ft_strncmp(&line[i], id[j], id_len) == 0)
			{
				printf("id: [%s]\n", id[j]);
				i += id_len; // skip de id en geef de rest van de line mee aan de functie (points naar path/hexa of spaties bielem correcte input)
				if (tracker[j] == true)
					fatal("Multiple paths for the same identification\n");
				tracker[j] = true;
				i += path_textures_to_struct(&line[i], id[j], textures, id_len);
				printf("i: [%d], line: [%s]\n", i, &line[i]);
				j = 0;
				break ;
			}
			j++;
		}
	}
	if (!all_elements_found(tracker))
		fatal("Invalid element formatting (end loop)\n"); // line meegeven waar gevonden // KAN OF ELEMENTEN MISSENDE ZIJN OF TROEP TUSSEN DE ELEMENTEN
		// fatal("Missing texture element\n"); // als er troep tussen de elementen staat, dan is het geeft hij deze error message en dit is incorrect 
	return (i); // vanaf i moet de map beginnen
}
