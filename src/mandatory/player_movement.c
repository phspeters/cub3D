/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:19:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/18 16:58:46 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief handles the player's forward and backward movement by checking for
 * key presses (W and S) and updating the player's position accordingly. It
 * also checks for collisions with the game map to ensure the player does not
 * move into blocked areas.
 *
 * @param game struct containing the game data
 * @param player struct containing the player's data
 * @param move_speed multiplier for the player's movement speed
 * @param collision_distance multiplier for the player's collision distance
 */
void	move_player_forward_backward(t_game *game, t_player *player,
		double move_speed, double collision_distance)
{
	t_map	map;

	map = game->map;
	if (mlx_is_key_down(game->window, MLX_KEY_W))
	{
		if (map.grid[(int)player->pos[Y]][(int)(player->pos[X] + player->dir[X]
			* (move_speed + collision_distance))] <= EMPTY)
			player->pos[X] += player->dir[X] * move_speed;
		if (map.grid[(int)(player->pos[Y] + player->dir[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= EMPTY)
			player->pos[Y] += player->dir[Y] * move_speed;
	}
	if (mlx_is_key_down(game->window, MLX_KEY_S))
	{
		if (map.grid[(int)player->pos[Y]][(int)(player->pos[X] - player->dir[X]
			* (move_speed + collision_distance))] <= EMPTY)
			player->pos[X] -= player->dir[X] * move_speed;
		if (map.grid[(int)(player->pos[Y] - player->dir[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= EMPTY)
			player->pos[Y] -= player->dir[Y] * move_speed;
	}
}

/**
 * @brief handles the player's strafing movement by checking for key presses
 * (D and A) and updating the player's position accordingly. It also checks
 * for collisions with the game map to ensure the player does not move into
 * blocked areas.
 *
 * @param game struct containing the game data
 * @param player struct containing the player's data
 * @param move_speed multiplier for the player's movement speed
 * @param collision_distance multiplier for the player's collision distance
 */
void	strafe_player_left_right(t_game *game, t_player *player,
		double move_speed, double collision_distance)
{
	t_map	map;

	map = game->map;
	if (mlx_is_key_down(game->window, MLX_KEY_D))
	{
		if (map.grid[(int)player->pos[Y]][(int)(player->pos[X]
			+ player->plane[X] * (move_speed + collision_distance))] <= EMPTY)
			player->pos[X] += player->plane[X] * move_speed;
		if (map.grid[(int)(player->pos[Y] + player->plane[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= EMPTY)
			player->pos[Y] += player->plane[Y] * move_speed;
	}
	if (mlx_is_key_down(game->window, MLX_KEY_A))
	{
		if (map.grid[(int)player->pos[Y]][(int)(player->pos[X]
			- player->plane[X] * (move_speed + collision_distance))] <= EMPTY)
			player->pos[X] -= player->plane[X] * move_speed;
		if (map.grid[(int)(player->pos[Y] - player->plane[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= EMPTY)
			player->pos[Y] -= player->plane[Y] * move_speed;
	}
}

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
