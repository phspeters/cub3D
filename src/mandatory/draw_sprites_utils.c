/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:19:30 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/17 19:56:20 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief animates the death of a sprite by cycling through a series of
 * textures. It initializes and calculates the sprite's dimensions, draws the
 * sprite, and updates the frame counter. Once the animation sequence is
 * complete, it resets the sprite's state and respawns it.
 * 
 * @param game struct containing all the game information
 * @param sprite information about the sprite to be drawn
 */
void	draw_death_animation_and_respawn(t_game *game, t_sprite sprite)
{
	mlx_texture_t	*texture;
	static int		tex_index = 0;
	static int		frame_counter = 0;

	texture = sprite.death_animation[tex_index];
	initialize_sprite(game, &sprite);
	calculate_sprite_dimensions(game, &sprite);
	draw_sprite_columns(game, &sprite, texture);
	frame_counter++;
	if (frame_counter >= sprite.frames_per_texture)
	{
		tex_index++;
		frame_counter = 0;
	}
	if (tex_index == 4)
	{
		game->map.sprite.killed = 0;
		tex_index = 0;
		randomize_sprite_position(game);
	}
}

/**
 * @brief generates a random position for the sprite within the map boundaries
 * and checks if the position is empty. If it is, it updates the sprite's
 * position. If not, it recursively tries again until a valid position is found.
 * 
 * @param game 
 */
void	randomize_sprite_position(t_game *game)
{
	int			new_sprite_pos[2];

	new_sprite_pos[X] = rand() % game->map.width;
	new_sprite_pos[Y] = rand() % game->map.height;
	if (g_map[new_sprite_pos[Y]][new_sprite_pos[X]] == 0)
	{
		game->map.sprite.pos[X] = new_sprite_pos[X] + 0.5;
		game->map.sprite.pos[Y] = new_sprite_pos[Y] + 0.5;
	}
	else
		randomize_sprite_position(game);
}
