/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:52:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/05 19:16:33 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief toggles the state of doors in the game map based on the player's
 * position. It iterates over the surrounding tiles within a 2-unit radius of
 * the player's current position and toggles the state of any doors found.
 *
 * @param game struct containing the game data
 * @param player_pos player's current x and y position
 */
void	open_doors(t_game *game, double player_pos[2])
{
	t_map	map;
	int		delta[2];
	int		cur[2];
	int		tile[2];

	map = game->map;
	cur[X] = player_pos[X];
	cur[Y] = player_pos[Y];
	delta[X] = -1;
	while (delta[X] < 2)
	{
		delta[Y] = -1;
		while (delta[Y] < 2)
		{
			tile[X] = cur[X] + delta[X];
			tile[Y] = cur[Y] + delta[Y];
			if (map.grid[tile[Y]][tile[X]] == CLOSED_DOOR
				|| map.grid[tile[Y]][tile[X]] == OPEN_DOOR)
				map.grid[tile[Y]][tile[X]] = -map.grid[tile[Y]][tile[X]];
			delta[Y]++;
		}
		delta[X]++;
	}
}

/**
 * @brief responsible for marking a sprite as "killed" if the player's position
 * is within a 1 tile proximity to the sprite's position.
 *
 * @param game struct containing the game data
 * @param player_pos player's current x and y position
 */
void	kill_sprites(t_game *game, double player_pos[2])
{
	t_map	*map;

	map = &game->map;
	if (map->sprite.pos[X] > (player_pos[X] - 1)
		&& map->sprite.pos[X] < (player_pos[X] + 1)
		&& map->sprite.pos[Y] > (player_pos[Y] - 1)
		&& map->sprite.pos[Y] < (player_pos[Y] + 1))
	{
		map->sprite.killed = true;
	}
}
