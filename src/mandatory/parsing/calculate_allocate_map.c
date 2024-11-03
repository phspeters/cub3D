/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_allocate_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:03:19 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/03 13:15:14 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	calculate_map_dimensions(t_game *game, char *file_path)
{
	int		fd;
	char	*line;
	int		width;
	int		height;
	int		current_width;

	fd = open(file_path, O_RDONLY);
	width = 0;
	height = 0;
	if (fd < 0)
	{
		handle_error("Failed to open map file.");
		return (FAILURE);
	}
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		if (is_map_line(line))
		{
			current_width = 0;
			while (line[current_width] && line[current_width] != '\n')
				current_width++;
			if (current_width > width)
				width = current_width;
			height++;
		}
		free(line);
	}
	close(fd);
	game->map.width = width;
	game->map.height = height;
	return (SUCCESS);
}

void	allocate_map_grid(t_game *game)
{
	int	i;

	game->map.grid = malloc(sizeof(int *) * game->map.height);
	if (!game->map.grid)
	{
		handle_error("Memory allocation failed for map grid.");
		return ;
	}
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = malloc(sizeof(int) * game->map.width);
		if (!game->map.grid[i])
		{
			handle_error("Memory allocation failed for map row.");
			return ;
		}
		i++;
	}
}
