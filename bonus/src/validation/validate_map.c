/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:29:21 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/28 18:20:40 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Responsible for validating the map, checking if it is surrounded by
 * walls, if there are no spaces inside and if there is only one player.
 * 
 * @param game struct with game information
 */
void	validate_map(t_game *game)
{
	validate_map_borders(game);
	validate_map_content(game);
	validate_player(game);
}

/**
 * @brief Check if the map borders are walls or voids.
 * 
 * @param game struct with game information
 */
void	validate_map_borders(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.width)
	{
		if (!is_wall_or_void(game->map.grid[0][i])
			|| !is_wall_or_void(game->map.grid[game->map.height - 1][i]))
		{
			handle_error(game,
				"Invalid map horizontal borders: must be walls or spaces");
		}
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		if (!is_wall_or_void(game->map.grid[i][0])
			|| !is_wall_or_void(game->map.grid[i][game->map.width - 1]))
		{
			handle_error(game,
				"Invalid map vertical borders: must be walls or spaces");
		}
		i++;
	}
}

/**
 * @brief Iterates through the map checking if the tiles next to each other are
 * valid.
 * 
 * @param game struct with game information
 */
void	validate_map_content(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height - 1)
	{
		j = 0;
		while (j < game->map.width - 1)
		{
			validate_cell_neighbours(game, i, j);
			j++;
		}
		i++;
	}
}

/**
 * @brief Checks if the cell right and below neighbors are valid. That is, void
 * cells must not have empty or closed door cells as neighbors and vice versa. 
 * 
 * @param game struct with game information
 * @param i cell row
 * @param j cell column
 */
void	validate_cell_neighbours(t_game *game, int i, int j)
{
	if (game->map.grid[i][j] == EMPTY || game->map.grid[i][j] == CLOSED_DOOR)
	{
		if (game->map.grid[i + 1][j] == VOID
		|| game->map.grid[i][j + 1] == VOID)
		{
			handle_error(game, "Invalid map content:\
 map must be surrounded by walls with no spaces inside");
		}
	}
	else if (game->map.grid[i][j] == VOID)
	{
		if (game->map.grid[i + 1][j] == EMPTY
			|| game->map.grid[i][j + 1] == EMPTY
			|| game->map.grid[i + 1][j] == CLOSED_DOOR
			|| game->map.grid[i][j + 1] == CLOSED_DOOR)
		{
			handle_error(game, "Invalid map content:\
 map must be surrounded by walls with no spaces inside");
		}
	}
}

void	validate_player(t_game *game)
{
	if (game->player.player_count == 0)
		handle_error(game, "No player detected: must have at least one player");
	if (game->player.player_count > 1)
		handle_error(game,
			"Multiple players detected: must have only one player");
}
