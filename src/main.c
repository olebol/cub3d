/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 18:40:32 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc == 2)
		parse_map(argv[1], &map);

	// print map
	// for (map.width = 0; map.width < 10; map.width++)
	// {
	// 	for (map.height = 0; map.height < 10; map.height++)
	// 		printf("%c", map.map[map.width][map.height]);
	// 	printf("\n");
	// }

	int i = 0;
	int j = 0;
	while (map.map[i])
	{
		while (map.map[i][j])
		{
			printf("%c", map.map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}
