/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:22:00 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/22 18:29:30 by pehenri2         ###   ########.fr       */
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
