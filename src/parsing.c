/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:25:25 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/17 18:47:40 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// ERROR MESSAGES WITH THE LINE IN WHICH THE INCORRECT INPUT WAS FOUND (!!!)

// void	check_valid_chars(char *map) // dit kan pas wanneer map in een eigen string staat
// {
// 	size_t	i;
// 	size_t	player;

// 	i = 0;
// 	player = 0;
// 	while (map[i])
// 	{
// 		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'E' || map[i] == 'W')
// 			player++;
// 		else if (map[i] != '0' && map[i] != '1' && map[i] != '2' && map[i] != '\n' && map[i] != ' ')
// 			fatal("Invalid character in map\n", 2);
// 		i++;
// 	}
// 	if (player != 1)
// 		fatal("Invalid number of players\n", 2);
// }

void	copy_map_to_array(t_map *map, char *line, int len)
{
	int	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] && i < len)
	{
		if (line[i] == '\n')
		{
			j++;
			k = 0;
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

// int	map_width(char *line, int height)
// {
// 	size_t	width;

// 	width = 0;
// 	while (line[width] != '\n' && line[width] != '\0')
// 		width++;
// 	return (width);
// }

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
		if (ret == -1)
			fatal_perror("Read failed\n");
		line = ft_strjoin(line, temp);
		ret = read(fd, temp, 1);
	}
	free(temp);
	return (line);
}

int	len_path(char *line)
{
	int	line_len;
	int	path_len;

	line_len = 0;
	while (line[line_len] && line[line_len] != '\n')
		line_len++;
	path_len = line_len;
	// printf("line[path_len]: %s\n", &line[path_len]);
	while (path_len > 0 && (line[path_len] == ' ' || line[path_len] == '\t'))
	{ // >= 0? 
		path_len--;
	}
	// printf("path_len: %d\n", path_len);
	// printf(">>>%c<<<\n", line[path_len]);
	return (path_len);
}

// unsigned int	rgb_to_hexa(int r, int g, int b)
// {
// 	return (r << 16 | g << 8 | b);
// }

bool	is_valid_rgb(int value)
{
	return (value >= 0 && value <= 255);
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

char	*strip_path(char *line, int path_len) // hier probeer ik de spaties op het eind te verwijderen maar so far not so good
{
	char	*path;
	int		end_len;
	int		i;

	i = 0;
	end_len = path_len;
	while (end_len > 0 && (line[end_len] == ' ' || line[end_len] == '\t'))
		end_len--;
		printf("end_len: %d, path_len: %d\n", end_len, path_len);
	path = (char *) malloc((end_len + 1) * sizeof(char));
	if (!path)
		fatal_perror("Malloc failed\n");
	while (i < end_len)
	{
		path[i] = line[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

int	parse_rgb_component(char *str)
{
	int value;

	value = 0;
	if (!str)
		return (-1);
	while (*str) // != '\0' ?
	{
		if (*str == ',')
			break ;
		if (ft_isdigit(*str))
			value = value * 10 + (*str - '0');
		else
			return (-1);
		str++;
	}
	if (!is_valid_rgb(value))
		return (-1);
	if (*str == ',')
		str++;
	return (value);
}

unsigned int	get_rgb_color(char *rgb) // miss even andere naam bedenken
{
	int	r;
	int	g;
	int	b;

	r = parse_rgb_component(rgb);
	g = parse_rgb_component(rgb);
	b = parse_rgb_component(rgb);
	if (r == -1 || g == -1 || b == -1)
		fatal("Invalid input format\n");
	return (r << 16 | g << 8 | b);
}

bool	all_elements_found(int *tracker) // bool?
{
	int	i;

	i = 0;
	while (i < MAX_ID)
	{
		if (tracker[i] == 0)
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
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path_len = len_path(&line[i]);
	// printf("path_len: %d, surface: %s\n", path_len, surface);
	// printf("WE = %d\n", ft_strncmp(surface, "WE", 2));
	if (ft_strncmp(surface, "NO", 2) == 0)
	{
		textures->no = strip_path(&line[i], path_len);
		printf("textures->no: [%s]\n", textures->no);
	}
	else if (ft_strncmp(surface, "SO", 2) == 0)
	{
		textures->so = strip_path(&line[i], path_len);
		printf("textures->so: [%s]\n", textures->so);
	}	
	else if (ft_strncmp(surface, "WE", 2) == 0)
	{
		textures->we = strip_path(&line[i], path_len);
		printf("textures->we: [%s]\n", textures->we);
	}
	else if (ft_strncmp(surface, "EA", 2) == 0)
	{
		textures->ea = strip_path(&line[i], path_len);
		printf("textures->ea: [%s]\n", textures->ea);
	}
	else if (ft_strncmp(surface, "F ", 2) == 0)
	{
		rgb = strip_path(&line[i], path_len);
		textures->f = get_rgb_color(rgb);
		printf("textures->f: [%d]\n", textures->f);
	}
	else if (ft_strncmp(surface, "C ", 2) == 0)
	{
		rgb = strip_path(&line[i], path_len);
		textures->c = get_rgb_color(rgb);
		printf("textures->c: [%d]\n", textures->c);
	}
	else 
		fatal("dit hoort nooit te gebeuren\n"); // dit hoort nooit te gebeuren dus weghalen later maar is als check
	return (i + path_len); //+ 1); // + 1 voor de \n
}

// paths naar alle elementen in de struct textures en hexadecimalen voor de kleuren van c en f
// checks of er geen troep tussen staat en of er geen dubbele id's zijn of missende id's

// elements en map in andere string want anders werkt deze functie niet

int	get_elements(char *line, t_textures *textures) // ff kijken naar als j = 6, want dat heb ik nu veranderd
{
	int	i;
	size_t	j;
	char	*id[] = {"NO", "SO", "WE", "EA", "F ", "C "};
	int		tracker[] = {0, 0, 0, 0, 0, 0};

	i = 0;
	j = 0;
	while (line[i] && line[i + 1] && j < MAX_ID)
	{
		// i = skip_empty(line, i);
		while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
			i++;
		while (line[i] && j < MAX_ID)
		{
			if (ft_strncmp(&line[i], id[j], 2) == 0)
			{
				i += 2; // skip de id en geef de rest van de line mee aan de functie (points naar path/hexa of spaties bij correcte input)
				if (tracker[j] == 1)
					fatal("Multiple paths for the same identification\n");
				tracker[j] = 1;
				i += path_textures_to_struct(&line[i], id[j], textures);
				j = 0;
				break ;
			}
			j++;
		}
	}
	if (!all_elements_found(tracker))
		fatal("Missing texture element\n"); // miss functie schrijven die checkt welk element er mist voor een specifiekere error message
	return (i); // vanaf i moet de map beginnen
}
	
bool	end_of_map(char *map, int i) // same als skip_empty, maar dan voor de map :((
{
	// printf("map = %s\n", map);
	while (map[i])
	{
		// printf("map[i]: %c\n", map[i]);
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
	// printf("line: %s\n", line);
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			player++;
		else if (line[i] == '\n')
		{
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
	// check_valid_chars(line, start_map);
	start_map = skip_empty(line, start_map);
	if (line[start_map] == '\0')
		fatal("No map found\n");
	end_map = check_map(&line[start_map], map) + start_map;
	printf("end_map: %d && %s\n", end_map, &line[end_map]);
	if (end_of_map(&line[end_map], 0) == false)
		fatal("Garbage after map\n");
	map->map = (char **) malloc((map->height + 1) * sizeof(char *));
	if (!map)
		fatal_perror("Malloc failed\n");
	map->map[map->height] = NULL;
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
	if (len >= EXTENSION_LEN)
		if (ft_strncmp(&infile[len - EXTENSION_LEN], EXTENSION, EXTENSION_LEN) == 0) // return  :)??
			return (true);
	return (false);
}

// void	set_paths_to_null(t_textures *textures)
// {
// 	textures->no = NULL;
// 	textures->so = NULL;
// 	textures->we = NULL;
// 	textures->ea = NULL;
// 	textures->f = NULL;
// 	textures->c = NULL;
// }

int	parse_infile(char *infile, t_map *map, t_textures *textures)
{
	int		i;
	int		fd;
	char	*line;
	// char	*map;
	// char	*elements;


	i = 0;
	if (!extension_check(infile))
		fatal("Invalid file extension\n");
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		fatal_perror("Invalid file\n");
	line = file_to_str(fd);
	// map = get_map(line);
	// check_valid_chars(line); // check of er geen rare chars in de map staan (alleen 0, 1, 2, N, S, E, W, \n, spatie (kan pas wann map in een eigen string staat)
	// set_paths_to_null(textures);
	split_elements_and_map(line, textures, map);
	
	// (void)map;

	// // height moet het aantal lines zijn van de map, dus alle \n moeten geteld worden (maar miss ook new lines na de map zelf, die moeten niet meegeteld worden)
	// map->height = map_height(line);

	// // width moet de langste line zijn, dus alle lines moeten geteld worden en de langste moet gepakt worden
	// map->width = map_width(line);

	// // check op gesloten map, dus omlijnd met 1 (let op spaties (ook binnen in de map??))

	// map->map = (char **) malloc((map->height + 1) * sizeof(char *));
	// if (!map->map)
	// {
	// 	ft_putstr_fd("Error\n", 2);
	// 	ft_putstr_fd("Malloc failed\n", 2);
	// 	exit(1);
	// }
	// map->map[map->height] = NULL;
	// while (i < map->height)
	// {
	// 	map->map[i] = (char *) malloc((map->width + 1) * sizeof(char));
	// 	if (!map->map[i])
	// 	{
	// 		ft_putstr_fd("Error\n", 2);
	// 		ft_putstr_fd("Malloc failed\n", 2);
	// 		exit(1);
	// 	}
	// 	map->map[i][map->width] = '\0';
	// 	i++;
	// }
	// copy_map_to_array(map, line);
	close(fd);
	return (0);
}