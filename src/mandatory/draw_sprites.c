/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:13:27 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/16 15:44:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief checks if the sprite was killed, initializes it, calculates its
 * dimensions, draws it on the screen, and handles sprite animation by updating
 * the texture index and frame counter.
 * 
 * @param game struct with all game information
 */
void	draw_sprites(t_game *game)
{
	t_sprite		sprite;
	mlx_texture_t	*texture;
	static int		tex_index = 0;
	static int		frame_counter = 0;

	sprite = game->map.sprite;
	texture = sprite.texture[tex_index];
	if (game->map.sprite.killed == 1)
	{
		draw_death_animation_and_respawn(game, sprite);
		return ;
	}
	initialize_sprite(game, &sprite);
	calculate_sprite_dimensions(game, &sprite);
	draw_sprite_columns(game, &sprite, texture);
	(frame_counter)++;
	if (frame_counter >= sprite.frames_per_texture)
	{
		tex_index = (tex_index + 1) % 9;
		frame_counter = 0;
	}
}

/**
 * @brief adjusts the sprite's position relative to the player, transforms it
 * into the player's view space (always facing the player), and calculates the
 * horizontal screen position where the sprite should be drawn.
 * 
 * @param game struct with all game information
 * @param sprite information about the sprite
 */
void	initialize_sprite(t_game *game, t_sprite *sprite)
{
	sprite->pos[X] -= game->player.pos[X];
	sprite->pos[Y] -= game->player.pos[Y];
	sprite->inverse_projection_determinant = 1.0 / (game->player.plane[X]
			* game->player.dir[Y] - game->player.dir[X]
			* game->player.plane[Y]);
	sprite->transform[X] = sprite->inverse_projection_determinant
		* (game->player.dir[Y] * sprite->pos[X] - game->player.dir[X]
			* sprite->pos[Y]);
	sprite->transform[Y] = sprite->inverse_projection_determinant
		* (-game->player.plane[Y] * sprite->pos[X] + game->player.plane[X]
			* sprite->pos[Y]);
	sprite->screen_x = (int)((game->screen_size[X] / 2) * (1
				+ sprite->transform[X] / sprite->transform[Y]));
}

/**
 * @brief calculates the height and width of the sprite based on its distance
 * from the player, and determines the start and end positions for drawing the
 * sprite on the screen, ensuring that the sprite is correctly centered and
 * clamped within the screen boundaries.
 * 
 * @param game struct with all game information
 * @param sprite information about the sprite
 */
void	calculate_sprite_dimensions(t_game *game, t_sprite *sprite)
{
	sprite->height = abs((int)(game->screen_size[Y] / (sprite->transform[Y])));
	sprite->draw_start[Y] = -sprite->height / 2 + game->screen_size[Y] / 2;
	if (sprite->draw_start[Y] < 0)
		sprite->draw_start[Y] = 0;
	sprite->draw_end[Y] = sprite->height / 2 + game->screen_size[Y] / 2;
	if (sprite->draw_end[Y] >= game->screen_size[Y])
		sprite->draw_end[Y] = game->screen_size[Y] - 1;
	sprite->width = abs((int)(game->screen_size[Y] / (sprite->transform[Y])));
	sprite->draw_start[X] = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start[X] < 0)
		sprite->draw_start[X] = 0;
	sprite->draw_end[X] = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end[X] >= game->screen_size[X])
		sprite->draw_end[X] = game->screen_size[X] - 1;
}

/**
 * @brief iterates through the vertical columns of a sprite, calculates the
 * corresponding texture coordinates, checks if the sprite is visible and not
 * occluded by walls, and draws the sprite's pixels on the screen.
 * 
 * @param game struct with all game information
 * @param sprite information about the sprite
 * @param texture information about the sprite's texture
 */
void	draw_sprite_columns(t_game *game, t_sprite *sprite,
		mlx_texture_t *texture)
{
	int	column;

	column = sprite->draw_start[X];
	while (column < sprite->draw_end[X])
	{
		sprite->texture_coord[X] = (int)(256 * (column - (-sprite->width / 2
						+ sprite->screen_x)) * texture->width / sprite->width)
			/ 256;
		if (sprite->transform[Y] > 0 && column > 0
			&& column < game->screen_size[X]
			&& sprite->transform[Y]
			< game->player.wall_distance_on_camera_x[column])
		{
			draw_sprite_pixels(game, sprite, texture, column);
		}
		column++;
	}
}

/**
 * @brief iterates through the vertical pixels of a sprite, calculates the
 * corresponding texture coordinates, retrieves the texel color from the
 * texture, and draws the pixel on the screen.
 * 
 * @param game struct with all game information
 * @param sprite information about the sprite
 * @param texture information about the sprite's texture
 * @param column 
 */
void	draw_sprite_pixels(t_game *game, t_sprite *sprite,
		mlx_texture_t *texture, int column)
{
	int	y;

	y = sprite->draw_start[Y];
	while (y < sprite->draw_end[Y])
	{
		sprite->texture_y_position = y * 256 - game->screen_size[Y] * 128
			+ sprite->height * 128;
		sprite->texture_coord[Y] = ((sprite->texture_y_position
					* texture->height) / sprite->height) / 256;
		put_valid_pixel(game, column, y, get_texel_color(texture,
				sprite->texture_coord[X], sprite->texture_coord[Y]));
		y++;
	}
}
