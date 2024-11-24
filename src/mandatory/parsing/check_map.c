/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:29:21 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/23 14:51:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	{
		handle_error("Map is not closed at the top or bottom.");
		return (FAILURE);
	}
	if (validate_vertical_borders(game) == FAILURE)
	{
		handle_error("Map is not closed on the left or right.");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	validate_single_player(t_game *game)
{
	if (game->player_count != 1)
	{
		if (game->player_count == 0)
			handle_error("No player detected in the map.");
		else
			handle_error("Multiple players detected in the map.");
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
			if (game->map.grid[i][j] != 1 && game->map.grid[i][j] != 0 && \
				game->map.grid[i][j] != 8)
			{
				handle_error("Invalid character in map.");
				return (FAILURE);
			}
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
	{
		handle_error("Map has open spaces near playable cells.");
		return (FAILURE);
	}
	if (validate_neighbor_values(game, i, j) == FAILURE)
	{
		handle_error("Invalid neighbors around playable cell.");
		return (FAILURE);
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
				if (validate_cell_neighbors(game, i, j) == FAILURE)
					return (FAILURE);
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
