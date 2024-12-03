/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:19:30 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/28 17:02:23 by pehenri2         ###   ########.fr       */
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
	project_sprite_position(game, &sprite);
	calculate_sprite_dimensions(game, &sprite);
	draw_sprite(game, &sprite, texture);
	frame_counter++;
	if (frame_counter >= FRAMES_PER_TEXTURE)
	{
		tex_index++;
		frame_counter = 0;
	}
	if (tex_index == 4)
	{
		game->map.sprite.killed = false;
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
	t_map	map;
	int		new_sprite_pos[2];

	map = game->map;
	new_sprite_pos[X] = get_random_position(game->map.width);
	new_sprite_pos[Y] = get_random_position(game->map.height);
	if (map.grid[new_sprite_pos[Y]][new_sprite_pos[X]] == EMPTY)
	{
		game->map.sprite.pos[X] = new_sprite_pos[X] + 0.5;
		game->map.sprite.pos[Y] = new_sprite_pos[Y] + 0.5;
	}
	else
		randomize_sprite_position(game);
}

int	get_random_position(int max)
{
	static unsigned long	seed;
	static int				initialized = 0;
	int						fd;

	if (!initialized)
	{
		fd = open("/dev/urandom", O_RDONLY);
		if (fd < 0 || read(fd, &seed, sizeof(seed)) != sizeof(seed))
		{
			seed = rand();
		}
		close(fd);
		initialized = 1;
	}
	seed = seed * 1103515245 + 12345;
	return (seed % max);
}

int	calculate_texture_x(int screen_x, t_sprite *sprite, mlx_texture_t *texture)
{
	int	sprite_x;

	sprite_x = screen_x - (-sprite->width / 2 + sprite->screen_x);
	return ((int)(256 * sprite_x * texture->width / sprite->width) / 256);
}

int	calculate_texture_y(int screen_y, t_game *game, t_sprite *sprite,
		mlx_texture_t *texture)
{
	int	sprite_y;

	sprite_y = screen_y * 256 - game->screen_size[Y] * 128 + sprite->height
		* 128;
	return (((sprite_y * texture->height) / sprite->height) / 256);
}
