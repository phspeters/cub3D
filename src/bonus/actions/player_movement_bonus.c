/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:19:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/05 19:16:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	t_map	*map;
	double	total_distance;
	double	next[2];

	map = &game->map;
	total_distance = move_speed + collision_distance;
	if (mlx_is_key_down(game->window, MLX_KEY_W))
	{
		next[X] = player->pos[X] + player->dir[X] * total_distance;
		next[Y] = player->pos[Y] + player->dir[Y] * total_distance;
		if (can_move_to_position(map, next[X], player->pos[Y]))
			player->pos[X] += player->dir[X] * move_speed;
		if (can_move_to_position(map, player->pos[X], next[Y]))
			player->pos[Y] += player->dir[Y] * move_speed;
	}
	if (mlx_is_key_down(game->window, MLX_KEY_S))
	{
		next[X] = player->pos[X] - player->dir[X] * total_distance;
		next[Y] = player->pos[Y] - player->dir[Y] * total_distance;
		if (can_move_to_position(map, next[X], player->pos[Y]))
			player->pos[X] -= player->dir[X] * move_speed;
		if (can_move_to_position(map, player->pos[X], next[Y]))
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
	t_map	*map;
	double	total_distance;
	double	next[2];

	map = &game->map;
	total_distance = move_speed + collision_distance;
	if (mlx_is_key_down(game->window, MLX_KEY_D))
	{
		next[X] = player->pos[X] + player->plane[X] * total_distance;
		next[Y] = player->pos[Y] + player->plane[Y] * total_distance;
		if (can_move_to_position(map, next[X], player->pos[Y]))
			player->pos[X] += player->plane[X] * move_speed;
		if (can_move_to_position(map, player->pos[X], next[Y]))
			player->pos[Y] += player->plane[Y] * move_speed;
	}
	if (mlx_is_key_down(game->window, MLX_KEY_A))
	{
		next[X] = player->pos[X] - player->plane[X] * total_distance;
		next[Y] = player->pos[Y] - player->plane[Y] * total_distance;
		if (can_move_to_position(map, next[X], player->pos[Y]))
			player->pos[X] -= player->plane[X] * move_speed;
		if (can_move_to_position(map, player->pos[X], next[Y]))
			player->pos[Y] -= player->plane[Y] * move_speed;
	}
}

bool	can_move_to_position(t_map *map, double x, double y)
{
	return (map->grid[(int)y][(int)x] <= EMPTY);
}
