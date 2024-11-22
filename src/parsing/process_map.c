/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:20:37 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/22 15:41:07 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map_line(t_game *game, char *line)
{
	static int	i;
	int			j;

	j = 0;
	if (i > game->map.height)
		handle_error(game, "Map exceeds allocated height");
	while (line[j] && line[j] != '\n' && j < game->map.width)
	{
		if (line[j] == '1')
			game->map.grid[i][j] = 1;
		else if (line[j] == '0')
			game->map.grid[i][j] = 0;
		else if (line[j] == ' ')
			game->map.grid[i][j] = 8;
		else if (ft_strchr("NSEW", line[j]))
		{
			game->player.pos[Y] = i + 0.5;
			game->player.pos[X] = j + 0.5;
			game->player.start_dir = line[j];
			game->map.grid[i][j] = 0;
			game->player.player_count++;
		}
		else
			handle_error(game, "Invalid character in map");
		j++;
	}
	while (j < game->map.width)
	{
		game->map.grid[i][j] = 8;
		j++;
	}
	i++;
}
