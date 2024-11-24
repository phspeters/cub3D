/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:03:44 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/23 20:52:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_textures(t_game *game)
{
	if (game->map.texture_path[NORTH] == NULL)
		handle_error(game, "Missing texture for NORTH wall");
	if (game->map.texture_path[SOUTH] == NULL)
		handle_error(game, "Missing texture for SOUTH wall");
	if (game->map.texture_path[WEST] == NULL)
		handle_error(game, "Missing texture for WEST wall");
	if (game->map.texture_path[EAST] == NULL)
		handle_error(game, "Missing texture for EAST wall");
}

void	set_texture_path(t_game *game, char **texture_dest, char *line)
{
	char	*texture_path;
	int		len;

	if (*texture_dest != NULL)
	{
		handle_error(game, "Duplicated texture info: texture already set");
	}
	texture_path = trim_line(line + 2);
	len = ft_strlen(texture_path);
	if (texture_path[len - 1] == '\n')
		texture_path[len - 1] = '\0';
	if (!is_png_file(texture_path))
	{
		handle_error(game, "Invalid texture file extension: file must be .png");
	}
	*texture_dest = texture_path;
}

int	is_png_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (file[len - 4] != '.'
		|| file[len - 3] != 'p'
		|| file[len - 2] != 'n'
		|| file[len - 1] != 'g'
		|| file[len] != '\0')
		return (0);
	return (1);
}
