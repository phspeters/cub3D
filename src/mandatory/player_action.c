/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:52:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/29 18:13:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_doors(t_game *game, double pos[2])
{
	t_map	map;
	int		offset[2];
	int		cur[2];

	map = game->map;
	(void)map;
	cur[X] = pos[X];
	cur[Y] = pos[Y];
	offset[X] = -2;
	while (++offset[X] < 2)
	{
		offset[Y] = -2;
		while (++offset[Y] < 2)
		{
			if (g_map[cur[Y] + offset[Y]][cur[X] + offset[X]] == 'D'
				|| g_map[cur[Y] + offset[Y]][cur[X] + offset[X]] == - 'D')
				g_map[cur[Y] + offset[Y]][cur[X] + offset[X]] = -g_map[cur[Y]
					+ offset[Y]][cur[X] + offset[X]];
		}
	}
}

void	kill_sprites(t_game *game, double pos[2])
{
	t_map	*map;

	map = &game->map;
	if (map->sprite.pos[X] > pos[X] - 1 && map->sprite.pos[X] < pos[X] + 1
		&& map->sprite.pos[Y] > pos[Y] - 1 && map->sprite.pos[Y] < pos[Y] + 1)
	{
		map->sprite.killed = 1;
	}
}
