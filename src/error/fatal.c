/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fatal.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:49:16 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 11:48:52 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// data structure meegeven om te free'en?
void	fatal(void)
{
	perror("CUB3D");
	exit(EXIT_FAILURE);
}
