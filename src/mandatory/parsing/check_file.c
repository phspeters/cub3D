/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:20:09 by codespace         #+#    #+#             */
/*   Updated: 2024/11/11 20:45:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_dir(char *argv_file)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(argv_file, __O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

static bool	is_cub_file(char *argv_file)
{
	size_t	len;

	len = ft_strlen(argv_file);
	if ((argv_file[len - 3] != 'c' || argv_file[len - 2] != 'u'
			|| argv_file[len - 1] != 'b'
			|| argv_file[len - 4] != '.'))
		return (false);
	return (true);
}

int	check_file(char *argv_file, bool cub)
{
	int	fd;

	if (is_dir(argv_file))
		return (FAILURE);
	fd = open(argv_file, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	close(fd);
	if (cub && !is_cub_file(argv_file))
		return (FAILURE);
	return (SUCCESS);
}
