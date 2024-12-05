/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/05 19:16:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	move_player_forward_backward(game, player, move_speed, collision_distance);
	strafe_player_left_right(game, player, move_speed, collision_distance);
	keyboard_rotate_player(game, player, rot_speed);
	mouse_rotate_player(game, player, rot_speed);
}

/**
 * @brief handles the Space key press event. When the Space key is pressed,
 * it performs actions related to opening doors and killing sprites in the
 * game.
 * 
 * @param keydata received key data
 * @param param pointer to the game struct
 */
void	keyboard_action_loop_hook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;

	game = param;
	if ((keydata.key == MLX_KEY_SPACE) && (keydata.action == MLX_PRESS))
	{
		open_doors(game, game->player.pos);
		kill_sprites(game, game->player.pos);
	}
	if ((keydata.key == MLX_KEY_M) && (keydata.action == MLX_PRESS))
		game->map.is_minimap_active = !game->map.is_minimap_active;
}

/**
 * @brief handles mouse button actions in the game.
 * When the right mouse button is pressed, it toggles the is_mouse_active
 * flag in the player structure. If the flag is active, the player can
 * rotate the camera using the mouse.
 * When the left mouse button is pressed, it performs actions related to
 * opening doors and killing sprites.
 * 
 * @param button mouse button pressed
 * @param action what action was performed
 * @param mod unused
 * @param param pointer to the game struct
 */
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
