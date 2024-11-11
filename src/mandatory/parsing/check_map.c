/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:29:21 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/11 15:40:09 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map_borders(t_game *game)
{
	int	i;

	while (i < game->map.width)
	{
		if (game->map.grid[0][i] != 1 || game->map.grid[game->map.height
			- 1][i] != 1)
		{
			handle_error(game, "Map is not closed (top or bottom row is open).");
			return (FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i][0] != 1 || game->map.grid[i][game->map.width
			- 1] != 1)
		{
			handle_error(game, "Map is not closed (left or right column is open).");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	validate_single_player(t_game *game)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 0 && (game->player.pos[X] == i
					&& game->player.pos[Y] == j))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		handle_error(game, "Map must have exactly one player.");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] != 1 && game->map.grid[i][j] != 0
				&& !(i == game->player.pos[X] && j == game->player.pos[Y]))
			{
				handle_error(game, "Invalid character in map.");
				return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	validate_map_neighbors(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < game->map.height - 1)
	{
		j = 1;
		while (j < game->map.width - 1)
		{
			if (game->map.grid[i][j] == 0)
			{
				if (game->map.grid[i - 1][j] == -1 || game->map.grid[i
					+ 1][j] == -1 || game->map.grid[i][j - 1] == -1
					|| game->map.grid[i][j + 1] == -1)
				{
					handle_error(game, "Map has open spaces around interior walls.");
					return (FAILURE);
				}
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	validate_all_map(t_game *game)
{
	if (validate_map_borders(game) == FAILURE)
		return (FAILURE);
	if (validate_single_player(game) == FAILURE)
		return (FAILURE);
	if (validate_map_characters(game) == FAILURE)
		return (FAILURE);
	if (validate_map_neighbors(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
