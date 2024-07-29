/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:01:34 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/29 18:14:30 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_game_params(t_game *game)
{
	load_map_and_screen_params(game);
	load_player_params(game);
	load_map_textures(game);
	load_sprite_textures(game);
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
	game->map.sprite.pos[X] = 21.5;
	game->map.sprite.pos[Y] = 11.5;
	game->map.sprite.killed = 0;
	game->map.sprite.frames_per_texture = 3;
}

void	load_player_params(t_game *game)
{
	game->player.pos[X] = 22;
	game->player.pos[Y] = 12;
	game->player.is_mouse_active = 0;
	game->player.dir[X] = 0;
	game->player.dir[Y] = 0;
	game->player.plane[X] = 0;
	game->player.plane[Y] = 0;
	game->player.wall_distance_on_camera_x = malloc(sizeof(double)
			* game->screen_size[X]);
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
