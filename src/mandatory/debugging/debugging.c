/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:31:48 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/03 14:42:07 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_texture_paths(t_game *game)
{
	const char	*texture_name[5] = {"NORTH", "SOUTH", "WEST", "EAST", "DOOR"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (game->map.texture_path[i] != NULL)
		{
			ft_printf("Texture for %s:  %s", texture_name[i], \
			game->map.texture_path[i]);
		}
		else
			ft_printf("Texture for %s not set. ", texture_name[i]);
		i++;
	}
}

void	print_rgb_values(t_game *game)
{
	if (game->map.ceiling == 0)
		ft_printf("Ceiling color not set. \n");
	else
		printf("Ceiling color: %#010x\n", game->map.ceiling);
	if (game->map.floor == 0)
		ft_printf("Floor color not set. \n");
	else
		printf("Floor color: %#010x\n", game->map.floor);
}

void	print_map_grid(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	printf("Player detect: %c in position (X: %d, Y: %d)\n", \
		game->player.player_start_char, \
		(int)game->player.pos[X], (int)game->player.pos[Y]);
	printf("Player direction: (dir[X]: %f, dir[Y]: %f)\n", game->player.dir[X],
		game->player.dir[Y]);
	printf("Map height: %d, Map width: %d\n", game->map.height,
		game->map.width);
	printf("Map grid:\n");
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			printf("%d ", game->map.grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_validate_map_borders(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.width)
	{
		printf("Top border - grid[0][%d]: %d\n", i, game->map.grid[0][i]);
		printf("Bottom border - grid[%d][%d]: %d\n", game->map.height - 1, i,
			game->map.grid[game->map.height - 1][i]);
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		printf("Left border - grid[%d][0]: %d\n", i, game->map.grid[i][0]);
		printf("Right border - grid[%d][%d]: %d\n", i, game->map.width - 1,
			game->map.grid[i][game->map.width - 1]);
		i++;
	}
}
