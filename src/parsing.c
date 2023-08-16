/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:25:25 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/16 17:21:34 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	copy_map_to_array(t_map *map, char *line)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i])
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

int	map_width(char *line, int height)
{
	size_t	width;

	width = 0;
	while (line[width] != '\n' && line[width] != '\0')
		width++;
	return (width);
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

	while (line[line_len] && line[line_len] != '\n')
		line_len++;
	path_len = line_len;
	while (path_len > 0 && line[path_len] == ' ')
		path_len--;
	return (path_len);
}

char	*strip_path(char *line, int path_len)
{
	char	*path;
	int		i;

	i = 0;
	path = (char *) malloc((path_len + 1) * sizeof(char));
	if (!path)
		fatal_perror("Malloc failed\n");
	while (i < path_len)
	{
		path[i] = line[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

void	path_textures_to_struct(char *line, char *surface, t_textures *textures)
{
	size_t	i;
	int		path_len;
	
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	path_len = len_path(line[i]);
	if (ft_strncmp(surface, "NO", 2) && textures->no == NULL)
		textures->no = strip_path(line[i], path_len);
	else if (ft_strncmp(surface, "SO", 2) && textures->so == NULL)
		textures->so = strip_path(line[i], path_len);
	else if (ft_strncmp(surface, "WE", 2) && textures->we == NULL)
		textures->we = strip_path(line[i], path_len);
	else if (ft_strncmp(surface, "EA", 2) && textures->ea == NULL)
		textures->ea = strip_path(line[i], path_len);

	
	// (!!!) voor f en c moet er nog een functie komen die de string met 3 getallen ranging van 0 tot 255 omzet naar een unsigned int
	
	// else if (ft_strncmp(surface, "F ", 2) && textures->f == NULL)
	// 	textures->f = ft_atoi_hexa(line[i]);
	// else if (ft_strncmp(surface, "C ", 2) && textures->c == NULL)
	// 	textures->c = ft_atoi_hexa(line[i]);
	
	else
		fatal("Multiple paths for the same identification\n");
}

void	get_path_to_textures(char *line, t_textures *textures)
{
	size_t	i;
	size_t	j;
	char	*id[] = {"NO", "SO", "WE", "EA", "F ", "C "};

	i = 0;
	j = 0;
	while (line[i] && line[i + 1])
	{
		while (line[i] == ' ' || line[i] == '\n')
			i++;
		while (j < 6)
		{
			if (ft_strncmp(line[i], id[j], 2) == 0)
			{
				i += 2;
				// while (line[i] && line[i] == ' ')
				// 	i++;
				path_textures_to_struct(&line[i], id[j], textures);
				break ;
			}
			j++;
		}
		// wat als er de id niet klopt > fix dit :)
		j = 0;
	}
	
}

bool	extension_check(char *infile)
{
	int	len;

	len = ft_strlen(infile);
	if (len >= EXTENSION_LEN)
		if (ft_strncmp(&infile[len - EXTENSION_LEN], EXTENSION, EXTENSION_LEN) == 0)
			return (true);
	return (false);
}

void	set_paths_to_null(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->f = NULL;
	textures->c = NULL;
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

	// check_valid_chars(line); // check of er geen rare chars in de map staan (alleen 0, 1, 2, N, S, E, W, \n, spatie (kan pas wann map in een eigen string staat)
	set_paths_to_null(&textures);
	get_path_to_textures(line, textures);
	

	// height moet het aantal lines zijn van de map, dus alle \n moeten geteld worden (maar miss ook new lines na de map zelf, die moeten niet meegeteld worden)
	map->height = map_height(line);

	// width moet de langste line zijn, dus alle lines moeten geteld worden en de langste moet gepakt worden
	map->width = map_width(line);

	// check op gesloten map, dus omlijnd met 1 (let op spaties (ook binnen in de map??))

	map->map = (char **) malloc((map->height + 1) * sizeof(char *));
	if (!map->map)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}
	map->map[map->height] = NULL;
	while (i < map->height)
	{
		map->map[i] = (char *) malloc((map->width + 1) * sizeof(char));
		if (!map->map[i])
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Malloc failed\n", 2);
			exit(1);
		}
		map->map[i][map->width] = '\0';
		i++;
	}
	copy_map_to_array(map, line);
	close(fd);
}