/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:29:21 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/22 17:00:28 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_horizontal_borders(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.width)
	{
		if ((game->map.grid[0][i] != 1 && game->map.grid[0][i] != 8) || \
			(game->map.grid[game->map.height - 1][i] != 1 && \
			game->map.grid[game->map.height - 1][i] != 8))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	validate_vertical_borders(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		if ((game->map.grid[i][0] != 1 && game->map.grid[i][0] != 8) || \
			(game->map.grid[i][game->map.width - 1] != 1 && \
			game->map.grid[i][game->map.width - 1] != 8))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	validate_map_borders(t_game *game)
{
	if (validate_horizontal_borders(game) == FAILURE)
		handle_error(game, "Map is not closed at the top or bottom.");
	if (validate_vertical_borders(game) == FAILURE)
		handle_error(game, "Map is not closed on the left or right.");
	return (SUCCESS);
}

int	validate_single_player(t_game *game)
{
	if (game->player.player_count != 1)
	{
		if (game->player.player_count == 0)
			handle_error(game, "No player detected in the map.");
		else
			handle_error(game, "Multiple players detected in the map.");
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
			if (game->map.grid[i][j] != 1 && game->map.grid[i][j] != 0 && \
				game->map.grid[i][j] != 8)
				handle_error(game, "Invalid character in map.");
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

// funcao
static int	validate_open_neighbors(t_game *game, int i, int j)
{
	if (game->map.grid[i - 1][j] == -1 || game->map.grid[i + 1][j] == -1 || \
		game->map.grid[i][j - 1] == -1 || game->map.grid[i][j + 1] == -1)
		return (FAILURE);
	return (SUCCESS);
}

static int	validate_neighbor_values(t_game *game, int i, int j)
{
	if (game->map.grid[i - 1][j] != 1 && game->map.grid[i - 1][j] != 0 && \
		game->map.grid[i - 1][j] != 8)
		return (FAILURE);
	if (game->map.grid[i + 1][j] != 1 && game->map.grid[i + 1][j] != 0 && \
		game->map.grid[i + 1][j] != 8)
		return (FAILURE);
	if (game->map.grid[i][j - 1] != 1 && game->map.grid[i][j - 1] != 0 && \
		game->map.grid[i][j - 1] != 8)
		return (FAILURE);
	if (game->map.grid[i][j + 1] != 1 && game->map.grid[i][j + 1] != 0 && \
		game->map.grid[i][j + 1] != 8)
		return (FAILURE);
	return (SUCCESS);
}

static int	validate_cell_neighbors(t_game *game, int i, int j)
{
	if (validate_open_neighbors(game, i, j) == FAILURE)
		handle_error(game, "Map has open spaces near playable cells.");
	if (validate_neighbor_values(game, i, j) == FAILURE)
		handle_error(game, "Invalid neighbors around playable cell.");
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
				validate_cell_neighbors(game, i, j);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	validate_all_map(t_game *game)
{
	validate_map_borders(game);
	validate_single_player(game);
	validate_map_characters(game);
	validate_map_neighbors(game);
	return (SUCCESS);
}
