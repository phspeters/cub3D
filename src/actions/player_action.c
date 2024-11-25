/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:52:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/18 17:04:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief toggles the state of doors in the game map based on the player's
 * position. It iterates over the surrounding tiles within a 2-unit radius of
 * the player's current position and toggles the state of any doors found.
 *
 * @param game struct containing the game data
 * @param pos player's current x and y position
 */
void	open_doors(t_game *game, double pos[2])
{
	t_map	map;
	int		offset[2];
	int		cur[2];

	map = game->map;
	cur[X] = pos[X];
	cur[Y] = pos[Y];
	offset[X] = -2;
	while (++offset[X] < 2)
	{
		offset[Y] = -2;
		while (++offset[Y] < 2)
		{
			if (map.grid[cur[Y] + offset[Y]][cur[X] + offset[X]] == CLOSED_DOOR
				|| map.grid[cur[Y] + offset[Y]][cur[X]
				+ offset[X]] == OPEN_DOOR)
				map.grid[cur[Y] + offset[Y]][cur[X] + offset[X]] = \
					-map.grid[cur[Y] + offset[Y]][cur[X] + offset[X]];
		}
	}
}

/**
 * @brief responsible for marking a sprite as "killed" if the player's position
 * is within a certain proximity to the sprite's position.
 *
 * @param game struct containing the game data
 * @param pos player's current x and y position
 */
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
