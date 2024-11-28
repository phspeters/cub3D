/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:22:00 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/28 18:24:43 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_arguments(t_game *game, int argc, char **argv)
{
	if (argc != 2)
	{
		handle_error(game,
			"Invalid number of arguments: Usage: ./cub3D <path to map>");
	}
	validate_file(game, argv[1]);
}

void	validate_file(t_game *game, char *argv_file)
{
	int	fd;

	if (is_directory(argv_file))
		handle_error(game, "Invalid file argument: path is a directory");
	fd = open(argv_file, O_RDONLY);
	if (fd == -1)
		handle_error(game, "Invalid file argument");
	close(fd);
	if (!has_cub_extension(argv_file))
		handle_error(game,
			"Invalid file argument: file must have a .cub extension");
}

bool	is_directory(char *argv_file)
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

bool	has_cub_extension(char *argv_file)
{
	size_t	len;

	len = ft_strlen(argv_file);
	if ((argv_file[len - 4] != '.')
		|| argv_file[len - 3] != 'c'
		|| argv_file[len - 2] != 'u'
		|| argv_file[len - 1] != 'b'
		|| argv_file[len] != '\0')
	{
		return (false);
	}
	return (true);
}
