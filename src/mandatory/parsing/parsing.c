/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/11/20 22:00:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	handle_error(char *message)
{
	if (errno)
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		perror(message);
		exit(errno);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		ft_fprintf(STDERR_FILENO, "%s.\n", message);
		exit(EXIT_FAILURE);
	}
}

char	*trim_line(char *line)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || \
	line[i] == '\r' || line[i] == '\v' || line[i] == '\f')
		i++;
	trimmed = ft_strdup(line + i);
	return (trimmed);
}

void	parse_map(t_game *game, char *argv[])
{
	int		fd;
	char	*line;

	if (calculate_map_dimensions(game, argv[1]) == FAILURE)
	{
		printf("Erro ao calcular as dimensões do mapa.\n");
		return ;
	}
	allocate_map_grid(game);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		handle_error("Error opening map file.");
		return ;
	}
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		line = trim_line(line);
		if (is_texture_line(line))
		{
			if (!validate_textures(game, line))
				handle_error ("Invalid texture path or type.");
		}
		else if (is_rgb_line(line))
		{
			if (!validate_rgb(game, line))
				handle_error("Invalid RGB values.");
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
		handle_error("Missing mandatory texture.");
	if (!validate_all_floor_ceiling(game))
		handle_error("Missing floor or ceiling color.");
	if (validate_all_map(game) == FAILURE)
	{
		handle_error("Map validation failed.");
		return ;
	}
}
