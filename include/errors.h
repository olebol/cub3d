/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/27 17:08:10 by opelser       #+#    #+#                 */
/*   Updated: 2024/03/26 15:21:15 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum s_error
{
	E_MALLOC = 1,
	E_READ,
	E_ARGC,
	E_MLX_INIT,
	E_IMAGE_INIT,
	E_FILE_EXTENSION,
	E_FILE,
	E_ELEM_DUPLICATE,
	E_ELEM_ID,
	E_ELEM_MISSING,
	E_ELEM_RGB,
	E_ELEM_VALUE,
	E_PLAYER_DUP,
	E_MAP_EMPTY,
	E_MAP_INVALID,
	E_PLAYER_NO,
	E_MAP_UNCLOSED,
	E_MAP_DOOR,
}			t_error;

/**
 * @brief Prints an error message and exits with the given exit code
*/
void	error(t_error exit_code);

#endif
