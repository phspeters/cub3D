/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:20:09 by codespace         #+#    #+#             */
/*   Updated: 2024/11/22 18:37:22 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_dir(char *argv_file)
{
	int	fd;

	fd = open(argv_file, __O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (true);
	}
	errno = 0;
	return (false);
}

static bool	is_cub_file(char *argv_file)
{
	size_t	len;

	len = ft_strlen(argv_file);
	if ((argv_file[len - 4] != '.')
		|| argv_file[len - 3] != 'c'
		|| argv_file[len - 2] != 'u'
		|| argv_file[len - 1] != 'b')
	{
		return (false);
	}
	return (true);
}

void	validate_file(t_game *game, char *argv_file)
{
	int	fd;

	if (is_dir(argv_file))
	{
		handle_error(game, "Invalid file argument: path is a directory");
	}
	fd = open(argv_file, O_RDONLY);
	if (fd == -1)
	{
		handle_error(game, "Invalid file argument");
	}
	close(fd);
	if (!is_cub_file(argv_file))
	{
		handle_error(game,
			"Invalid file argument: file must have a .cub extension");
	}
}
