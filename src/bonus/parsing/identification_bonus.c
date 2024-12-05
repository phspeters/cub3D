/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:43 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/05 19:16:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_valid_line(char *line)
{
	while (*line && ft_strchr(" \t", *line))
		line++;
	return (is_texture_line(line)
		|| is_rgb_line(line)
		|| is_map_line(line)
		|| *line == '\n');
}

bool	is_texture_line(char *line)
{
	if (!line)
		return (0);
	while (*line && ft_strchr(" \t", *line))
		line++;
	return ((ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		&& ft_strchr(" \t", line[2]));
}

bool	is_rgb_line(char *line)
{
	if (!line)
		return (0);
	while (*line && ft_strchr(" \t", *line))
	{
		line++;
	}
	return ((ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
		&& ft_strchr(" \t", line[1]));
}

bool	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}
