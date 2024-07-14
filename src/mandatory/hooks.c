/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:40 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/14 18:59:13 by pehenri2         ###   ########.fr       */
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
		cube->player.pos[Y] -= 5;
	if (mlx_is_key_down(cube->window, MLX_KEY_DOWN))
		cube->player.pos[Y] += 5;
	if (mlx_is_key_down(cube->window, MLX_KEY_LEFT))
		cube->player.pos[X] -= 5;
	if (mlx_is_key_down(cube->window, MLX_KEY_RIGHT))
		cube->player.pos[X] += 5;
}
