/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:14:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/18 18:49:54 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(t_game *game, int x_coordinate)
{
	t_ray		ray;
	t_player	player;
	t_map		map;

	player = game->player;
	map = game->map;
	ray.camera_x_coordinate = 2 * x_coordinate / (double)SCREEN_WIDTH - 1;
	ray.ray_dir[X] = player.dir[X] + player.plane[X] * (2 * x_coordinate
			/ (double)SCREEN_WIDTH - 1);
	ray.ray_dir[Y] = player.dir[Y] + player.plane[Y] * (2 * x_coordinate
			/ (double)SCREEN_WIDTH - 1);
	map.current_x = (int)player.pos[X];
	map.current_y = (int)player.pos[Y];
	if (ray.ray_dir[X] == 0)
		ray.delta_distance[X] = 1e30;
	else
		ray.delta_distance[X] = fabs(1 / ray.ray_dir[X]);
	if (ray.ray_dir[Y] == 0)
		ray.delta_distance[Y] = 1e30;
	else
		ray.delta_distance[Y] = fabs(1 / ray.ray_dir[Y]);
	ray.hit = 0;
	if (ray.ray_dir[X] < 0)
	{
		ray.grid_step[X] = -1;
		ray.distance_to_side[X] = (player.pos[X] - map.current_x)
			* ray.delta_distance[X];
	}
	else
	{
		ray.grid_step[X] = 1;
		ray.distance_to_side[X] = (map.current_x + 1.0 - player.pos[X])
			* ray.delta_distance[X];
	}
	if (ray.ray_dir[Y] < 0)
	{
		ray.grid_step[Y] = -1;
		ray.distance_to_side[Y] = (player.pos[Y] - map.current_y)
			* ray.delta_distance[Y];
	}
	else
	{
		ray.grid_step[Y] = 1;
		ray.distance_to_side[Y] = (map.current_y + 1.0 - player.pos[Y])
			* ray.delta_distance[Y];
	}
	while (ray.hit == 0)
	{
		if (ray.distance_to_side[X] < ray.distance_to_side[Y])
		{
			ray.distance_to_side[X] += ray.delta_distance[X];
			map.current_x += ray.grid_step[X];
			ray.side_hit = 0;
		}
		else
		{
			ray.distance_to_side[Y] += ray.delta_distance[Y];
			map.current_y += ray.grid_step[Y];
			ray.side_hit = 1;
		}
		if (g_map[map.current_y][map.current_x] > 0)
			ray.hit = 1;
	}
	if (ray.side_hit == 0)
		ray.perpendicular_wall_distance = ray.distance_to_side[X]
			- ray.delta_distance[X];
	else
		ray.perpendicular_wall_distance = ray.distance_to_side[Y]
			- ray.delta_distance[Y];
	ray.wall_height = (int)(SCREEN_HEIGHT / ray.perpendicular_wall_distance);
	ray.wall_line_start = -ray.wall_height / 2 + SCREEN_HEIGHT / 2;
	if (ray.wall_line_start < 0)
		ray.wall_line_start = 0;
	ray.wall_line_end = ray.wall_height / 2 + SCREEN_HEIGHT / 2;
	if (ray.wall_line_end >= SCREEN_HEIGHT)
		ray.wall_line_end = SCREEN_HEIGHT - 1;
	ray.wall_color = 0xFF0000FF;
	if (ray.side_hit == 1)
		ray.wall_color = 0xAA0000FF;
	draw_vertical_line(game, x_coordinate, ray);
}
