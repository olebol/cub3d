/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_gen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:25:25 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/18 18:39:01 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// ERROR MESSAGES WITH THE LINE IN WHICH THE INCORRECT INPUT WAS FOUND (!!!)

void	copy_map_to_array(t_map *map, char *line, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] && i < len)
	{
		if (line[i] == '\n' && k == map->width)
		{
			k = 0;
			j++;
		}
		else if (line[i] == '\n' && k < map->width)
		{
			while (k < map->width)
			{
				map->map[j][k] = ' ';
				k++;
			}
			k = 0;
			j++;
		}
		else
		{
			map->map[j][k] = line[i];
			k++;
		}
		i++;
	}
}

int map_height(char *line)
{
	size_t	height;
	size_t	i;

	height = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			height++;
		i++;
	}
	if (line[height - 1] != '\n') // even nadenken over hoe de laatste line eruit kan zien en wel of niet meetellen icm input file
		height++;
	return (height);
}

char	*file_to_str(int fd) // get_next_line style
{
	char	*line;
	char	*temp;
	int		ret;

	line = (char *) malloc(1 * sizeof(char));
	if (!line)
		fatal_perror("Malloc failed\n");
	line[0] = '\0';
	temp = (char *) malloc(2 * sizeof(char));
	if (!temp)
		fatal_perror("Malloc failed\n");
	temp[1] = '\0';
	ret = read(fd, temp, 1);
	while (ret > 0)
	{
		line = ft_strjoin(line, temp);
		ret = read(fd, temp, 1);
	}
	if (ret == -1)
			fatal_perror("Read failed\n");
	free(temp);
	return (line);
}

bool	is_valid_rgb(int value)
{
	return (value >= 0 && value <= 255);
}

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
				i += 2; // skip de id en geef de rest van de line mee aan de functie (points naar path/hexa of spaties bij correcte input)
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
		fatal("Invalid element formatting\n"); // line meegeven waar gevonden
		// fatal("Missing texture element\n"); // als er troep tussen de elementen staat, dan is het geeft hij deze error message en dit is incorrect 
	return (i); // vanaf i moet de map beginnen
}
	
bool	end_of_map(char *map, int i) // same als skip_empty, maar dan voor de map :((
{
	while (map[i])
	{
		if (map[i] != '\n' && map[i] != ' ' && map[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	check_map(char *line, t_map *map)
{
	int	i;
	int	player;
	int	width;

	i = 0;
	player = 0;
	width = 0;
	map->width = 0;
	map->height = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			map->x = width - 1;
			map->y = map->height;
			map->dir = line[i];
			player++; // ?? kan ook andere check hiervoor doen maar ok
		}
		else if (line[i] == '\n')
		{
			printf("width: %d\n", width);
			if (line[i - 1] && line[i - 1] == '\n')
				break ;
			if (width == 0 && end_of_map(line, i) == false)
				fatal("Invalid map\n"); // line of zo
			else if (width == 0 && end_of_map(line, i) == true)
				break ;
			map->height++;
			if (width > map->width)
				map->width = width;
			width = 0;
		}
		else if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != ' ')
		{
			if (i == 0)
				fatal("Garbage before map\n"); // line of zo
			fatal("Invalid character in map\n"); // line of zo
		}
		i++;
		width++;
	}
	if (line[i] == '\0' && width > 0)
		map->height++;
	if (width > map->width)
		map->width = width;
	if (player != 1)
		fatal("Invalid number of players\n"); // line of zo
	return (i);
}

void	split_elements_and_map(char *line, t_textures *textures, t_map *map)
{
	int		start_map;
	int		end_map;
	int		i;

	i = 0;

	start_map = get_elements(line, textures);
	start_map = skip_empty(line, start_map);
	if (line[start_map] == '\0')
		fatal("No map found\n");
	end_map = check_map(&line[start_map], map) + start_map;
	if (end_of_map(&line[end_map], 0) == false)
		fatal("Garbage after map\n");
	map->map = (char **) malloc((map->height + 1) * sizeof(char *));
	if (!map)
		fatal_perror("Malloc failed\n");
	// map->map[map->height] = NULL;
	printf("map->height: %d, map->width: %d\n", map->height, map->width);
	while (i < map->height)
	{
		map->map[i] = (char *) malloc((map->width + 1) * sizeof(char));
		if (!map->map[i])
			fatal_perror("Malloc failed\n");
		map->map[i][map->width] = '\0';
		i++;
	}
	copy_map_to_array(map, &line[start_map], end_map - start_map);	
}

bool	extension_check(char *infile) // bool?
{
	int	len;

	len = ft_strlen(infile);
	// return (len >= EXTENSION_LEN && ft_strncmp(&infile[len - EXTENSION_LEN], EXTENSION, EXTENSION_LEN) == 0);

	if (len >= EXTENSION_LEN)
		if (ft_strncmp(&infile[len - EXTENSION_LEN], EXTENSION, EXTENSION_LEN) == 0) // return  :)??
			return (true);
	return (false);
}

int	parse_infile(char *infile, t_map *map, t_textures *textures)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	if (!extension_check(infile))
		fatal("Invalid file extension\n");
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		fatal_perror("Invalid file\n");
	line = file_to_str(fd);
	split_elements_and_map(line, textures, map);
	printf("map->x: %d, map->y: %d, map->dir: %c\n", map->x, map->y, map->dir);
	close(fd);
	return (0);
}