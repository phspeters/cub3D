/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:19:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/18 21:19:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, t_player *player, double move_speed,
		double collision_distance)
{
	if (mlx_is_key_down(game->window, MLX_KEY_UP))
	{
		if (g_map[(int)player->pos[Y]][(int)(player->pos[X] + player->dir[X]
			* (move_speed + collision_distance))] == 0)
			player->pos[X] += player->dir[X] * move_speed;
		if (g_map[(int)(player->pos[Y] + player->dir[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] == 0)
			player->pos[Y] += player->dir[Y] * move_speed;
	}
	if (mlx_is_key_down(game->window, MLX_KEY_DOWN))
	{
		if (g_map[(int)player->pos[Y]][(int)(player->pos[X] - player->dir[X]
			* (move_speed + collision_distance))] == 0)
			player->pos[X] -= player->dir[X] * move_speed;
		if (g_map[(int)(player->pos[Y] - player->dir[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] == 0)
			player->pos[Y] -= player->dir[Y] * move_speed;
	}
}

void	rotate_player_left(t_game *game, t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->window, MLX_KEY_LEFT))
	{
		old_dir_x = player->dir[X];
		player->dir[X] = player->dir[X] * cos(rot_speed) - player->dir[Y]
			* sin(rot_speed);
		player->dir[Y] = old_dir_x * sin(rot_speed) + player->dir[Y]
			* cos(rot_speed);
		old_plane_x = player->plane[X];
		player->plane[X] = player->plane[X] * cos(rot_speed) - player->plane[Y]
			* sin(rot_speed);
		player->plane[Y] = old_plane_x * sin(rot_speed) + player->plane[Y]
			* cos(rot_speed);
	}
}

void	rotate_player_right(t_game *game, t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->window, MLX_KEY_RIGHT))
	{
		old_dir_x = player->dir[X];
		player->dir[X] = player->dir[X] * cos(-rot_speed) - player->dir[Y]
			* sin(-rot_speed);
		player->dir[Y] = old_dir_x * sin(-rot_speed) + player->dir[Y]
			* cos(-rot_speed);
		old_plane_x = player->plane[X];
		player->plane[X] = player->plane[X] * cos(-rot_speed) - player->plane[Y]
			* sin(-rot_speed);
		player->plane[Y] = old_plane_x * sin(-rot_speed) + player->plane[Y]
			* cos(-rot_speed);
	}
}
