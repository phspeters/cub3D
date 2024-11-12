/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/11/12 17:00:46 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_line(char *line)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r' \
			|| line[i] == '\v' || line[i] == '\f')
			i++;
	trimmed = ft_strdup(line + i);
	return (trimmed);
}

void	parse_map(t_game *game, char *argv[])
{
	int		fd;
	char	*line;

	if (calculate_map_dimensions(game, argv[1]) == FAILURE)
		handle_error(game, "Error getting map dimensions");
	allocate_map_grid(game);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_error(game, "Error opening map file");
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		line = trim_line(line);
		if (is_texture_line(line))
		{
			if (!validate_textures(game, line))
				handle_error(game, "Invalid texture path or type");
		}
		else if (is_rgb_line(line))
		{
			if (!validate_rgb(game, line))
				handle_error(game, "Invalid RGB values");
		}
		else if (is_map_line(line))
		{
			process_map_line(game, line);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (!validate_all_textures(game))
		handle_error(game, "Missing mandatory texture");
	if (!validate_all_floor_ceiling(game))
		handle_error(game, "Missing floor or ceiling color");
	if (validate_all_map(game) == FAILURE)
		handle_error(game, "Map validation failed");
}
