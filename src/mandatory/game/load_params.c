/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:01:34 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/03 19:35:04 by pehenri2         ###   ########.fr       */
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

/**
 * @brief initializes the textures for different parts of the game map by
 * loading PNG images from specified file paths. It also sets the ceiling and
 * floor colors for the map.
 * 
 * @param game struct containing all game info
 */
void	load_map_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->textures[NORTH] = ft_load_png(game, game->map.texture_path[NORTH]);
	map->textures[SOUTH] = ft_load_png(game, game->map.texture_path[SOUTH]);
	map->textures[WEST] = ft_load_png(game, game->map.texture_path[WEST]);
	map->textures[EAST] = ft_load_png(game, game->map.texture_path[EAST]);
}
