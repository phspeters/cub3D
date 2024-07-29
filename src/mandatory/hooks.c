/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/29 18:14:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	move_speed = game->window->delta_time * MOVEMENT_SPEED_MULTIPLIER;
	rot_speed = game->window->delta_time * ROTATION_SPEED_MULTIPLIER;
	collision_distance = move_speed * COLLISION_DISTANCE_MULTIPLIER;
	move_player_forward_backward(game, player, move_speed, collision_distance);
	strafe_player_left_right(game, player, move_speed, collision_distance);
	keyboard_rotate_player(game, player, rot_speed);
	mouse_rotate_player(game, player, rot_speed);
}

void	keyboard_action_loop_hook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;
	t_map		*map;

	game = param;
	map = &game->map;
	(void)(map);
	if ((keydata.key == MLX_KEY_SPACE) && (keydata.action == MLX_PRESS))
	{
		open_doors(game, game->player.pos);
		kill_sprites(game, game->player.pos);
	}
}

void	mouse_action_loop_hook(mouse_key_t button, action_t action,
		modifier_key_t mod, void *param)
{
	t_game	*game;

	(void)mod;
	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		game->player.is_mouse_active = !game->player.is_mouse_active;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		open_doors(game, game->player.pos);
		kill_sprites(game, game->player.pos);
	}
}
