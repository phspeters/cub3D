/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:46:33 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/24 20:08:10 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_game *game)
{
	t_map	map;
	int		counter[2];
	int		start[2];
	double	x_offset;

	map = game->map;
	x_offset = game->screen_size[X] - MINIMAP_SIZE * map.minimap_block_size;
	start[X] = (int)(game->player.pos[X]) - MINIMAP_SIZE / 2;
	start[Y] = (int)(game->player.pos[Y]) - MINIMAP_SIZE / 2;
	counter[Y] = 0;
	while (counter[Y] < MINIMAP_SIZE)
	{
		counter[X] = 0;
		while (counter[X] < MINIMAP_SIZE)
		{
			draw_minimap_block(start, counter, x_offset, game);
			counter[X]++;
		}
		counter[Y]++;
	}
}

void	draw_minimap_block(int start[2], int counter[2], double x_offset,
		t_game *game)
{
	t_map	map;
	double	block_start[2];

	map = game->map;
	map.current[X] = start[X] + counter[X];
	map.current[Y] = start[Y] + counter[Y];
	block_start[X] = counter[X] * map.minimap_block_size + x_offset;
	block_start[Y] = counter[Y] * map.minimap_block_size;
	if (map.current[X] >= 0 && map.current[X] < map.width && map.current[Y] >= 0
		&& map.current[Y] < map.height)
	{
		if (g_map[map.current[Y]][map.current[X]] == 1)
			draw_block(block_start, map.minimap_block_size, WALL_COLOR, game);
		else if (g_map[map.current[Y]][map.current[X]] == 'D'
			|| g_map[map.current[Y]][map.current[X]] == - 'D')
			draw_block(block_start, map.minimap_block_size, DOOR_COLOR, game);
		else
			draw_block(block_start, map.minimap_block_size, FLOOR_COLOR, game);
	}
	else
		draw_block(block_start, map.minimap_block_size, WALL_COLOR, game);
}

void	draw_block(double start[2], int block_size, uint32_t color,
		t_game *game)
{
	int	x;
	int	y;

	y = start[Y];
	while (y < start[Y] + block_size)
	{
		x = start[X];
		while (x < start[X] + block_size)
		{
			put_valid_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player_on_minimap(t_game *game)
{
	t_player	player;
	int			minimap_scale;
	int			dir_end[2];
	int			plane[2];
	double		offset[2];

	player = game->player;
	minimap_scale = game->map.minimap_block_size;
	offset[X] = game->screen_size[X] - (MINIMAP_SIZE * minimap_scale) / 2;
	offset[Y] = (MINIMAP_SIZE * minimap_scale) / 2;
	dir_end[X] = (int)(offset[X] + player.dir[X] * minimap_scale);
	dir_end[Y] = (int)(offset[Y] + player.dir[Y] * minimap_scale);
	plane[X] = (int)(offset[X] + player.plane[X] * minimap_scale / 2);
	plane[Y] = (int)(offset[Y] + player.plane[Y] * minimap_scale / 2);
	draw_line(plane, dir_end, PLAYER_COLOR, game);
	plane[X] = (int)(offset[X] - player.plane[X] * minimap_scale / 2);
	plane[Y] = (int)(offset[Y] - player.plane[Y] * minimap_scale / 2);
	draw_line(plane, dir_end, PLAYER_COLOR, game);
}
