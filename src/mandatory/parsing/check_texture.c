/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:03:44 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/20 17:10:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_texture_line(char *line)
{
	line = trim_line(line);
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0);
}

static bool	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	set_texture_path(char **texture_dest, char *line)
{
	char	*texture_path;

	texture_path = trim_line(line + 2);
	if (!is_xpm_file(texture_path))
		*texture_dest = trim_line(line + 2);
	free(texture_path);
	return (FAILURE);
}

int	validate_textures(t_game *game, char *line)
{
	line = trim_line(line);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (set_texture_path(&game->map.texture_path[NORTH], line));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (set_texture_path(&game->map.texture_path[SOUTH], line));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (set_texture_path(&game->map.texture_path[WEST], line));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (set_texture_path(&game->map.texture_path[EAST], line));
	return (FAILURE);
}

int	validate_all_textures(t_game *game)
{
	if (game->map.texture_path[NORTH] == NULL)
	{
		handle_error("Missing texture for NORTH.\n");
		return (0);
	}
	if (game->map.texture_path[SOUTH] == NULL)
	{
		handle_error("Missing texture for SOUTH.\n");
		return (0);
	}
	if (game->map.texture_path[WEST] == NULL)
	{
		handle_error("Missing texture for WEST.\n");
		return (0);
	}
	if (game->map.texture_path[EAST] == NULL)
	{
		handle_error("Missing texture for EAST.\n");
		return (0);
	}
	return (1);
}
