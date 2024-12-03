/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:19:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/28 14:55:50 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief handles the player's rotation based on keyboard input. It checks if
 * the left or right arrow keys are pressed and rotates the player's direction
 * and plane accordingly.
 *
 * @param game struct containing the game data
 * @param player struct containing the player's data
 * @param rot_speed multiplier for the player's rotation speed
 */
void	keyboard_rotate_player(t_game *game, t_player *player, double rot_speed)
{
	if (mlx_is_key_down(game->window, MLX_KEY_LEFT))
		rotate_direction_and_plane(player, rot_speed, LEFT);
	if (mlx_is_key_down(game->window, MLX_KEY_RIGHT))
		rotate_direction_and_plane(player, rot_speed, RIGHT);
}

/**
 * @brief rotates the player based on the mouse's horizontal position. If the
 * mouse is to the right of the screen center, the player rotates right; if to
 * the left, the player rotates left. After adjusting the player's direction,
 * the function re-centers the mouse cursor to the middle of the screen.
 *
 * @param game struct containing the game data
 * @param player struct containing the player's data
 * @param rot_speed multiplier for the player's rotation speed
 */
void	mouse_rotate_player(t_game *game, t_player *player, double rot_speed)
{
	int32_t	mouse_pos[2];

	if (!player->is_mouse_active)
		return ;
	mlx_get_mouse_pos(game->window, &mouse_pos[X], &mouse_pos[Y]);
	if (mouse_pos[X] != game->screen_size[X] / 2)
	{
		if (mouse_pos[X] > game->screen_size[X] / 2)
			rotate_direction_and_plane(player, rot_speed, RIGHT);
		else
			rotate_direction_and_plane(player, rot_speed, LEFT);
	}
	mlx_set_mouse_pos(game->window, game->screen_size[X] / 2,
		game->screen_size[Y] / 2);
}

/**
 * @brief rotates the player's direction and camera plane vectors based
 * on the specified rotation speed and direction. It uses trigonometric
 * functions to calculate the new direction and plane vectors, allowing
 * the player to look left or right in the game.
 *
 * @param player struct containing the player's data
 * @param rot_speed multiplier for the player's rotation speed
 * @param direction which way the player should rotate (LEFT or RIGHT)
 */
void	rotate_direction_and_plane(t_player *player, double rot_speed,
		int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_speed;
	double	sin_speed;

	old_dir_x = player->dir[X];
	old_plane_x = player->plane[X];
	cos_speed = cos(direction * rot_speed);
	sin_speed = sin(direction * rot_speed);
	player->dir[X] = old_dir_x * cos_speed - player->dir[Y] * sin_speed;
	player->dir[Y] = old_dir_x * sin_speed + player->dir[Y] * cos_speed;
	player->plane[X] = old_plane_x * cos_speed - player->plane[Y] * sin_speed;
	player->plane[Y] = old_plane_x * sin_speed + player->plane[Y] * cos_speed;
}
