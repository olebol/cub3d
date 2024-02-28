/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:43:42 by evalieve          #+#    #+#             */
/*   Updated: 2024/02/27 17:03:07 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_elems(t_elements *elements)
{
	if (elements->no)
		free(elements->no);
	if (elements->so)
		free(elements->so);
	if (elements->we)
		free(elements->we);
	if (elements->ea)
		free(elements->ea);
	if (elements->f)
		free(elements->f);
	if (elements->c)
		free(elements->c);
}
