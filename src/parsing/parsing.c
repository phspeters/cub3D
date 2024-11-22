/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/11/22 17:03:53 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_line(char *line)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
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
	validate_all_textures(game);
	validate_all_floor_ceiling(game);
	validate_all_map(game);
}
