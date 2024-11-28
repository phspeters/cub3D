/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:13:27 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/28 16:29:21 by pehenri2         ###   ########.fr       */
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
	if (game->map.sprite.killed == true)
	{
		draw_death_animation_and_respawn(game, sprite);
		return ;
	}
	project_sprite_position(game, &sprite);
	calculate_sprite_dimensions(game, &sprite);
	draw_sprite(game, &sprite, texture);
	(frame_counter)++;
	if (frame_counter >= FRAMES_PER_TEXTURE)
	{
		tex_index = (tex_index + 1) % 9;
		frame_counter = 0;
	}
}

/**
 * @brief adjusts the sprite's position relative to the player, transforms it
 * into the player's view space (always facing the player), and calculates the
 * horizontal screen position where the sprite should be drawn.
 * Steps:
 * 1) Converts sprite position to player-relative coordinates
 * 2) Calculates inverse determinant for camera transformation matrix
 * 3) Transforms sprite from world space to camera space
 * 4) Projects sprite position onto screen coordinates
 *
 * @param game struct with all game information
 * @param sprite information about the sprite
 */
void	project_sprite_position(t_game *game, t_sprite *sprite)
{
	double	dir_plane_inverse_determinant;

	sprite->pos[X] -= game->player.pos[X];
	sprite->pos[Y] -= game->player.pos[Y];
	dir_plane_inverse_determinant = 1.0 / (game->player.plane[X]
			* game->player.dir[Y] - game->player.dir[X]
			* game->player.plane[Y]);
	sprite->transform[X] = dir_plane_inverse_determinant * (game->player.dir[Y]
			* sprite->pos[X] - game->player.dir[X] * sprite->pos[Y]);
	sprite->transform[Y] = dir_plane_inverse_determinant
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
	int	half_sprite_height;
	int	screen_center_y;
	int	half_sprite_width;

	sprite->height = abs((int)(game->screen_size[Y] / sprite->transform[Y]));
	half_sprite_height = sprite->height / 2;
	screen_center_y = game->screen_size[Y] / 2;
	sprite->draw_start[Y] = -half_sprite_height + screen_center_y;
	sprite->draw_end[Y] = half_sprite_height + screen_center_y;
	sprite->draw_start[Y] = fmax(0, sprite->draw_start[Y]);
	sprite->draw_end[Y] = fmin(game->screen_size[Y] - 1, sprite->draw_end[Y]);
	sprite->width = abs((int)(game->screen_size[Y] / sprite->transform[Y]));
	half_sprite_width = sprite->width / 2;
	sprite->draw_start[X] = -half_sprite_width + sprite->screen_x;
	sprite->draw_end[X] = half_sprite_width + sprite->screen_x;
	sprite->draw_start[X] = fmax(0, sprite->draw_start[X]);
	sprite->draw_end[X] = fmin(game->screen_size[X] - 1, sprite->draw_end[X]);
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
void	draw_sprite(t_game *game, t_sprite *sprite,
		mlx_texture_t *texture)
{
	bool	is_visible;
	int		screen_x;

	screen_x = sprite->draw_start[X];
	while (screen_x < sprite->draw_end[X])
	{
		is_visible = (sprite->transform[Y] > 0 && screen_x > 0
				&& screen_x < game->screen_size[X]
				&& sprite->transform[Y]
				< game->player.wall_distance_on_camera_x[screen_x]);
		if (is_visible)
		{
			draw_sprite_columns(game, sprite, texture, screen_x);
		}
		screen_x++;
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
 * @param screen_x horizontal screen position where the sprite should be drawn
 */
void	draw_sprite_columns(t_game *game, t_sprite *sprite,
		mlx_texture_t *texture, int screen_x)
{
	int			screen_y;
	uint32_t	color;

	sprite->texture_coord[X] = calculate_texture_x(screen_x, sprite, texture);
	screen_y = sprite->draw_start[Y];
	while (screen_y < sprite->draw_end[Y])
	{
		sprite->texture_coord[Y] = calculate_texture_y(screen_y, game, sprite,
				texture);
		color = get_texel_color(texture, sprite->texture_coord[X],
				sprite->texture_coord[Y]);
		put_valid_pixel(game, screen_x, screen_y, color);
		screen_y++;
	}
}
