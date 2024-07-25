/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:53:17 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/25 18:10:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	run_game_loop(t_game *game)
{
	if (!mlx_loop_hook(game->window, draw_loop, game))
		handle_mlx_error(game);
	if (!mlx_loop_hook(game->window, close_loop_hook, game))
		handle_mlx_error(game);
	if (!mlx_loop_hook(game->window, move_player_loop_hook, game))
		handle_mlx_error(game);
	mlx_key_hook(game->window, player_action_loop_hook, game);
	mlx_loop(game->window);
}

void	end_game(t_game *game)
{
	free(game->player.wall_distance);
	mlx_terminate(game->window);
}
