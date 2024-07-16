/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:33:42 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/16 20:19:51 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_params(t_cube *cube);

int			g_map[] = {
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
	cube.window = mlx_init(WIDTH, HEIGHT, "Xube3D", true);
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
	cube->map.grid = g_map;
	cube->player.pos[X] = WIDTH / 4;
	cube->player.pos[Y] = HEIGHT / 2;
	cube->player.dir_angle = PI / 2;
	cube->player.movement_delta[X] = cos(cube->player.dir_angle) * 5;
	cube->player.movement_delta[Y] = sin(cube->player.dir_angle) * 5;
	cube->player.color = 0xFF0000FF;
}
