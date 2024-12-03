/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:17:01 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/03 19:29:44 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief handles the rendering of the game scene by deleting the old image,
 * creating a new image, attaching it to the window, and then drawing the 3D
 * scene, minimap, player on the minimap, and sprites. All in a loop.
 *
 * @param param pointer to the game struct holding all game information
 */
void	draw_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_3d_scene(game);
}

/**
 * @brief iterates through each horizontal pixel column of the screen,
 * casting a ray for each column to determine what is visible from the
 * player's perspective and rendering the 3D view accordingly. Then draws
 * the correspondingvertical line of the screen.
 *
 * @param game struct with game information
 */
void	draw_3d_scene(t_game *game)
{
	int		x_coordinate;
	t_ray	ray;

	x_coordinate = 0;
	while (x_coordinate <= game->screen_size[X])
	{
		ray = cast_ray(game, x_coordinate);
		draw_vertical_screen_line(game, x_coordinate, ray);
		x_coordinate++;
	}
}
