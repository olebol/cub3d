/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:08:02 by opelser           #+#    #+#             */
/*   Updated: 2024/05/31 17:12:31 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "errors.h"

void	validate_elements(t_elements *elements, size_t loops)
{
	size_t		i;

	if (loops < TEXTURE_AMOUNT + 2)
		error(E_ELEM_MISSING);
	i = 0;
	while (i < TEXTURE_AMOUNT)
	{
		if (elements->textures[i] == NULL)
			error(E_ELEM_MISSING);
		i++;
	}
	if (elements->floor == 0x00000000 || elements->ceiling == 0x00000000)
		error(E_ELEM_MISSING);
}
