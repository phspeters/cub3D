/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:01:34 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/24 18:56:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_game_params(t_game *game)
{
	load_map_and_screen_params(game);
	load_player_params(game);
	load_textures(game);
}

void	load_map_and_screen_params(t_game *game)
{
	game->map.minimap_block_size = 8;
	game->map.width = MAP_WIDTH;
	game->map.height = MAP_HEIGHT;
	mlx_get_monitor_size(0, &game->screen_size[X], &game->screen_size[Y]);
	if (!game->screen_size[X] || !game->screen_size[Y])
	{
		game->screen_size[X] = SCREEN_WIDTH;
		game->screen_size[Y] = SCREEN_HEIGHT;
	}
}

void	load_player_params(t_game *game)
{
	game->player.pos[X] = 22;
	game->player.pos[Y] = 12;
	game->player.minimap_color = 0xFF0000FF;
	game->player.is_mouse_active = 0;
	game->player.dir[X] = 0;
	game->player.dir[Y] = 0;
	game->player.plane[X] = 0;
	game->player.plane[Y] = 0;
	set_player_start_dir(game, 'N');
}

void	set_player_start_dir(t_game *game, int start_dir)
{
	if (start_dir == 'W')
	{
		game->player.dir[X] = -1;
		game->player.plane[Y] = -0.66;
	}
	else if (start_dir == 'E')
	{
		game->player.dir[X] = 1;
		game->player.plane[Y] = 0.66;
	}
	else if (start_dir == 'S')
	{
		game->player.dir[Y] = 1;
		game->player.plane[X] = -0.66;
	}
	else if (start_dir == 'N')
	{
		game->player.dir[Y] = -1;
		game->player.plane[X] = 0.66;
	}
}

void	load_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->textures[NORTH] = mlx_load_png("./assets/redbrick.png");
	if (!map->textures[NORTH])
		handle_mlx_error(game);
	map->textures[SOUTH] = mlx_load_png("./assets/colorstone.png");
	if (!map->textures[SOUTH])
		handle_mlx_error(game);
	map->textures[WEST] = mlx_load_png("./assets/purplestone.png");
	if (!map->textures[WEST])
		handle_mlx_error(game);
	map->textures[EAST] = mlx_load_png("./assets/greystone.png");
	if (!map->textures[EAST])
		handle_mlx_error(game);
	map->textures[DOOR] = mlx_load_png("./assets/eagle.png");
	if (!map->textures[DOOR])
		handle_mlx_error(game);
	map->ceiling = 0x87CEEBFF;
	map->floor = 0xC0C0C0FF;
}
