/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:17:01 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/18 20:45:24 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_delete_image(game->window, game->image);
	game->image = mlx_new_image(game->window, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(game->window, game->image, 0, 0);
	draw_3d_scene(game);
	draw_minimap(game);
}

void	draw_3d_scene(t_game *game)
{
	int	x_coordinate;

	x_coordinate = 0;
	while (x_coordinate <= SCREEN_WIDTH)
	{
		cast_ray(game, x_coordinate);
		x_coordinate++;
	}
}

void	draw_minimap(t_game *game)
{
	t_map	map;
	int		x;
	int		y;
	double	start[2];
	double	x_offset;

	map = game->map;
	x_offset = SCREEN_WIDTH - map.width * map.minimap_block_size;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			start[X] = x * map.minimap_block_size + x_offset;
			start[Y] = y * map.minimap_block_size;
			if (g_map[y][x] == 1)
				draw_block(start, map.minimap_block_size, 0xFFFFFFFF, game);
			else
				draw_block(start, map.minimap_block_size, 0x000000FF, game);
			x++;
		}
		y++;
	}
	draw_player(game);
}

void	draw_player(t_game *game)
{
	t_player	player;
	int			player_size;
	t_map		map;
	double		x_offset;

	map = game->map;
	x_offset = SCREEN_WIDTH - map.width * map.minimap_block_size;
	player = game->player;
	player_size = game->map.minimap_block_size / 2;
	player.pos[X] *= game->map.minimap_block_size;
	player.pos[Y] *= game->map.minimap_block_size;
	player.pos[X] += x_offset - player_size / 2;
	player.pos[Y] -= player_size / 2;
	draw_block(player.pos, player_size, player.color, game);
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
			put_valid_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}
