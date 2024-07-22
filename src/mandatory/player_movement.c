/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:19:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/22 18:21:10 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_forward_backward(t_game *game, t_player *player,
		double move_speed, double collision_distance)
{
	if (mlx_is_key_down(game->window, MLX_KEY_W))
	{
		if (g_map[(int)player->pos[Y]][(int)(player->pos[X] + player->dir[X]
			* (move_speed + collision_distance))] <= 0)
			player->pos[X] += player->dir[X] * move_speed;
		if (g_map[(int)(player->pos[Y] + player->dir[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= 0)
			player->pos[Y] += player->dir[Y] * move_speed;
	}
	if (mlx_is_key_down(game->window, MLX_KEY_S))
	{
		if (g_map[(int)player->pos[Y]][(int)(player->pos[X] - player->dir[X]
			* (move_speed + collision_distance))] <= 0)
			player->pos[X] -= player->dir[X] * move_speed;
		if (g_map[(int)(player->pos[Y] - player->dir[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= 0)
			player->pos[Y] -= player->dir[Y] * move_speed;
	}
}

void	strafe_player_left_right(t_game *game, t_player *player,
		double move_speed, double collision_distance)
{
	if (mlx_is_key_down(game->window, MLX_KEY_D))
	{
		if (g_map[(int)player->pos[Y]][(int)(player->pos[X] + player->plane[X]
			* (move_speed + collision_distance))] <= 0)
			player->pos[X] += player->plane[X] * move_speed;
		if (g_map[(int)(player->pos[Y] + player->plane[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= 0)
			player->pos[Y] += player->plane[Y] * move_speed;
	}
	if (mlx_is_key_down(game->window, MLX_KEY_A))
	{
		if (g_map[(int)player->pos[Y]][(int)(player->pos[X] - player->plane[X]
			* (move_speed + collision_distance))] <= 0)
			player->pos[X] -= player->plane[X] * move_speed;
		if (g_map[(int)(player->pos[Y] - player->plane[Y] * (move_speed
					+ collision_distance))][(int)player->pos[X]] <= 0)
			player->pos[Y] -= player->plane[Y] * move_speed;
	}
}

void	keyboard_rotate_player(t_game *game, t_player *player, double rot_speed)
{
	if (mlx_is_key_down(game->window, MLX_KEY_LEFT))
		rotate_direction_and_plane(player, rot_speed, LEFT);
	if (mlx_is_key_down(game->window, MLX_KEY_RIGHT))
		rotate_direction_and_plane(player, rot_speed, RIGHT);
}

void	mouse_rotate_player(t_game *game, t_player *player, double rot_speed)
{
	int32_t	mouse_pos[2];

	mlx_set_cursor_mode(game->window, MLX_MOUSE_HIDDEN);
	if (mlx_is_mouse_down(game->window, MLX_MOUSE_BUTTON_LEFT))
		player->is_mouse_active = !player->is_mouse_active;
	if (!player->is_mouse_active)
		return ;
	mlx_get_mouse_pos(game->window, &mouse_pos[X], &mouse_pos[Y]);
	if (mouse_pos[X] != SCREEN_WIDTH / 2)
	{
		if (mouse_pos[X] > SCREEN_WIDTH / 2)
			rotate_direction_and_plane(player, rot_speed, RIGHT);
		else
			rotate_direction_and_plane(player, rot_speed, LEFT);
	}
	mlx_set_mouse_pos(game->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

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
