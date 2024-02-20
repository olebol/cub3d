/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:40:08 by opelser       #+#    #+#                 */
/*   Updated: 2023/08/16 14:41:42 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *message)
{
	printf("%s%s", C_LRED, C_BOLD);
	printf("Error\n%s\n", message);
	printf("%s", C_RESET);
	exit(1);
}
