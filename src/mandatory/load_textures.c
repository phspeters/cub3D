/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:50:21 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/16 17:01:06 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_map_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->textures[NORTH] = mlx_load_png("./assets/black_wood.png");
	map->textures[SOUTH] = mlx_load_png("./assets/wood_brick.png");
	map->textures[WEST] = mlx_load_png("./assets/plant_wall.png");
	map->textures[EAST] = mlx_load_png("./assets/cave_wall.png");
	map->textures[DOOR] = mlx_load_png("./assets/door.png");
	if (!map->textures[NORTH] || !map->textures[SOUTH] || !map->textures[WEST]
		|| !map->textures[EAST] || !map->textures[DOOR])
		handle_mlx_error(game);
	map->ceiling = 0x87CEEBFF;
	map->floor = 0xC0C0C0FF;
}

/**
 * @brief loads sprite textures and death animation textures from PNG files
 * into the game using mlx_load_png, and checks for any loading errors.
 * If any texture fails to load, it calls the handle_mlx_error function to
 * handle the error.
 * 
 * @param game pointer to the game structure
 */
void	load_sprite_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->sprite.texture[0] = mlx_load_png("./assets/sprite0.png");
	map->sprite.texture[1] = mlx_load_png("./assets/sprite1.png");
	map->sprite.texture[2] = mlx_load_png("./assets/sprite2.png");
	map->sprite.texture[3] = mlx_load_png("./assets/sprite3.png");
	map->sprite.texture[4] = mlx_load_png("./assets/sprite4.png");
	map->sprite.texture[5] = mlx_load_png("./assets/sprite5.png");
	map->sprite.texture[6] = mlx_load_png("./assets/sprite6.png");
	map->sprite.texture[7] = mlx_load_png("./assets/sprite7.png");
	map->sprite.texture[8] = mlx_load_png("./assets/sprite8.png");
	map->sprite.death_animation[0] = mlx_load_png("./assets/death0.png");
	map->sprite.death_animation[1] = mlx_load_png("./assets/death1.png");
	map->sprite.death_animation[2] = mlx_load_png("./assets/death2.png");
	map->sprite.death_animation[3] = mlx_load_png("./assets/death3.png");
	if (!map->sprite.texture[0] || !map->sprite.texture[1]
		|| !map->sprite.texture[2] || !map->sprite.texture[3]
		|| !map->sprite.texture[4] || !map->sprite.texture[5]
		|| !map->sprite.texture[6] || !map->sprite.texture[7]
		|| !map->sprite.texture[8] || !map->sprite.death_animation[0]
		|| !map->sprite.death_animation[1] || !map->sprite.death_animation[2]
		|| !map->sprite.death_animation[3])
		handle_mlx_error(game);
}
