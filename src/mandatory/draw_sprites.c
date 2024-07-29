/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:13:27 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/29 18:19:10 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprites(t_game *game)
{
	t_sprite	sprite;
	static int	tex_index = 0;
	static int	frame_counter = 0;

	sprite = game->map.sprite;
	initialize_sprite(game, &sprite);
	calculate_sprite_dimensions(game, &sprite);
	draw_sprite_stripes(game, &sprite, tex_index);
	(frame_counter)++;
	if (frame_counter >= sprite.frames_per_texture)
	{
		tex_index = (tex_index + 1) % 9;
		frame_counter = 0;
	}
	if (game->map.sprite.killed == 1)
	{
		game->map.sprite.pos[X] = 11.5;
		game->map.sprite.pos[Y] = 21.5;
		game->map.sprite.killed = 0;
	}
}

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

void	draw_sprite_stripes(t_game *game, t_sprite *sprite, int tex_index)
{
	int	stripe;

	stripe = sprite->draw_start[X];
	while (stripe < sprite->draw_end[X])
	{
		sprite->texture_coord[X] = (int)(256 * (stripe - (-sprite->width / 2
						+ sprite->screen_x)) * sprite->texture[tex_index]->width
				/ sprite->width) / 256;
		if (sprite->transform[Y] > 0
			&& stripe > 0
			&& stripe < game->screen_size[X]
			&& sprite->transform[Y]
			< game->player.wall_distance_on_camera_x[stripe])
		{
			draw_sprite_pixels(game, sprite, stripe, tex_index);
		}
		stripe++;
	}
}

void	draw_sprite_pixels(t_game *game, t_sprite *sprite, int stripe,
		int tex_index)
{
	int	y;

	y = sprite->draw_start[Y];
	while (y < sprite->draw_end[Y])
	{
		sprite->texture_y_position = y * 256 - game->screen_size[Y] * 128
			+ sprite->height * 128;
		sprite->texture_coord[Y] = ((sprite->texture_y_position
					* sprite->texture[tex_index]->height) / sprite->height)
			/ 256;
		put_valid_pixel(game, stripe, y,
			get_texel_color(sprite->texture[tex_index],
				sprite->texture_coord[X], sprite->texture_coord[Y]));
		y++;
	}
}
