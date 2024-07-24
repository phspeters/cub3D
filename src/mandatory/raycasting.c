/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:14:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/23 21:13:01 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	perform_dda(t_map *map, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->distance_to_side[X] < ray->distance_to_side[Y])
		{
			ray->distance_to_side[X] += ray->delta_distance[X];
			map->current[X] += ray->grid_step[X];
			ray->side_hit = 0;
		}
		else
		{
			ray->distance_to_side[Y] += ray->delta_distance[Y];
			map->current[Y] += ray->grid_step[Y];
			ray->side_hit = 1;
		}
		if (g_map[map->current[Y]][map->current[X]] > 0)
			ray->hit = g_map[map->current[Y]][map->current[X]];
	}
}

void	calculate_wall_distance_and_draw(t_game *game, t_ray *ray,
		int x_coordinate)
{
	if (ray->side_hit == 0)
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
	if (ray->hit == 'D')
		ray->wall_texture = game->map.door_texture;
	else if (ray->side_hit == 1 && ray->ray_dir[Y] < 0)
		ray->wall_texture = game->map.north_texture;
	else if (ray->side_hit == 1 && ray->ray_dir[Y] > 0)
		ray->wall_texture = game->map.south_texture;
	else if (ray->side_hit == 0 && ray->ray_dir[X] > 0)
		ray->wall_texture = game->map.east_texture;
	else if (ray->side_hit == 0 && ray->ray_dir[X] < 0)
		ray->wall_texture = game->map.west_texture;
	draw_vertical_line(game, x_coordinate, *ray);
}
