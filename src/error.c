/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:43:51 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/28 17:52:09 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "colors.h"
#include "unistd.h"

const char	*ft_strerror(t_error error)
{
	static const char *messages[] = {
		[E_MALLOC]			= "Memory allocation failed",
		[E_READ]			= "Failed to read file",
		[E_ARGC]			= "Invalid number of arguments",
		[E_MLX_INIT]		= "Failed to initialize mlx",
		[E_IMAGE_INIT]		= "Failed to initialize an image",
		[E_EXTENSION]		= "Invalid file extension",
		[E_FILE]			= "Failed to open file",
		[E_ELEM_DUP]		= "Duplicate element found",
		[E_ELEM_ID]			= "Invalid element identifier",
		[E_ELEM_MISS]		= "Missing element",
		[E_RGB]				= "Invalid RGB value",
		[E_ELEM_VALUE]		= "Invalid element value",
		[E_PLAYER_DUP]		= "Duplicate player start position",
		[E_INVALID_MAP]		= "Invalid character in map",
		[E_NO_PLAYER]		= "No player start position found",
		[E_UNCLOSED_MAP]	= "Unclosed map",
	};

	return (messages[error]);
}

void	error(t_error exit_code)
{
	ft_putstr_fd(C_RED, STDERR_FILENO);
	ft_putendl_fd("CUB3D: ", STDERR_FILENO);
	ft_putendl_fd((char *) ft_strerror(exit_code), STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);

	exit(exit_code);
}
