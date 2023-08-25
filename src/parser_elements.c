/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_elements.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:23:04 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/25 16:19:31 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


bool	all_elements_found(int *tracker) // bool?
{
	int	i;

	i = 0;
	while (i < MAX_ID)
	{
		if (tracker[i] == false)
			return (false);
		i++;
	}
	return (true);
}


int path_textures_to_struct(char *line, char *surface, t_textures *textures)
{
	int	i;
	int		path_len;
	char	*rgb;
	
	i = 0;
	rgb = NULL;
	// while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	// 	i++;
	// printf("komt ie hier?\n");
	path_len = len_path(&line[i]);
	if (ft_strncmp(surface, "NO", LEN_ID) == 0)
	{
		textures->no = strip_path(&line[i]); // , path_len);
		printf("textures->no: [%s]\n", textures->no);
	}
	else if (ft_strncmp(surface, "SO", LEN_ID) == 0)
	{
		textures->so = strip_path(&line[i]); // , path_len);
		printf("textures->so: [%s]\n", textures->so);
	}	
	else if (ft_strncmp(surface, "WE", LEN_ID) == 0)
	{
		textures->we = strip_path(&line[i]); // , path_len);
		printf("textures->we: [%s]\n", textures->we);
	}
	else if (ft_strncmp(surface, "EA", LEN_ID) == 0)
	{
		textures->ea = strip_path(&line[i]); // , path_len);
		printf("textures->ea: [%s]\n", textures->ea);
	}
	else if (ft_strncmp(surface, "F ", LEN_ID) == 0)
	{
		rgb = strip_path(&line[i]); // , path_len);
		textures->f = str_to_rgb(rgb);
		printf("textures->f: [%d]\n", textures->f);
	}
	else if (ft_strncmp(surface, "C ", LEN_ID) == 0)
	{
		rgb = strip_path(&line[i]); // , path_len);
		textures->c = str_to_rgb(rgb);
		printf("textures->c: [%d]\n", textures->c);
	}
	else 
		fatal("dit hoort nooit te gebeuren\n"); // dit hoort nooit te gebeuren dus weghalen later maar is als check
	return (i + path_len); //+ 1); // + 1 voor de \n
}


int	get_elements(char *line, t_textures *textures) // ff kijken naar als j = 6, want dat heb ik nu veranderd
{
	int	i;
	size_t	j;
	char	*id[] = {"NO", "SO", "WE", "EA", "F ", "C "};
	int		tracker[] = {false, false, false, false, false, false};

	i = 0;
	j = 0;
	while (line[i] && line[i + 1] && j < MAX_ID)
	{
		// i = skip_empty(line, i);
		i = skip_chars(line, i, " \t\n");
		// while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
		// 	i++;
		while (line[i] && j < MAX_ID)
		{
			if (ft_strncmp(&line[i], id[j], LEN_ID) == 0)
			{
				printf("id: [%s]\n", id[j]);
				i += LEN_ID; // skip de id en geef de rest van de line mee aan de functie (points naar path/hexa of spaties bij correcte input)
				if (tracker[j] == true)
					fatal("Multiple paths for the same identification\n");
				tracker[j] = true;
				i += path_textures_to_struct(&line[i], id[j], textures);
				j = 0;
				break ;
			}
			j++;
		}
	}
	if (!all_elements_found(tracker))
		fatal("Invalid element formatting\n"); // line meegeven waar gevonden // KAN OF ELEMENTEN MISSENDE ZIJN OF TROEP TUSSEN DE ELEMENTEN
		// fatal("Missing texture element\n"); // als er troep tussen de elementen staat, dan is het geeft hij deze error message en dit is incorrect 
	return (i); // vanaf i moet de map beginnen
}
