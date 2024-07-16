/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:14:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/16 20:42:46 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_entity player, t_map map, t_cube *cube)
{
	t_entity	vertical_ray;
	t_entity	horizontal_ray;
	float		vertical_distance;
	float		horizontal_distance;

	vertical_ray = calculate_vertical_collision_point(player, map);
	horizontal_ray = calculate_horizontal_collision_point(player, map);
	vertical_distance = sqrt(pow(vertical_ray.pos[X] - player.pos[X], 2)
			+ pow(vertical_ray.pos[Y] - player.pos[Y], 2));
	horizontal_distance = sqrt(pow(horizontal_ray.pos[X] - player.pos[X], 2)
			+ pow(horizontal_ray.pos[Y] - player.pos[Y], 2));
	if (vertical_distance < horizontal_distance)
		draw_line(player.pos, vertical_ray.pos, 0x00FF00FF, cube);
	else
		draw_line(player.pos, horizontal_ray.pos, 0x00FF00FF, cube);
}

// check vertical line hit with horizontal grid line
t_entity	calculate_vertical_collision_point(t_entity player, t_map map)
{
	t_entity	vertical_ray;
	float		neg_inverse_tan;
	int			depth;
	int			current_cell;

	depth = 0;
	vertical_ray.dir_angle = player.dir_angle;
	neg_inverse_tan = -1 / tan(vertical_ray.dir_angle);
	if (vertical_ray.dir_angle > PI)
	{
		vertical_ray.pos[Y] = floor(player.pos[Y] / map.block_size)
			* map.block_size;
		vertical_ray.pos[X] = (player.pos[Y] - vertical_ray.pos[Y])
			* neg_inverse_tan + player.pos[X];
		vertical_ray.movement_delta[Y] = -map.block_size;
		vertical_ray.movement_delta[X] = -vertical_ray.movement_delta[Y]
			* neg_inverse_tan;
	}
	if (vertical_ray.dir_angle < PI)
	{
		vertical_ray.pos[Y] = floor(player.pos[Y] / map.block_size)
			* map.block_size + map.block_size;
		vertical_ray.pos[X] = (player.pos[Y] - vertical_ray.pos[Y])
			* neg_inverse_tan + player.pos[X];
		vertical_ray.movement_delta[Y] = map.block_size;
		vertical_ray.movement_delta[X] = -vertical_ray.movement_delta[Y]
			* neg_inverse_tan;
	}
	if (vertical_ray.dir_angle == 0 || vertical_ray.dir_angle == PI)
	{
		vertical_ray.pos[X] = player.pos[X] * 100000;
		vertical_ray.pos[Y] = player.pos[Y] * 100000;
		depth = 8;
	}
	while (depth < 8)
	{
		current_cell = ((int)vertical_ray.pos[Y] / map.block_size) * map.width
			+ (int)vertical_ray.pos[X] / map.block_size;
		if (current_cell > 0 && current_cell < map.width * map.height
			&& map.grid[current_cell] == 1)
			break ;
		else
		{
			vertical_ray.pos[X] += vertical_ray.movement_delta[X];
			vertical_ray.pos[Y] += vertical_ray.movement_delta[Y];
			depth++;
		}
	}
	return (vertical_ray);
}

// check horizontal line hit with vertical grid line
t_entity	calculate_horizontal_collision_point(t_entity player, t_map map)
{
	t_entity	horizontal_ray;
	float		neg_tan;
	int			depth;
	int			current_cell;

	depth = 0;
	horizontal_ray.dir_angle = player.dir_angle;
	neg_tan = -tan(horizontal_ray.dir_angle);
	if (horizontal_ray.dir_angle > PI / 2 && horizontal_ray.dir_angle < 3 * PI
		/ 2)
	{
		horizontal_ray.pos[X] = floor(player.pos[X] / map.block_size)
			* map.block_size;
		horizontal_ray.pos[Y] = (player.pos[X] - horizontal_ray.pos[X])
			* neg_tan + player.pos[Y];
		horizontal_ray.movement_delta[X] = -map.block_size;
		horizontal_ray.movement_delta[Y] = -horizontal_ray.movement_delta[X]
			* neg_tan;
	}
	if (horizontal_ray.dir_angle < PI / 2 || horizontal_ray.dir_angle > 3 * PI
		/ 2)
	{
		horizontal_ray.pos[X] = floor(player.pos[X] / map.block_size)
			* map.block_size + map.block_size;
		horizontal_ray.pos[Y] = (player.pos[X] - horizontal_ray.pos[X])
			* neg_tan + player.pos[Y];
		horizontal_ray.movement_delta[X] = map.block_size;
		horizontal_ray.movement_delta[Y] = -horizontal_ray.movement_delta[X]
			* neg_tan;
	}
	if (horizontal_ray.dir_angle == PI / 2 || horizontal_ray.dir_angle == 3 * PI
		/ 2)
	{
		horizontal_ray.pos[Y] = player.pos[Y] * 100000;
		horizontal_ray.pos[X] = player.pos[X] * 100000;
		depth = 8;
	}
	while (depth < 8)
	{
		current_cell = ((int)horizontal_ray.pos[X] / map.block_size) * map.width
			+ (int)horizontal_ray.pos[Y] / map.block_size;
		if (current_cell > 0 && current_cell < map.width * map.height
			&& map.grid[current_cell] == 1)
			break ;
		else
		{
			horizontal_ray.pos[Y] += horizontal_ray.movement_delta[Y];
			horizontal_ray.pos[X] += horizontal_ray.movement_delta[X];
			depth++;
		}
	}
	return (horizontal_ray);
}
