/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:40:08 by opelser       #+#    #+#                 */
/*   Updated: 2024/02/27 12:19:47 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <colors.h>
#include <stdlib.h>

void	ft_error(char *message)
{
	printf("%s%s", C_LRED, C_BOLD);
	printf("Error\n%s\n", message);
	printf("%s", C_RESET);
	exit(1);
}
