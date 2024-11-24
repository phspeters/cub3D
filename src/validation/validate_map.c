/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:29:21 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/23 20:56:38 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map_borders(t_game *game)
{
	validate_top_border(game);
	validate_bottom_border(game);
	validate_left_border(game);
	validate_right_border(game);
}

void	validate_top_border(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.width)
	{
		if (game->map.grid[0][i] != 1 && game->map.grid[0][i] != 8)
		{
			handle_error(game, "Map top border is not surrounded by walls");
		}
		i++;
	}
}

void	validate_bottom_border(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.width)
	{
		if (game->map.grid[game->map.height - 1][i] != 1
			&& game->map.grid[game->map.height - 1][i] != 8)
		{
			handle_error(game, "Map bottom is not surrounded by walls");
		}
		i++;
	}
}

void	validate_left_border(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < game->map.height - 1)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 1)
				return ;
			if (game->map.grid[i][j] == 8)
			{
				if (game->map.grid[i - 1][j] != 1 && game->map.grid[i
					- 1][j] != 8)
					handle_error(game,
						"Map left border is not surrounded by walls");
				if (game->map.grid[i + 1][j] != 1 && game->map.grid[i
					+ 1][j] != 8)
					handle_error(game,
						"Map left border is not surrounded by walls");
			}
			j++;
		}
		i++;
	}
}

void	validate_right_border(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < game->map.height - 1)
	{
		j = game->map.width - 1;
		while (j >= 0)
		{
			if (game->map.grid[i][j] == 1)
				return ;
			if (game->map.grid[i][j] == 8)
			{
				if (game->map.grid[i - 1][j] != 1 && game->map.grid[i
					- 1][j] != 8)
					handle_error(game,
						"Map right border is not surrounded by walls");
				if (game->map.grid[i + 1][j] != 1 && game->map.grid[i
					+ 1][j] != 8)
					handle_error(game,
						"Map right border is not surrounded by walls");
			}
			j--;
		}
		i++;
	}
}
