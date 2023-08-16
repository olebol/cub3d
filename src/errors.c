/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <evan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 13:45:10 by evan-der      #+#    #+#                 */
/*   Updated: 2023/08/16 15:19:46 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// fatal functie voor errors binnen de file (error\n) en voor buiten de file (perror)
// betere naam bedenken en checken hoe de output is als ze opgeroepen worden

void	fatal(char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	fatal_perror(char *error)
{
	ft_putstr_fd("Error\n", 2);
	perror(error);
	exit(EXIT_FAILURE);
}