/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:17:01 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/16 20:30:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_loop(void *param)
{
	t_cube		*cube;
	t_entity	player;
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

void	draw_map(t_cube *cube, uint32_t color, t_map map)
{
	int		x;
	int		y;
	float	start[2];

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			start[X] = x * map.block_size;
			start[Y] = y * map.block_size;
			if (map.grid[(y * map.width) + x] == 1)
				draw_block (start, map.block_size, color, cube);
			else
				draw_block (start, map.block_size, 0x000000FF, cube);
			x++;
		}
		y++;
	}
}

void	draw_player(t_entity player, t_cube *cube)
{
	int	player_size;

	player_size = cube->map.block_size / 8;
	player.pos[X] -= player_size / 2;
	player.pos[Y] -= player_size / 2;
	draw_block(player.pos, player_size, player.color, cube);
}

void	draw_block(float start[2], int block_size, uint32_t color, t_cube *cube)
{
	int	x;
	int	y;

	y = start[Y];
	while (y < start[Y] + block_size - 1)
	{
		x = start[X];
		while (x < start[X] + block_size - 1)
		{
			put_valid_pixel(cube->image, x, y, color);
			x++;
		}
		y++;
	}
}
