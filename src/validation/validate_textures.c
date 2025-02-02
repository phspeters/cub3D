/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:03:44 by roglopes          #+#    #+#             */
/*   Updated: 2024/11/25 19:35:17 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_textures(t_game *game)
{
	if (game->map.texture_path[NORTH] == NULL)
		handle_error(game, "Missing texture for north (NO) wall");
	if (game->map.texture_path[SOUTH] == NULL)
		handle_error(game, "Missing texture for south (SO) wall");
	if (game->map.texture_path[WEST] == NULL)
		handle_error(game, "Missing texture for west (WE) wall");
	if (game->map.texture_path[EAST] == NULL)
		handle_error(game, "Missing texture for east (EA) wall");
}

void	set_texture_path(t_game *game, char **texture_dest, char *line)
{
	char	*texture_path;
	int		fd;

	if (*texture_dest != NULL)
	{
		handle_error(game, "Duplicated texture info: texture already set");
	}
	texture_path = ft_strtrim(line + 2, " \t\n\f\r\v");
	if (!is_png_file(texture_path))
	{
		handle_error(game, "Invalid texture file extension: file must be .png");
	}
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
	{
		handle_error(game, "Invalid texture file path");
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
