/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:08:10 by opelser           #+#    #+#             */
/*   Updated: 2024/07/06 19:15:22 by opelser          ###   ########.fr       */
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
	E_FILE_EMPTY,
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
}			t_error;

/**
 * @brief Prints an error message and exits with the given exit code
*/
void	error(t_error exit_code);

#endif
