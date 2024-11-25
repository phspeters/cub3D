/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:53:07 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/24 15:34:50 by pehenri2         ###   ########.fr       */
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
 * @brief attempts to load a PNG texture from a given file path and handles
 * any errors that occur during the loading process. If successful, it returns
 * the loaded texture.
 * 
 * @param game struct with game info
 * @param path texture file path
 * @return mlx_texture_t* 
 */
mlx_texture_t	*ft_load_png(t_game *game, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		handle_mlx_error(game, "mlx_load_png");
	return (texture);
}

/**
 * @brief iterates over an array of texture pointers and deletes each texture
 * that is not NULL using the mlx_delete_texture function from the MiniLibX
 * library.
 * 
 * @param textures array of texture pointers
 * @param count number of textures in the array
 */
void	delete_textures(mlx_texture_t **textures, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (textures[i])
			mlx_delete_texture(textures[i]);
		i++;
	}
}

int	is_wall_or_void(int map_cell)
{
	return (map_cell == WALL || map_cell == VOID);
}
