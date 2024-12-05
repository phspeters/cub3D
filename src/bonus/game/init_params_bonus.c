/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:00:28 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/05 19:46:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	init_sprite_params(game);
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
	game->map.minimap_block_size = game->screen_size[Y] / 135;
	game->image = NULL;
	game->window = NULL;
	game->map.is_minimap_active = true;
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
	game->player.is_mouse_active = 0;
	game->player.dir[X] = 0;
	game->player.dir[Y] = 0;
	game->player.plane[X] = 0;
	game->player.plane[Y] = 0;
	game->player.wall_distance_on_camera_x = ft_safalloc(sizeof(double),
			(game->screen_size[X] + 1));
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
	while (++i < 5)
		game->map.texture_path[i] = NULL;
	i = -1;
	while (++i < 5)
		game->map.textures[i] = NULL;
	i = -1;
	while (++i < 9)
		game->map.sprite.texture[i] = NULL;
	i = -1;
	while (++i < 4)
		game->map.sprite.death_animation[i] = NULL;
	game->map.ceiling = 0;
	game->map.floor = 0;
}

void	init_sprite_params(t_game *game)
{
	game->map.sprite.killed = false;
}
