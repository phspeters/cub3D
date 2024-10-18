/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:01:34 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/17 20:52:13 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief initializes various game parameters by calling helper functions to
 * load map and screen parameters, player parameters, map textures, and sprite
 * textures. Ensures that all necessary game data is loaded and initialized
 * before the game starts.
 *
 * @param game struct containing game data
 */
void	load_params(t_game *game)
{
	fake_load_map_params(game);
	load_player_params(game);
	load_map_textures(game);
	load_sprite_textures(game);
	randomize_sprite_position(game);
}

//TEMPORARY FUNCTION
void	fake_load_map_params(t_game *game)
{
	int		row;
	int		col;
	int		len;
	int		file;
	char	*line;

	file = open("./maps/invalid/fake.cub", O_RDONLY);
	if (file < 0)
		handle_error(game, "open");
	line = ft_get_next_line(file);
	len = ft_strlen(line);
	game->map.height = len - 1;
	game->map.width = len - 1;
	game->map.grid = ft_safalloc(sizeof(int *), len);
	row = 0;
	while (line)
	{
		game->map.grid[row] = ft_safalloc(sizeof(int), len);
		col = 0;
		while (col < len)
		{
			if (line[col] == 'N' || line[col] == 'S' || line[col] == 'W'
				|| line[col] == 'E')
			{
				game->player.pos[X] = col;
				game->player.pos[Y] = row;
				game->player.start_dir = line[col];
				line[col] = '0';
			}
			game->map.grid[row][col] = ft_atoi(&line[col]);
			col++;
		}
		row++;
		free(line);
		line = ft_get_next_line(file);
	}
	close(file);
}

/**
 * @brief sets the player's direction and plane vectors based on the starting
 * direction (start_dir).
 * 
 * @param game struct containing game data
 */
void	load_player_params(t_game *game)
{
	if (game->player.start_dir == 'W')
	{
		game->player.dir[X] = -1;
		game->player.plane[Y] = -0.66;
	}
	else if (game->player.start_dir == 'E')
	{
		game->player.dir[X] = 1;
		game->player.plane[Y] = 0.66;
	}
	else if (game->player.start_dir == 'S')
	{
		game->player.dir[Y] = 1;
		game->player.plane[X] = -0.66;
	}
	else if (game->player.start_dir == 'N')
	{
		game->player.dir[Y] = -1;
		game->player.plane[X] = 0.66;
	}
}
