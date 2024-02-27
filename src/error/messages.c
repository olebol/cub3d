/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:43:51 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 14:20:07 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

const char	*error_messages(t_error error)
{
	const char *messages[] = {
		[E_ARGC] = "Invalid number of arguments",
		[E_MLX_INIT] = "Failed to initialize mlx",
		[E_EXTENSION] = "Invalid file extension",
		[E_FILE] = "Failed to open file",
		[E_ELEM_DUP] = "Duplicate element found",
		[E_ELEM_WRONG] = "Invalid element identifier",
		[E_ELEM_MISS] = "Missing element",
		[E_RGB] = "Invalid RGB value",
		[E_ELEM_VALUE] = "Invalid element value",
		[E_PLAYER_DUP] = "Duplicate player start position",
		[E_INVALID_MAP] = "Invalid character in map",
		[E_NO_PLAYER] = "No player start position found",
		[E_UNCLOSED_MAP] = "Unclosed map",
	};

	return (messages[error]);
}

int	set_error(t_data *data, t_error e_code) //, t_return r_value)
{
	// data->r_value = e_code;//r_value;
	data->e_code = e_code;
	return (e_code);
}

int	error(t_data *data)
{
	ft_putstr_fd("CUB3D: ", STDERR_FILENO);
	ft_putstr_fd((char *)error_messages(data->e_code), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (data->e_code);
}
