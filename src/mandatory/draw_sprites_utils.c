/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:19:30 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/29 21:21:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_death_animation_and_respawn(t_game *game, t_sprite sprite)
{
	mlx_texture_t	*texture;
	static int		tex_index = 0;
	static int		frame_counter = 0;

	printf("death animation\n");
	texture = sprite.death_animation[tex_index];
	initialize_sprite(game, &sprite);
	calculate_sprite_dimensions(game, &sprite);
	draw_sprite_stripes(game, &sprite, texture);
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
		respawn_sprite(game);
	}
}

void	respawn_sprite(t_game *game)
{
	//int	new_sprite_pos[2];

	game->map.sprite.pos[X] = 10.5;
	game->map.sprite.pos[Y] = 10.5;
	//new_sprite_pos[X] = get_random_map_coordinate(game->map.width);
	//new_sprite_pos[Y] = get_random_map_coordinate(game->map.height);
	//if (g_map[new_sprite_pos[Y]][new_sprite_pos[X]] == '0')
	//{
	//	game->map.sprite.pos[X] = new_sprite_pos[X] + 0.5;
	//	game->map.sprite.pos[Y] = new_sprite_pos[Y] + 0.5;
	//}
	//else
	//	respawn_sprite(game);
}

int	get_random_map_coordinate(int max)
{
	int				new_sprite_pos;
	int				urandom_fd;
	unsigned int	random_value;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		handle_error("open");
	if (read(urandom_fd, &random_value,
			sizeof(random_value)) != sizeof(random_value))
		handle_error("read");
	new_sprite_pos = random_value % max;
	close(urandom_fd);
	return (new_sprite_pos);
}
