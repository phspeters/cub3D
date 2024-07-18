/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/18 20:48:45 by pehenri2         ###   ########.fr       */
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
	double		old_dir_x;
	double		old_plane_x;
	double		collision_distance;

	game = param;
	player = &game->player;
	move_speed = game->window->delta_time * 5.0;
	rot_speed = game->window->delta_time * 3.0;
	collision_distance = 0.4;
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
