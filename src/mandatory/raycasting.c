/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:14:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/18 17:06:53 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief casts a single ray for a given x-coordinate on the screen. It
 * initializes the ray and player, calculates the step direction and initial
 * side distance, performs the DDA algorithm to find the wall hit by the ray,
 * and then calculates the wall distance and draws the result on the screen.
 * This function is part of the raycasting process used to render a 3D view
 * from a 2D map.
 * 
 * @param game struct containing the game data
 * @param x_coordinate on the screen
 */
void	cast_ray(t_game *game, int x_coordinate)
{
	t_ray		ray;
	t_player	*player;
	t_map		*map;

	player = &game->player;
	map = &game->map;
	initialize_ray_and_player(game, &ray, x_coordinate);
	calculate_step_and_initial_side_distance(game, player, &ray);
	perform_dda(map, &ray);
	calculate_wall_distance_and_draw(game, &ray, x_coordinate);
}

/**
 * @brief sets up the initial state of the ray and player for a given
 * x-coordinate on the screen. It calculates the camera x-coordinate,
 * ray direction, initializes the ray's hit flag, sets the current map
 * position to the player's position, and calculates the delta distance for
 * the ray in the x and y directions.
 * 
 * @param game struct containing the game data
 * @param ray struct containing the ray data
 * @param x_coordinate on the screen
 */
void	initialize_ray_and_player(t_game *game, t_ray *ray, int x_coordinate)
{
	t_player	player;

	player = game->player;
	ray->camera_x_coordinate = 2 * x_coordinate / (double)game->screen_size[X]
		- 1;
	ray->ray_dir[X] = player.dir[X] + player.plane[X]
		* ray->camera_x_coordinate;
	ray->ray_dir[Y] = player.dir[Y] + player.plane[Y]
		* ray->camera_x_coordinate;
	ray->hit = 0;
	game->map.current[X] = (int)player.pos[X];
	game->map.current[Y] = (int)player.pos[Y];
	if (ray->ray_dir[X] == 0)
		ray->delta_distance[X] = 1e30;
	else
		ray->delta_distance[X] = fabs(1 / ray->ray_dir[X]);
	if (ray->ray_dir[Y] == 0)
		ray->delta_distance[Y] = 1e30;
	else
		ray->delta_distance[Y] = fabs(1 / ray->ray_dir[Y]);
}

/**
 * @brief determines the initial step direction and distance to the first side
 * of a grid cell for a ray being cast. It sets the step direction (grid_step)
 * and calculates the initial distance to the side (distance_to_side) for both
 * the X and Y directions based on the ray's direction. This setup is essential
 * for the DDA algorithm to correctly traverse the grid cells and determine
 * intersections.
 * 
 * @param game struct containing the game data
 * @param player struct containing the player data
 * @param ray struct containing the ray data
 */
void	calculate_step_and_initial_side_distance(t_game *game, t_player *player,
		t_ray *ray)
{
	if (ray->ray_dir[X] < 0)
	{
		ray->grid_step[X] = -1;
		ray->distance_to_side[X] = (player->pos[X] - game->map.current[X])
			* ray->delta_distance[X];
	}
	else
	{
		ray->grid_step[X] = 1;
		ray->distance_to_side[X] = (game->map.current[X] + 1.0 - player->pos[X])
			* ray->delta_distance[X];
	}
	if (ray->ray_dir[Y] < 0)
	{
		ray->grid_step[Y] = -1;
		ray->distance_to_side[Y] = (player->pos[Y] - game->map.current[Y])
			* ray->delta_distance[Y];
	}
	else
	{
		ray->grid_step[Y] = 1;
		ray->distance_to_side[Y] = (game->map.current[Y] + 1.0 - player->pos[Y])
			* ray->delta_distance[Y];
	}
}

/**
 * @brief uses the Digital Differential Analyzer (DDA) algorithm to advance
 * a ray step by step through a 2D grid until it hits a wall. It updates the
 * ray's distance to the next vertical and horizontal grid lines, moves the
 * current position in the map, and checks if a wall is hit.
 * 
 * @param map struct containing the map data
 * @param ray struct containing the ray data
 */
void	perform_dda(t_map *map, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->distance_to_side[X] < ray->distance_to_side[Y])
		{
			ray->distance_to_side[X] += ray->delta_distance[X];
			map->current[X] += ray->grid_step[X];
			ray->side_hit = WEST_EAST;
		}
		else
		{
			ray->distance_to_side[Y] += ray->delta_distance[Y];
			map->current[Y] += ray->grid_step[Y];
			ray->side_hit = NORTH_SOUTH;
		}
		if (map->grid[map->current[Y]][map->current[X]] > EMPTY)
			ray->hit = map->grid[map->current[Y]][map->current[X]];
	}
}

/**
 * @brief calculates the perpendicular distance to the wall hit by the ray,
 * determines the height and position of the wall slice to be drawn, selects
 * the appropriate wall texture, and then draws the vertical line representing
 * the wall slice on the screen.
 * 
 * @param game struct containing the game data
 * @param ray struct containing the ray data
 * @param x_coordinate on the screen
 */
void	calculate_wall_distance_and_draw(t_game *game, t_ray *ray,
		int x_coordinate)
{
	if (ray->side_hit == WEST_EAST)
		ray->perpendicular_wall_distance = ray->distance_to_side[X]
			- ray->delta_distance[X];
	else
		ray->perpendicular_wall_distance = ray->distance_to_side[Y]
			- ray->delta_distance[Y];
	ray->wall_height = (int)(game->screen_size[Y]
			/ ray->perpendicular_wall_distance);
	ray->wall_line_start = -ray->wall_height / 2 + game->screen_size[Y] / 2;
	if (ray->wall_line_start < 0)
		ray->wall_line_start = 0;
	ray->wall_line_end = ray->wall_height / 2 + game->screen_size[Y] / 2;
	if (ray->wall_line_end >= game->screen_size[Y])
		ray->wall_line_end = game->screen_size[Y] - 1;
	if (ray->hit == CLOSED_DOOR)
		ray->wall_texture = game->map.textures[DOOR];
	else if (ray->side_hit == NORTH_SOUTH && ray->ray_dir[Y] < 0)
		ray->wall_texture = game->map.textures[NORTH];
	else if (ray->side_hit == NORTH_SOUTH && ray->ray_dir[Y] > 0)
		ray->wall_texture = game->map.textures[SOUTH];
	else if (ray->side_hit == WEST_EAST && ray->ray_dir[X] > 0)
		ray->wall_texture = game->map.textures[EAST];
	else if (ray->side_hit == WEST_EAST && ray->ray_dir[X] < 0)
		ray->wall_texture = game->map.textures[WEST];
	draw_vertical_line(game, x_coordinate, *ray);
}
