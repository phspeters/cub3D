/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/16 19:41:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	action_hooks(void *param)
{
	t_cube	*cube;

	cube = param;
	mlx_loop_hook(cube->window, close_loop_hook, cube);
	mlx_loop_hook(cube->window, move_player_loop_hook, cube);
}

void	close_loop_hook(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->window, MLX_KEY_ESCAPE))
		mlx_close_window(cube->window);
}

void	move_player_loop_hook(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->window, MLX_KEY_UP))
	{
		cube->player.pos[Y] += cube->player.movement_delta[Y];
		cube->player.pos[X] += cube->player.movement_delta[X];
	}
	if (mlx_is_key_down(cube->window, MLX_KEY_DOWN))
	{
		cube->player.pos[Y] -= cube->player.movement_delta[Y];
		cube->player.pos[X] -= cube->player.movement_delta[X];
	}
	if (mlx_is_key_down(cube->window, MLX_KEY_LEFT))
	{
		cube->player.dir_angle -= 0.1;
		if (cube->player.dir_angle < 0)
			cube->player.dir_angle += 2 * PI;
		cube->player.movement_delta[X] = cos(cube->player.dir_angle) * 5;
		cube->player.movement_delta[Y] = sin(cube->player.dir_angle) * 5;
	}
	if (mlx_is_key_down(cube->window, MLX_KEY_RIGHT))
	{
		cube->player.dir_angle += 0.1;
		if (cube->player.dir_angle > 2 * PI)
			cube->player.dir_angle -= 2 * PI;
		cube->player.movement_delta[X] = cos(cube->player.dir_angle) * 5;
		cube->player.movement_delta[Y] = sin(cube->player.dir_angle) * 5;
	}
}
