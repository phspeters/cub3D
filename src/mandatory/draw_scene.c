/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:17:01 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/21 13:17:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_delete_image(game->window, game->image);
	game->image = mlx_new_image(game->window, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->image)
		handle_mlx_error(game);
	if (mlx_image_to_window(game->window, game->image, 0, 0) == -1)
		handle_mlx_error(game);
	draw_3d_scene(game);
	draw_minimap(game);
}

void	draw_3d_scene(t_game *game)
{
	int	x_coordinate;

	x_coordinate = 0;
	while (x_coordinate <= SCREEN_WIDTH)
	{
		cast_ray(game, x_coordinate);
		x_coordinate++;
	}
}

void	draw_vertical_line(t_game *game, int x, t_ray ray)
{
	int				y;
	t_texture_info	texture_info;

	y = 0;
	while (y < ray.wall_line_start)
	{
		put_valid_pixel(game->image, x, y, game->map.ceiling);
		y++;
	}
	calculate_texture_coordinates(game, &ray, &texture_info);
	while (y < ray.wall_line_end)
	{
		texture_info.texture_coord[Y] = (int)texture_info.texture_pos & \
			(ray.wall_texture->height - 1);
		texture_info.texture_pos += texture_info.step;
		put_valid_pixel(game->image, x, y, get_texel_color(ray.wall_texture,
				texture_info.texture_coord[X], texture_info.texture_coord[Y]));
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		put_valid_pixel(game->image, x, y, game->map.floor);
		y++;
	}
}

void	calculate_texture_coordinates(t_game *game, t_ray *ray,
		t_texture_info *texture_info)
{
	double	wall_x;

	if (ray->side_hit == 0)
		wall_x = game->player.pos[Y] + ray->perpendicular_wall_distance
			* ray->ray_dir[Y];
	else
		wall_x = game->player.pos[X] + ray->perpendicular_wall_distance
			* ray->ray_dir[X];
	wall_x -= floor(wall_x);
	texture_info->texture_coord[X] = (int)(wall_x
			* (double)(ray->wall_texture->width));
	if (ray->side_hit == 0 && ray->ray_dir[X] > 0)
		texture_info->texture_coord[X] = ray->wall_texture->width
			- texture_info->texture_coord[X] - 1;
	if (ray->side_hit == 1 && ray->ray_dir[Y] < 0)
		texture_info->texture_coord[X] = ray->wall_texture->width
			- texture_info->texture_coord[X] - 1;
	texture_info->step = 1.0 * ray->wall_texture->height / ray->wall_height;
	texture_info->texture_pos = (ray->wall_line_start - SCREEN_HEIGHT / 2
			+ ray->wall_height / 2) * (texture_info->step);
}

uint32_t	get_texel_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*channel;

	channel = &texture->pixels[(y * texture->width + x)
		* texture->bytes_per_pixel];
	return (channel[0] << 24 | channel[1] << 16 | channel[2] << 8 | channel[3]);
}
