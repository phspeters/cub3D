/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/22 18:30:33 by pehenri2         ###   ########.fr       */
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
	move_speed = game->window->delta_time * 5.0;
	rot_speed = game->window->delta_time * 3.0;
	collision_distance = move_speed * 5;
	move_player_forward_backward(game, player, move_speed, collision_distance);
	strafe_player_left_right(game, player, move_speed, collision_distance);
	keyboard_rotate_player(game, player, rot_speed);
	mouse_rotate_player(game, player, rot_speed);
}

void	player_action_loop_hook(void *param)
{
	t_game		*game;
	t_map		*map;
	int			offset[2];
	int			cur[2];

	game = param;
	map = &game->map;
	cur[X] = (int)game->player.pos[X];
	cur[Y] = (int)game->player.pos[Y];
	if (mlx_is_key_down(game->window, MLX_KEY_SPACE))
	{
		offset[X] = -2;
		while (++offset[X] < 2)
		{
			offset[Y] = -2;
			while (++offset[Y] < 2)
			{
				if (g_map[cur[Y] + offset[Y]][cur[X] + offset[X]] == 'D'
					|| g_map[cur[Y] + offset[Y]][cur[X] + offset[X]] == - 'D')
					g_map[cur[Y] + offset[Y]][cur[X] + offset[X]] = \
						-g_map[cur[Y] + offset[Y]][cur[X] + offset[X]];
			}
		}
	}
}
