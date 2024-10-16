/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:53:17 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/16 19:29:50 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief  initializes the game window and image using the MLX library. It
 * handles errors at each step by calling handle_mlx_error if any of the MLX
 * functions fail. The function sets up the graphical components necessary to
 * start the game.
 *
 * @param game struct containing the game information
 */
void	start_game(t_game *game)
{
	game->window = mlx_init(game->screen_size[X], game->screen_size[Y],
			"Cube3D", false);
	if (!game->window)
		handle_mlx_error(game);
	game->image = mlx_new_image(game->window, game->screen_size[X],
			game->screen_size[Y]);
	if (!game->image)
		handle_mlx_error(game);
	if (mlx_image_to_window(game->window, game->image, 0, 0) == -1)
		handle_mlx_error(game);
}

/**
 * @brief sets up the main game loop by registering various event hooks for
 * drawing, closing, player movement, keyboard actions, and mouse actions.
 * It hides the mouse cursor and enters the main loop to keep the application
 * running and responsive to events.
 *
 * @param game struct containing the game information
 */
void	run_game_loop(t_game *game)
{
	if (!mlx_loop_hook(game->window, draw_loop, game))
		handle_mlx_error(game);
	if (!mlx_loop_hook(game->window, close_loop_hook, game))
		handle_mlx_error(game);
	if (!mlx_loop_hook(game->window, move_player_loop_hook, game))
		handle_mlx_error(game);
	mlx_key_hook(game->window, keyboard_action_loop_hook, game);
	mlx_mouse_hook(game->window, mouse_action_loop_hook, game);
	mlx_set_cursor_mode(game->window, MLX_MOUSE_HIDDEN);
	mlx_loop(game->window);
}

/**
 * @brief responsible for cleaning up and freeing all dynamically allocated
 * resources when the game ends. It frees the player's wall distance array,
 * deletes all textures associated with the map and sprites, and terminates
 * the MLX window to ensure that no memory leaks occur.
 *
 * @param game struct containing the game information
 */
void	end_game(t_game *game)
{
	int	i;

	i = -1;
	free(game->player.wall_distance_on_camera_x);
	while (++i < 5)
	{
		if (game->map.textures[i])
			mlx_delete_texture(game->map.textures[i]);
	}
	i = -1;
	while (++i < 9)
	{
		if (game->map.textures[i])
			mlx_delete_texture(game->map.sprite.texture[i]);
	}
	i = -1;
	while (++i < 4)
	{
		if (game->map.textures[i])
			mlx_delete_texture(game->map.sprite.death_animation[i]);
	}
	mlx_terminate(game->window);
}
