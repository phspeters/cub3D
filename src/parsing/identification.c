/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:43 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/23 20:43:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture_line(char *line)
{
	if (!line)
		return (0);
	while (*line && ft_strchr(" \t", *line))
		line++;
	return ((ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		&& ft_strchr(" \t", line[2]));
}

int	is_rgb_line(char *line)
{
	if (!line)
		return (0);
	while (*line && ft_strchr(" \t", *line))
		line++;
	return ((ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
		&& ft_strchr(" \t", line[1]));
}

int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}
