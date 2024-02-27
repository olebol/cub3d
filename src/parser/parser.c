/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 17:42:50 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 14:19:40 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	verify_extension(const char *file, t_data *data)
{
	size_t	fn_len;

	fn_len = ft_strlen(file);
	if (fn_len < EXTENSION_LEN + 1 || \
			ft_strncmp(&file[fn_len - EXTENSION_LEN], EXTENSION, EXTENSION_LEN))
		return (set_error(data, E_EXTENSION));//, R_EXTENSION));
	return (R_SUCCESS);
}

int	parse_file(const char *file, t_data *data)
{
	int		fd;
	size_t	pos;
	char	*content;

	pos = 0;
	if (verify_extension(file, data) != R_SUCCESS)
		return (set_error(data, E_EXTENSION));//, R_EXTENSION));
	fd = open(file, O_RDONLY, 0);
	if (fd < 0)
		return (set_error(data, E_FILE));//, R_FILE)
	content = read_file(fd);
	close(fd);
	if (verify_elements(content, data, &pos) != R_SUCCESS)
		return (data->e_code);
	if (verify_map(content, data, &pos) != R_SUCCESS)
		return (data->e_code);
	free(content);
	return (R_SUCCESS);
}