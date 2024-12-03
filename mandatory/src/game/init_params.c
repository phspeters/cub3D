/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:00:28 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/03 19:34:46 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief serves as a high-level initializer that sets up various aspects of
 * the game by delegating the initialization tasks to more specific functions. 
 * 
 * @param game struct containing game data
 */
void	init_params(t_game *game)
{
	init_screen_params(game);
	init_player_params(game);
	init_textures_params(game);
}

/**
 * @brief initializes the screen size for the game by attempting to get the
 * monitor size. If it fails, it sets default screen dimensions. It also
 * calculates and sets the size of a block in the minimap based on the screen
 * height.
 * 
 * @param game struct containing game data
 */
void	init_screen_params(t_game *game)
{
	mlx_get_monitor_size(0, &game->screen_size[X], &game->screen_size[Y]);
	if (!game->screen_size[X] || !game->screen_size[Y])
	{
		game->screen_size[X] = SCREEN_WIDTH;
		game->screen_size[Y] = SCREEN_HEIGHT;
	}
	game->image = NULL;
	game->window = NULL;
}

/**
 * @brief initializes the player's parameters by setting initial values for
 * mouse activity, direction vector, and plane vector. It also allocates memory
 * for an array that will store wall distances along the X-axis of the camera. 
 * 
 * @param game struct containing game data
 */
void	init_player_params(t_game *game)
{
	game->player.player_count = 0;
	game->player.dir[X] = 0;
	game->player.dir[Y] = 0;
	game->player.plane[X] = 0;
	game->player.plane[Y] = 0;
}

/**
 * @brief initializes various texture-related arrays in the game structure
 * by setting each element to NULL. This includes texture paths, textures,
 * sprite textures, and death animation textures.
 * 
 * @param game struct containing game data
 */
void	init_textures_params(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		game->map.texture_path[i] = NULL;
	i = -1;
	while (++i < 4)
		game->map.textures[i] = NULL;
	game->map.ceiling = 0;
	game->map.floor = 0;
}
