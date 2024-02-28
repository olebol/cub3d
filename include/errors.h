/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:08:10 by opelser           #+#    #+#             */
/*   Updated: 2024/02/28 16:31:46 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "libft.h"

typedef enum s_error
{
	E_MALLOC,
	E_READ,
	E_ARGC,
	E_MLX_INIT,
	E_IMAGE_INIT,
	E_EXTENSION,
	E_FILE,
	E_ELEM_DUP,
	E_ELEM_ID,
	E_ELEM_MISS,
	E_RGB,
	E_ELEM_VALUE,
	E_PLAYER_DUP,
	E_INVALID_MAP,
	E_NO_PLAYER,
	E_UNCLOSED_MAP,
}			t_error;

/**
 * @brief Prints an error message and exits with the given exit code
*/
void	error(t_error exit_code);

#endif
