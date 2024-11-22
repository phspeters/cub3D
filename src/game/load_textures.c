/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:50:21 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/12 17:12:50 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief initializes the textures for different parts of the game map by
 * loading PNG images from specified file paths. It also sets the ceiling and
 * floor colors for the map.
 * 
 * @param game struct containing all game info
 */
void	load_map_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->textures[NORTH] = ft_load_png(game, "./assets/black_wood.png");
	map->textures[SOUTH] = ft_load_png(game, "./assets/wood_brick.png");
	map->textures[WEST] = ft_load_png(game, "./assets/plant_wall.png");
	map->textures[EAST] = ft_load_png(game, "./assets/cave_wall.png");
	map->textures[DOOR] = ft_load_png(game, "./assets/door.png");
}

/**
 * @brief loads sprite textures and death animation textures from PNG files
 * into the game using ft_load_png that checks for any loading errors.
 * If any texture fails to load, it calls the handle_mlx_error function to
 * handle the error.
 * 
 * @param game pointer to the game structure
 */
void	load_sprite_textures(t_game *game)
{
	t_map	*map;

	map = &game->map;
	map->sprite.texture[0] = ft_load_png(game, "./assets/sprite0.png");
	map->sprite.texture[1] = ft_load_png(game, "./assets/sprite1.png");
	map->sprite.texture[2] = ft_load_png(game, "./assets/sprite2.png");
	map->sprite.texture[3] = ft_load_png(game, "./assets/sprite3.png");
	map->sprite.texture[4] = ft_load_png(game, "./assets/sprite4.png");
	map->sprite.texture[5] = ft_load_png(game, "./assets/sprite5.png");
	map->sprite.texture[6] = ft_load_png(game, "./assets/sprite6.png");
	map->sprite.texture[7] = ft_load_png(game, "./assets/sprite7.png");
	map->sprite.texture[8] = ft_load_png(game, "./assets/sprite8.png");
	map->sprite.death_animation[0] = ft_load_png(game, "./assets/death0.png");
	map->sprite.death_animation[1] = ft_load_png(game, "./assets/death1.png");
	map->sprite.death_animation[2] = ft_load_png(game, "./assets/death2.png");
	map->sprite.death_animation[3] = ft_load_png(game, "./assets/death3.png");
}
// Attribution for sprite textures
// Sprites by PiXeRaT (https://opengameart.org/users/pixerat)