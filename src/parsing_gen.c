/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_gen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:25:25 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/23 16:26:35 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// ERROR MESSAGES WITH THE LINE IN WHICH THE INCORRECT INPUT WAS FOUND (!!!)


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