/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:03:44 by roglopes          #+#    #+#             */
/*   Updated: 2024/10/19 17:55:07 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}

int	is_texture_exists(char *texture_path)
{
	if (access(texture_path, F_OK) != -1)
		return (1);
	else
		return (0);
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

int	validate_textures(t_game *game, char *line)
{
	char	*texture_path;
	int		valid;

	valid = 1;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		if (!is_xpm_file(texture_path))
			game->map.texture_path[NORTH] = ft_strdup(line + 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		if (!is_xpm_file(texture_path))
			game->map.texture_path[SOUTH] = ft_strdup(line + 3);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		if (!is_xpm_file(texture_path))
			game->map.texture_path[WEST] = ft_strdup(line + 3);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		if (!is_xpm_file(texture_path))
			game->map.texture_path[EAST] = ft_strdup(line + 3);
	}
	else
		return (0);
/* 	if (!is_texture_exists(texture_path))
		return (0); */
	free (texture_path);
	return (valid);
}

int	validate_all_textures(t_game *game)
{
	if (game->map.texture_path[NORTH] == NULL)
	{
		handle_error("Missing texture for SOUTH.\n");
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
