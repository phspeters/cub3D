/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:33:42 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/14 19:03:41 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_loop(void *param);
void	init_params(t_cube *cube);

int	g_map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

int	main(void)
{
	t_cube	cube;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cube.window = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	cube.image = mlx_new_image(cube.window, WIDTH, HEIGHT);
	mlx_image_to_window(cube.window, cube.image, 0, 0);
	init_params(&cube);
	mlx_loop_hook(cube.window, draw_loop, &cube);
	action_hooks(&cube);
	mlx_loop(cube.window);
	mlx_terminate(cube.window);
	return (EXIT_SUCCESS);
}

void	init_params(t_cube *cube)
{
	cube->map.width = 8;
	cube->map.height = 8;
	cube->map.block_size = 64;
	cube->map.color = 0xFFFFFFFF;
	cube->map.cells = g_map;
	cube->player.pos[X] = WIDTH / 4;
	cube->player.pos[Y] = HEIGHT / 2;
	cube->player.color = 0xFF0000FF;
}

void	draw_loop(void *param)
{
	t_cube		*cube;
	t_player	player;
	t_map		map;

	cube = param;
	map = cube->map;
	player = cube->player;
	mlx_delete_image(cube->window, cube->image);
	cube->image = mlx_new_image(cube->window, WIDTH, HEIGHT);
	mlx_image_to_window(cube->window, cube->image, 0, 0);
	draw_map(cube, map.color, map);
	draw_block(player.pos, map.block_size / 4, player.color, cube);
}
