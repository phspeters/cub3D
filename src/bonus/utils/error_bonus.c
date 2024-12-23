/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:05 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/05 19:16:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief prints the appropriate error message and exits the program without
 * memory leaks when an error occurs in the mlx library.
 *
 * @param game struct with game info
 */
void	handle_mlx_error(t_game *game, char *message)
{
	end_game(game);
	ft_fprintf(STDERR_FILENO, "%s: %s.\n", message, mlx_strerror(mlx_errno));
	exit(mlx_errno);
}

/**
 * @brief prints the appropriate error message and exits the program without
 * memory leaks.
 *
 * @param game struct with game info
 * @param message error message
 */
void	handle_error(t_game *game, char *message)
{
	if (errno)
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		perror(message);
		end_game(game);
		exit(errno);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		ft_fprintf(STDERR_FILENO, "%s.\n", message);
		end_game(game);
		exit(EXIT_FAILURE);
	}
}
