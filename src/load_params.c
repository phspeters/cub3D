/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:01:34 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/12 16:15:20 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief initializes various game parameters by calling helper functions to
 * load map and screen parameters, player parameters, map textures, and sprite
 * textures. Ensures that all necessary game data is loaded and initialized
 * before the game starts.
 *
 * @param game struct containing game data
 */
void	load_params(t_game *game)
{
	load_player_params(game);
	load_map_textures(game);
	load_sprite_textures(game);
	randomize_sprite_position(game);
}

/**
 * @brief sets the player's direction and plane vectors based on the starting
 * direction (start_dir).
 * 
 * @param game struct containing game data
 */
void	load_player_params(t_game *game)
{
	if (game->player.start_dir == 'W')
	{
		game->player.dir[X] = -1;
		game->player.plane[Y] = -0.66;
	}
	else if (game->player.start_dir == 'E')
	{
		game->player.dir[X] = 1;
		game->player.plane[Y] = 0.66;
	}
	else if (game->player.start_dir == 'S')
	{
		game->player.dir[Y] = 1;
		game->player.plane[X] = -0.66;
	}
	else if (game->player.start_dir == 'N')
	{
		game->player.dir[Y] = -1;
		game->player.plane[X] = 0.66;
	}
}
