/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_screen_line.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:17:01 by pehenri2          #+#    #+#             */
/*   Updated: 2024/12/03 19:29:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief draws a vertical line on the screen at the given x coordindate, from
 * the ceiling to the floor, using the color information from the map and the
 * texture information from the ray.
 *
 * @param game struct with game information
 * @param x x coordinate of the screen
 * @param ray information about the ray casted on the x coordinate
 */
void	draw_vertical_screen_line(t_game *game, int x, t_ray ray)
{
	draw_colored_segment(game, x, ray, CEILING);
	draw_textured_wall_segment(game, x, ray);
	draw_colored_segment(game, x, ray, FLOOR);
}

/**
 * @brief draws a segment of the ceiling or floor on the screen, using the
 * color information from the map.
 *
 * @param game struct with game information
 * @param x x coordinate of the screen
 * @param ray information about the ray casted on the x coordinate
 * @param segment_id CEILING or FLOOR
 */
void	draw_colored_segment(t_game *game, int x, t_ray ray, int segment_id)
{
	int	y;

	if (segment_id == CEILING)
	{
		y = 0;
		while (y < ray.wall_line_start)
		{
			put_valid_pixel(game, x, y, game->map.ceiling);
			y++;
		}
	}
	else
	{
		y = ray.wall_line_end;
		while (y < game->screen_size[Y])
		{
			put_valid_pixel(game, x, y, game->map.floor);
			y++;
		}
	}
}

/**
 * @brief draws a segment of the wall on the screen, using the texture
 * information to determine the color of each pixel.
 *
 * @param game struct with game information
 * @param x x coordinate of the screen
 * @param ray information about the ray casted on the x coordinate
 */
void	draw_textured_wall_segment(t_game *game, int x, t_ray ray)
{
	t_texture_info	texture_info;
	uint32_t		color;
	int				y;
	int				tex[2];

	calculate_texture_coordinates(game, &ray, &texture_info);
	tex[X] = texture_info.texture_coord[X];
	tex[Y] = texture_info.texture_coord[Y];
	y = ray.wall_line_start;
	while (y < ray.wall_line_end)
	{
		tex[Y] = (int)texture_info.texture_pos & (ray.wall_texture->height - 1);
		texture_info.texture_pos += texture_info.step;
		color = get_texel_color(ray.wall_texture, tex[X], tex[Y]);
		put_valid_pixel(game, x, y, color);
		y++;
	}
}

/**
 * @brief calculates the exact position on the wall where the ray hit,
 * determines the corresponding texture coordinates, adjusts them if necessary,
 * and calculates the step size and initial position for moving through the
 * texture vertically.
 *
 * @param game struct with game information
 * @param ray information about the ray casted on the x coordinate
 * @param texture_info information about the texture to be drawn
 */
void	calculate_texture_coordinates(t_game *game, t_ray *ray,
		t_texture_info *texture_info)
{
	double	wall_x;

	if (ray->side_hit == WEST_EAST)
		wall_x = game->player.pos[Y] + ray->perp_wall_dist
			* ray->ray_dir[Y];
	else
		wall_x = game->player.pos[X] + ray->perp_wall_dist
			* ray->ray_dir[X];
	wall_x -= floor(wall_x);
	texture_info->texture_coord[X] = (int)(wall_x
			* (double)(ray->wall_texture->width));
	if (ray->side_hit == WEST_EAST && ray->ray_dir[X] < 0)
		texture_info->texture_coord[X] = ray->wall_texture->width
			- texture_info->texture_coord[X] - 1;
	if (ray->side_hit == NORTH_SOUTH && ray->ray_dir[Y] > 0)
		texture_info->texture_coord[X] = ray->wall_texture->width
			- texture_info->texture_coord[X] - 1;
	texture_info->step = 1.0 * ray->wall_texture->height / ray->wall_height;
	texture_info->texture_pos = (ray->wall_line_start - game->screen_size[Y] / 2
			+ ray->wall_height / 2) * (texture_info->step);
}

/**
 * @brief calculates the position of a specific texel within a texture's pixel
 * array and retrieves its color channels (RGBA), combining them into a single
 * 32-bit integer representing the color.
 *
 * @param texture texture to get the color from
 * @param x x coordinate of the texel
 * @param y y coordinate of the texel
 * @return uint32_t color of the texel
 */
uint32_t	get_texel_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*channel;

	channel = &texture->pixels[(y * texture->width + x)
		* texture->bytes_per_pixel];
	return (channel[0] << 24 | channel[1] << 16 | channel[2] << 8 | channel[3]);
}
