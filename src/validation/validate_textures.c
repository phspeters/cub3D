/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:03:44 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/22 17:09:53 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture_line(char *line)
{
	line = trim_line(line);
	return (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0);
}

static bool	is_png_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 4] != '.')
		|| arg[len - 3] != 'p'
		|| arg[len - 2] != 'n'
		|| arg[len - 1] != 'g')
		return (false);
	return (true);
}

int	set_texture_path(char **texture_dest, char *line)
{
	char	*texture_path;

	texture_path = trim_line(line + 2);
	if (!is_png_file(texture_path))
		*texture_dest = texture_path;
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
		handle_error(game, "Missing texture for NORTH wall");
	if (game->map.texture_path[SOUTH] == NULL)
		handle_error(game, "Missing texture for SOUTH wall");
	if (game->map.texture_path[WEST] == NULL)
		handle_error(game, "Missing texture for WEST wall");
	if (game->map.texture_path[EAST] == NULL)
		handle_error(game, "Missing texture for EAST wall");
	return (1);
}
