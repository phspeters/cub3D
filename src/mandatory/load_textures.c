/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:50:21 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/25 20:50:41 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_map_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->textures[NORTH] = mlx_load_png("./assets/black_wood.png");
	if (!map->textures[NORTH])
		handle_mlx_error(game);
	map->textures[SOUTH] = mlx_load_png("./assets/wood_brick.png");
	if (!map->textures[SOUTH])
		handle_mlx_error(game);
	map->textures[WEST] = mlx_load_png("./assets/plant_wall.png");
	if (!map->textures[WEST])
		handle_mlx_error(game);
	map->textures[EAST] = mlx_load_png("./assets/cave_wall.png");
	if (!map->textures[EAST])
		handle_mlx_error(game);
	map->textures[DOOR] = mlx_load_png("./assets/eagle.png");
	if (!map->textures[DOOR])
		handle_mlx_error(game);
	map->ceiling = 0x87CEEBFF;
	map->floor = 0xC0C0C0FF;
}

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
	if (!map->sprite.texture[0] || !map->sprite.texture[1]
		|| !map->sprite.texture[2] || !map->sprite.texture[3]
		|| !map->sprite.texture[4] || !map->sprite.texture[5]
		|| !map->sprite.texture[6] || !map->sprite.texture[7]
		|| !map->sprite.texture[8])
		handle_mlx_error(game);
}
