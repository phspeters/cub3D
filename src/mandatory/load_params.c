/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:01:34 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/23 21:24:40 by pehenri2         ###   ########.fr       */
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
	//int		screen[2];

	game->map.width = MAP_WIDTH;
	game->map.height = MAP_HEIGHT;
	game->map.minimap_block_size = 8;
	//mlx_get_monitor_size(0, &screen[X], &screen[Y]);
	//printf("screen size: %d %d\n", screen[X], screen[Y]);
	//game->screen_size[X] = screen[X];
	//game->screen_size[Y] = screen[Y];
	game->screen_size[X] = 1280;
	game->screen_size[Y] = 720;
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
	set_player_start_dir(game, 'W');
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
		game->player.plane[X] = 0.66;
	}
	else if (start_dir == 'N')
	{
		game->player.dir[Y] = -1;
		game->player.plane[X] = -0.66;
	}
}

void	load_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->north_texture = mlx_load_png("./assets/redbrick.png");
	if (!map->north_texture)
		handle_mlx_error(game);
	map->south_texture = mlx_load_png("./assets/colorstone.png");
	if (!map->south_texture)
		handle_mlx_error(game);
	map->west_texture = mlx_load_png("./assets/purplestone.png");
	if (!map->west_texture)
		handle_mlx_error(game);
	map->east_texture = mlx_load_png("./assets/greystone.png");
	if (!map->east_texture)
		handle_mlx_error(game);
	map->door_texture = mlx_load_png("./assets/eagle.png");
	if (!map->door_texture)
		handle_mlx_error(game);
	map->ceiling = 0x87CEEBFF;
	map->floor = 0xC0C0C0FF;
}
