/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:33:42 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/16 18:03:32 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_loop(void *param);
void	init_params(t_cube *cube);
void	draw_player(t_player player, t_cube *cube);
void	draw_rays(t_player player, t_map map, t_cube *cube);

int		g_map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0,
			0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
			0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

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
	cube->map.blocks = g_map;
	cube->player.pos[X] = WIDTH / 4;
	cube->player.pos[Y] = HEIGHT / 2;
	cube->player.dir_angle = PI / 2;
	cube->player.step[X] = cos(cube->player.dir_angle) * 5;
	cube->player.step[Y] = sin(cube->player.dir_angle) * 5;
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
	draw_player(player, cube);
	draw_rays(player, map, cube);
}

void	draw_player(t_player player, t_cube *cube)
{
	float	dir_end[2];
	int		player_size;

	player_size = cube->map.block_size / 8 + 1;
	dir_end[X] = player.pos[X] + player.step[X] * 4;
	dir_end[Y] = player.pos[Y] + player.step[Y] * 4;
	draw_line(player.pos, dir_end, player.color, cube);
	player.pos[X] -= player_size / 2;
	player.pos[Y] -= player_size / 2;
	draw_block(player.pos, player_size, player.color, cube);
}

void	draw_rays(t_player player, t_map map, t_cube *cube)
{
	float	ray_angle;
	float	ray_end[2];
	float	ray_step[2];
	float	angle_tan;
	int		depth;
	int		current_cell;

	depth = 0;
	ray_angle = player.dir_angle;
	angle_tan = -1 / tan(ray_angle);
	if (ray_angle > PI)
	{
		ray_end[Y] = floor(player.pos[Y] / map.block_size) * map.block_size;
		ray_end[X] = (player.pos[Y] - ray_end[Y]) * angle_tan + player.pos[X];
		ray_step[Y] = -map.block_size;
		ray_step[X] = -ray_step[Y] * angle_tan;
	}
	if (ray_angle < PI)
	{
		ray_end[Y] = floor(player.pos[Y] / map.block_size) * map.block_size + map.block_size;
		ray_end[X] = (player.pos[Y] - ray_end[Y]) * angle_tan + player.pos[X];
		ray_step[Y] = map.block_size;
		ray_step[X] = -ray_step[Y] * angle_tan;
	}
	if (ray_angle == 0 || ray_angle == PI)
	{
		ray_end[X] = player.pos[X];
		ray_end[Y] = player.pos[Y];
		depth = 8;
	}
	while (depth < 8)
	{
		current_cell = ((int)ray_end[Y] / map.block_size) * map.width
			+ (int)ray_end[X] / map.block_size;
		if (current_cell < map.width * map.height && current_cell >= 0
			&& map.blocks[current_cell] == 1)
			break ;
		else
		{
			ray_end[X] += ray_step[X];
			ray_end[Y] += ray_step[Y];
			depth++;
		}
	}
	draw_line(player.pos, ray_end, 0x00FF00FF, cube);
}
