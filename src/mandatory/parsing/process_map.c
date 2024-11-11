/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:20:37 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/03 14:19:49 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_player_start_dir(t_game *game, char start_dir)
{
	if (start_dir == 'N')
	{
		game->player.dir[X] = -1;
		game->player.dir[Y] = 0;
		game->player.plane[X] = 0;
		game->player.plane[Y] = 0.66;
	}
	else if (start_dir == 'S')
	{
		game->player.dir[X] = 1;
		game->player.dir[Y] = 0;
		game->player.plane[X] = 0;
		game->player.plane[Y] = -0.66;
	}
	else if (start_dir == 'E')
	{
		game->player.dir[X] = 0;
		game->player.dir[Y] = 1;
		game->player.plane[X] = 0.66;
		game->player.plane[Y] = 0;
	}
	else if (start_dir == 'W')
	{
		game->player.dir[X] = 0;
		game->player.dir[Y] = -1;
		game->player.plane[X] = -0.66;
		game->player.plane[Y] = 0;
	}
}

void	process_map_line(t_game *game, char *line)
{
	int	j;

	j = 0;
	if (game->map.current[0] >= game->map.height)
	{
		handle_error("Map exceeds allocated height.");
		return ;
	}
	while (line[j] && j < game->map.width)
	{
		if (line[j] == '1')
			game->map.grid[game->map.current[0]][j] = 1;
		else if (line[j] == '0')
			game->map.grid[game->map.current[0]][j] = 0;
		else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E'
			|| line[j] == 'W')
		{
			game->player.pos[X] = game->map.current[0];
			game->player.pos[Y] = j;
			game->player.player_start_char = line[j];
			game->map.grid[game->map.current[0]][j] = 0;
			set_player_start_dir(game, line[j]);
		}
		else
		{
			handle_error("Invalid character in map.");
			return ;
		}
		j++;
	}
	game->map.current[0]++;
}