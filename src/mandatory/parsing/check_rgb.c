/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:26:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/20 19:55:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_all_floor_ceiling(t_game *game)
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
	line = trim_line(line);
	return (ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0);
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

	if (line[0] == 'C' || line[0] == 'F')
	{
		game->map.c_or_f = line[0];
		line++;
		if (!parse_rgb_value(&line, &r) || *line != ',')
			return (0);
		line++;
		if (!parse_rgb_value(&line, &g) || *line != ',')
			return (0);
		line++;
		if (!parse_rgb_value(&line, &b))
			return (0);
		color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
		if (game->map.c_or_f == 'C')
			game->map.ceiling = color;
		else
			game->map.floor = color;
		return (1);
	}
	return (0);
}

int	validate_rgb(t_game *game, char *line)
{
	line = trim_line(line);
	if (!parse_rgb(game, line))
	{
		handle_error("Invalid RGB values.");
		return (0);
	}
	return (1);
}
