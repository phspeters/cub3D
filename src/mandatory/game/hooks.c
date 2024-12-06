/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/05 21:35:49 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief checks if the Escape key is pressed. If it is, the function closes
 * the game window.
 * 
 * @param param pointer to the game struct
 */
void	close_loop_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->window, MLX_KEY_ESCAPE))
		mlx_close_window(game->window);
}

/**
 * @brief updates the player's movement and rotation continuously based on user
 * input and the elapsed time. It calculates the movement and rotation speeds,
 * checks for collisions, and calls appropriate functions to handle
 * forward/backward movement, strafing, and rotation using both keyboard and
 * mouse inputs.
 * 
 * @param param pointer to the game struct
 */
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
	move_player_forwaard_backward(game, player, move_speed, collision_distance);
	strafe_player_left_right(game, player, move_speed, collision_distance);
	keyboard_rotate_player(game, player, rot_speed);
}
