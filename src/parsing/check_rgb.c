/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:26:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/12 16:59:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_all_floor_ceiling(t_game *game)
{
	if (game->map.ceiling == 0)
		handle_error(game, "Ceiling color not set");
	if (game->map.floor == 0)
		handle_error(game, "Floor color not set");
	return (1);
}

int	is_rgb_line(char *line)
{
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
	char		c_or_f;

	if (line[0] == 'C' || line[0] == 'F')
	{
		c_or_f = line[0];
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
		handle_error(game, "Invalid RGB values");
	return (1);
}
