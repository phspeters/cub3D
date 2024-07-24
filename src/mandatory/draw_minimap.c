/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:46:33 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/23 21:10:35 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_game *game)
{
	t_map	map;
	int		x;
	int		y;
	double	start[2];
	double	x_offset;

	map = game->map;
	x_offset = game->screen_size[X] - map.width * map.minimap_block_size;
	y = -1;
	while (++y < map.height)
	{
		x = -1;
		while (++x < map.width)
		{
			start[X] = x * map.minimap_block_size + x_offset;
			start[Y] = y * map.minimap_block_size;
			if (g_map[y][x] == 1)
				draw_block(start, map.minimap_block_size, 0xFFFFFFFF, game);
			else if (g_map[y][x] == 'D' || g_map[y][x] == - 'D')
				draw_block(start, map.minimap_block_size, 0x0000FFFF, game);
			else
				draw_block(start, map.minimap_block_size, 0x000000FF, game);
		}
	}
	draw_player(game);
}

void	draw_player(t_game *game)
{
	t_player	player;
	double		x_offset;
	int			minimap_scale;
	int			dir_end[2];
	int			plane[2];

	player = game->player;
	minimap_scale = game->map.minimap_block_size;
	x_offset = game->screen_size[X] - game->map.width * minimap_scale;
	player.pos[X] = (player.pos[X] - player.dir[X]) * minimap_scale + x_offset;
	player.pos[Y] = (player.pos[Y] - player.dir[Y]) * minimap_scale;
	dir_end[X] = (int)(player.pos[X] + player.dir[X] * minimap_scale);
	dir_end[Y] = (int)(player.pos[Y] + player.dir[Y] * minimap_scale);
	plane[X] = (int)(player.pos[X] + player.plane[X] * minimap_scale / 2);
	plane[Y] = (int)(player.pos[Y] + player.plane[Y] * minimap_scale / 2);
	draw_line(plane, dir_end, player.minimap_color, game);
	plane[X] = (int)(player.pos[X] - player.plane[X] * minimap_scale / 2);
	plane[Y] = (int)(player.pos[Y] - player.plane[Y] * minimap_scale / 2);
	draw_line(plane, dir_end, player.minimap_color, game);
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
