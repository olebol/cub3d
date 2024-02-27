/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: evalieve <evalieve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/27 14:21:48 by evalieve      #+#    #+#                 */
/*   Updated: 2024/02/27 14:39:42 by evalieve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

ssize_t	ft_read_cubed(int fd, void *buf, size_t count)
{
	ssize_t	ret;

	ret = read(fd, buf, count);
	if (ret == ERROR)
	{
		fatal();
		return (ERROR);
	}
	return (ret);
}

char	*read_file(int fd)
{
	char	*content;
	char	*temp;
	char	*buf;
	int		ret;

	content = (char *)ft_malloc(1 * sizeof(char));
	content[0] = '\0';
	buf = (char *)ft_malloc((BUF_SIZE + 1) * sizeof(char));
	buf[BUF_SIZE] = '\0';
	ret = ft_read_cubed(fd, buf, BUF_SIZE);
	while (ret > 0)
	{
		temp = ft_strjoin(content, buf); // malloc handling!
		free(content);
		content = temp;
		ret = ft_read_cubed(fd, buf, BUF_SIZE);
	}
	free(buf);
	return (content);
}