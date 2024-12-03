/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:26:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/28 18:23:37 by pehenri2         ###   ########.fr       */
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

/**
 * @brief Validates the RGB line, checking if it has 3 integers separated by
 * commas.
 * 
 * @param game struct with game information
 * @param line line to be validated
 */
void	validate_rgb_line(t_game *game, char *line)
{
	int	color_count;

	line = ft_strtrim(line, " \t\n\f\r\v");
	color_count = count_rgb_values(game, line);
	if (color_count != 3)
		handle_error(game,
			"Invalid RGB: must provide 3 integers separated by commas");
}

/**
 * @brief Iterates through the RGB line counting the number of integers
 * and commas.
 * 
 * @param game struct with game information
 * @param line rgb line to be counted
 * @return int number of integers
 */
int	count_rgb_values(t_game *game, char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (ft_isdigit(*line))
		{
			count++;
			while (ft_isdigit(*line))
				line++;
		}
		while (ft_isspace(*line))
			line++;
		if (*line == ',')
			line++;
		else if (*line != '\0')
			handle_error(game,
				"Invalid RGB: must provide 3 integers separated by commas");
	}
	return (count);
}

int	validate_rgb_value(t_game *game, char *rgb_string)
{
	int	rgb;

	rgb = ft_atoi(rgb_string);
	if (rgb < 0 || rgb > 255)
		handle_error(game, "Invalid RGB value: must be between 0 and 255");
	return (rgb);
}
