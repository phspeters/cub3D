/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:53:07 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/25 19:35:29 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_valid_pixel(t_game *game, int x, int y, uint32_t color)
{
	mlx_image_t	*image;

	image = game->image;
	if (color == 0xFF00FFFF)
		return ;
	if ((x > 0 && x < game->screen_size[X]) && (y > 0
			&& y < game->screen_size[Y]))
		mlx_put_pixel(image, x, y, color);
}

void	handle_mlx_error(t_game *game)
{
	(void)game;
	ft_fprintf(STDERR_FILENO, "%s.\n", mlx_strerror(mlx_errno));
	exit(mlx_errno);
}

void	handle_error(char *message)
{
	if (errno)
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		perror(message);
		exit(errno);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		ft_fprintf(STDERR_FILENO, "%s.\n", message);
		exit(EXIT_FAILURE);
	}
}
