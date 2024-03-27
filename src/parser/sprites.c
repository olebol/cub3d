/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opelser <opelser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:49:25 by opelser           #+#    #+#             */
/*   Updated: 2024/03/27 17:51:27 by opelser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"
#include "errors.h"

static void			add_sprite(t_data *data, t_sprite *new_sprite)
{
	t_sprite	*current;

	if (new_sprite == NULL)
		return ;

	if (data->sprites == NULL)
	{
		data->sprites = new_sprite;
		return ;
	}
	current = data->sprites;
	while (current->next)
		current = current->next;
	current->next = new_sprite;
}

static t_sprite		*create_sprite(t_data *data, double x, double y)
{
	t_sprite	*new_sprite;

	new_sprite = (t_sprite *) malloc(sizeof(t_sprite));
	if (new_sprite == NULL)
		error(E_MALLOC);

	new_sprite->texture = data->elements.textures[SPRITE];
	new_sprite->x = x;
	new_sprite->y = y;
	new_sprite->distance = 0;
	new_sprite->next = NULL;

	return (new_sprite);
}

void		find_sprites(t_map *map, t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '&')
			{
				add_sprite(data, create_sprite(data, x + 0.5, y + 0.5));
				map->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}