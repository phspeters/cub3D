/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:03:19 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/24 15:32:33 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_dimensions(t_game *game, char *file_path)
{
	int		fd;
	char	*line;
	int		width;
	int		height;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		handle_error(game, "Failed to open map file");
	width = 0;
	height = 0;
	line = get_first_map_line(game, fd);
	while (line != NULL && is_map_line(line))
	{
		width = get_line_width(line, width);
		height++;
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (line != NULL)
		handle_error(game, "Map must be the last information in the file");
	game->map.width = width;
	game->map.height = height;
}

char	*get_first_map_line(t_game *game, int fd)
{
	char	*line;

	line = ft_get_next_line(fd);
	while (line != NULL && !is_map_line(line))
	{
		line = ft_get_next_line(fd);
	}
	if (!line)
		handle_error(game, "Map information not found");
	return (line);
}

int	get_line_width(char *line, int current_width)
{
	int	width;

	width = 0;
	while (line[width] && line[width] != '\n')
		width++;
	if (width > current_width)
		return (width);
	return (current_width);
}

void	allocate_map_grid(t_game *game)
{
	int	i;

	game->map.grid = ft_safalloc(sizeof(int *), game->map.height);
	if (!game->map.grid)
		handle_error(game, "Memory allocation failed for map grid");
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_safalloc(sizeof(int), game->map.width);
		if (!game->map.grid[i])
			handle_error(game, "Memory allocation failed for map row");
		i++;
	}
}
