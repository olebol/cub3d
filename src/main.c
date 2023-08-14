/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 18:25:42 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc == 2)
		parse_map(argv[1], &map);

	// print map
	for (map.x = 0; map.x < 10; map.x++)
	{
		for (map.y = 0; map.y < 10; map.y++)
			printf("%c", map.map[map.x][map.y]);
		printf("\n");
	}
}
