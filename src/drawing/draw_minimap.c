/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:46:33 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/22 16:32:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief draws a MINIMAP_SIZE x MINIMAP_SIZE blocks minimap (Default 25).
 * The function iterates through each coordinate on the minimap, calling the
 * draw_minimap_block function to draw each block. The minimap is positioned
 * on the right side of the screen and centered around the player's position.
 *
 * @param game struct with game information
 */
void	draw_minimap(t_game *game)
{
	t_map	map;
	int		minimap_coord[2];
	int		start[2];
	double	x_offset;

	map = game->map;
	x_offset = game->screen_size[X] - MINIMAP_SIZE * map.minimap_block_size;
	start[X] = (int)(game->player.pos[X]) - MINIMAP_SIZE / 2;
	start[Y] = (int)(game->player.pos[Y]) - MINIMAP_SIZE / 2;
	minimap_coord[Y] = 0;
	while (minimap_coord[Y] < MINIMAP_SIZE)
	{
		minimap_coord[X] = 0;
		while (minimap_coord[X] < MINIMAP_SIZE)
		{
			draw_minimap_block(start, minimap_coord, x_offset, game);
			minimap_coord[X]++;
		}
		minimap_coord[Y]++;
	}
}

/**
 * @brief Draws a block of the minimap according to the minimap coordinates.
 * It determines the type of block (wall, door, or floor) based on the map
 * data and draws it at the appropriate position on the screen.
 *
 * @param start x and y coordinates of the top left corner of the block
 * @param minimap_coord x and y coordinates of the block in the minimap
 * @param x_offset offset to draw the minimap on the right side of the screen
 * @param game struct with game information
 */
void	draw_minimap_block(int start[2], int minimap_coord[2], double x_offset,
		t_game *game)
{
	t_map	map;
	double	block_start[2];

	map = game->map;
	map.current[X] = start[X] + minimap_coord[X];
	map.current[Y] = start[Y] + minimap_coord[Y];
	block_start[X] = minimap_coord[X] * map.minimap_block_size + x_offset;
	block_start[Y] = minimap_coord[Y] * map.minimap_block_size;
	if (map.current[X] >= 0 && map.current[X] < map.width && map.current[Y] >= 0
		&& map.current[Y] < map.height)
	{
		if (map.grid[map.current[Y]][map.current[X]] == WALL
			|| map.grid[map.current[Y]][map.current[X]] == VOID)
			draw_block(block_start, map.minimap_block_size, WALL_COLOR, game);
		else if (map.grid[map.current[Y]][map.current[X]] == CLOSED_DOOR
			|| map.grid[map.current[Y]][map.current[X]] == OPEN_DOOR)
			draw_block(block_start, map.minimap_block_size, DOOR_COLOR, game);
		else
			draw_block(block_start, map.minimap_block_size, FLOOR_COLOR, game);
	}
	else
		draw_block(block_start, map.minimap_block_size, WALL_COLOR, game);
}

/**
 * @brief Draws a block of block_size x block_size pixels with the specified
 * color at the specified start position from the top left corner.
 *
 * @param start x and y coordinates of the top left corner of the block
 * @param block_size size of the block in pixels
 * @param color rgba channel of the color to draw the block
 * @param game struct with game information
 */
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

/**
 * @brief Draws the player on the minimap as an arrow pointing in the direction
 * the player is facing. It uses the player's direction and plane vectors to
 * determine the end points of these lines and calls the draw_line function to
 * render them.
 * 
 * @param game struct with game information
 */
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
