/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/20 15:45:30 by roglopes         ###   ########.fr       */
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

int	validate_floor_ceiling(t_game *game)
{
	if (game->map.ceiling == 0)
	{
		handle_error("Ceiling color not set.\n");
		return (0);
	}
	if (game->map.floor == 0)
	{
		handle_error("Floor color not set.\n");
		return (0);
	}
	return (1);
}

int	is_rgb_line(char *line)
{
	return (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0);
}

int	parse_rgb_value(char **line_ptr, int *value)
{
	while (**line_ptr == ' ' || **line_ptr == '\t')
		(*line_ptr)++;
	*value = ft_atoi(*line_ptr);
	if (*value < 0 || *value > 255)
		return (0);
	while (**line_ptr >= '0' && **line_ptr <= '9')
		(*line_ptr)++;
	while (**line_ptr == ' ' || **line_ptr == '\t')
		(*line_ptr)++;
	return (1);
}

int	parse_rgb(t_game *game, char *line)
{
	int			r;
	int			g;
	int			b;
	uint32_t	color;
	char		c_or_f;

	if (line[0] == 'C' || line[0] == 'F')
	{
		c_or_f = line[0];
		printf("Linha lida: %s", line);
		line++;
		if (!parse_rgb_value(&line, &r) || *line != ',')
			return (0);
		line++;
		if (!parse_rgb_value(&line, &g) || *line != ',')
			return (0);
		line++;
		if (!parse_rgb_value(&line, &b))
			return (0);
		color = (r << 16) | (g << 8) | b;
		printf("Linha lida: %c", c_or_f);
		if (c_or_f == 'C')
			game->map.ceiling = color;
		else
			game->map.floor = color;
		return (1);
	}
	return (0);
}

int	validate_rgb(t_game *game, char *line)
{
	if (!parse_rgb(game, line))
	{
		handle_error("Invalid RGB values.");
		return (0);
	}
	return (1);
}

void	parse_map(t_game *game, int argc, char *argv[])
{
	char	*line;
	char	*trimmed_line;
	int		fd;
	int		i;

	(void)argc;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		handle_error("Error opening map file.");
		return ;
	}
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		//printf("Linha lida: %s", line); // Imprime a linha lida
		if (ft_strlen(line) > 0)
		{
			if (is_texture_line(line))
			{
				if (!validate_textures(game, line))
					handle_error("Invalid texture path or type.");
			}
			else if (is_rgb_line(line))
			{
				if (!validate_rgb(game, line))
					handle_error("Invalid RGB values.");
			}
		}
		free(line);
	}
	close(fd);
	if (!validate_all_textures(game))
		handle_error("Missing mandatory texture.");
/* 	if (!validate_floor_ceiling(game))
		handle_error("Missing floor or ceiling color."); */
}
