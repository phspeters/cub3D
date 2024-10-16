/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:53:07 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/16 16:22:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief draws a pixel on the screen at the specified coordinates and color,
 * but only if the coordinates are within the screen boundaries and the color
 * is not 0xFF00FFFF. It uses the mlx_put_pixel function to actually draw the
 * pixel on the image.
 * 
 * @param game struct with game info
 * @param x coordinate
 * @param y coordinate
 * @param color RGBA color
 */
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

/**
 * @brief prints the appropriate error message and exits the program without
 * memory leaks when an error occurs in the mlx library.
 * 
 * @param game struct with game info
 */
void	handle_mlx_error(t_game *game)
{
	(void)game; //TODO: free stuff
	ft_fprintf(STDERR_FILENO, "%s.\n", mlx_strerror(mlx_errno));
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
	(void)game; //TODO: free stuff
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
