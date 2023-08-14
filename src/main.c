/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 17:14:46 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/14 17:32:56 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc == 2)
		parse_map(argv[1], &map);
}