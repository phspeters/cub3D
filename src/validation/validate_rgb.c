/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:26:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/24 15:44:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_rgb(t_game *game)
{
	if (game->map.ceiling == 0)
		handle_error(game, "Missing color: ceiling color not set");
	if (game->map.floor == 0)
		handle_error(game, "Missing color: floor color not set");
}

void	validate_rgb_line(t_game *game, char *line)
{
	line = ft_strtrim(line, " \t\n\f\r\v");
	while (line && ft_isdigit(*line))
		line++;
	line = ft_strtrim(line, " \t\n\f\r\v");
	if (*line != ',')
		handle_error(game,
			"Invalid RGB line: must provide 3 integers separated by commas");
	line++;
	line = ft_strtrim(line, " \t\n\f\r\v");
	while (line && ft_isdigit(*line))
		line++;
	line = ft_strtrim(line, " \t\n\f\r\v");
	if (*line != ',')
		handle_error(game,
			"Invalid RGB line: must provide 3 integers separated by commas");
	line++;
	line = ft_strtrim(line, " \t\n\f\r\v");
	while (line && ft_isdigit(*line))
		line++;
	line = ft_strtrim(line, " \t\n\f\r\v");
	if (*line != '\0' && *line != '\n')
		handle_error(game,
			"Invalid RGB line: must provide 3 integers separated by commas");
}

int	validate_rgb_value(t_game *game, char *rgb_string)
{
	int	rgb;

	rgb = ft_atoi(rgb_string);
	if (rgb < 0 || rgb > 255)
		handle_error(game, "Invalid RGB value: must be between 0 and 255");
	return (rgb);
}
