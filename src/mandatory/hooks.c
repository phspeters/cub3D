/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/20 22:03:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	action_hooks(void *param)
{
	t_game	*game;

	game = param;
	mlx_loop_hook(game->window, close_loop_hook, game);
	mlx_loop_hook(game->window, move_player_loop_hook, game);
}

void	close_loop_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->window, MLX_KEY_ESCAPE))
		mlx_close_window(game->window);
}

void	move_player_loop_hook(void *param)
{
	t_game		*game;
	t_player	*player;
	double		move_speed;
	double		rot_speed;
	double		collision_distance;

	game = param;
	player = &game->player;
	move_speed = game->window->delta_time * 5.0;
	rot_speed = game->window->delta_time * 3.0;
	collision_distance = move_speed * 5;
	move_player(game, player, move_speed, collision_distance);
	rotate_player_right(game, player, rot_speed);
	rotate_player_left(game, player, rot_speed);
}
