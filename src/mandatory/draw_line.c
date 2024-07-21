/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:46:33 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/20 21:59:29 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_texel_color(mlx_texture_t *texture, unsigned int x,
		unsigned int y)
{
	uint8_t	*channel;

	channel = &texture->pixels[(y * texture->width + x)
		* texture->bytes_per_pixel];
	return (channel[0] << 24 | channel[1] << 16 | channel[2] << 8 | channel[3]);
}

void	draw_vertical_line(t_game *game, int x, t_ray ray)
{
	int				y;
	unsigned int	texture[2];
	double			step;
	double			texture_pos;
	double			wall_x;

	y = 0;
	while (y < ray.wall_line_start)
	{
		put_valid_pixel(game->image, x, y, game->map.ceiling);
		y++;
	}
	if (ray.side_hit == 0)
		wall_x = game->player.pos[Y] + ray.perpendicular_wall_distance
			* ray.ray_dir[Y];
	else
		wall_x = game->player.pos[X] + ray.perpendicular_wall_distance
			* ray.ray_dir[X];
	wall_x -= floor((wall_x));
	texture[X] = (int)(wall_x * (double)(ray.wall_texture->width));
	if (ray.side_hit == 0 && ray.ray_dir[X] > 0)
		texture[X] = ray.wall_texture->width - texture[X] - 1;
	if (ray.side_hit == 1 && ray.ray_dir[Y] < 0)
		texture[X] = ray.wall_texture->width - texture[X] - 1;
	texture[X] = fmax(0, fmin(texture[X], ray.wall_texture->width - 1));
	step = 1.0 * ray.wall_texture->height / ray.wall_height;
	texture_pos = (ray.wall_line_start - SCREEN_HEIGHT / 2 + ray.wall_height
			/ 2) * step;
	while (y < ray.wall_line_end)
	{
		texture[Y] = (int)texture_pos;
		texture_pos += step;
		texture[Y] = fmax(0, fmin(texture[Y], ray.wall_texture->height - 1));
		put_valid_pixel(game->image, x, y, get_texel_color(ray.wall_texture,
				texture[X], texture[Y]));
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		put_valid_pixel(game->image, x, y, game->map.floor);
		y++;
	}
}

void	draw_line(int start[2], int end[2], uint32_t color, t_game *game)
{
	t_line_info	line_info;

	line_info = set_line_info(start, end, color);
	if (line_info.abs[X] > line_info.abs[Y])
		draw_shallow_line(line_info, game->image);
	else
		draw_steep_line(line_info, game->image);
}

t_line_info	set_line_info(int start[2], int end[2], uint32_t color)
{
	t_line_info	line_info;

	line_info.start[X] = start[X];
	line_info.start[Y] = start[Y];
	line_info.end[X] = end[X];
	line_info.end[Y] = end[Y];
	line_info.delta[X] = line_info.end[X] - line_info.start[X];
	line_info.delta[Y] = line_info.end[Y] - line_info.start[Y];
	line_info.abs[X] = abs(line_info.delta[X]);
	line_info.abs[Y] = abs(line_info.delta[Y]);
	line_info.color = color;
	return (line_info);
}

/**
 * @brief Function that uses the Bresenham's line algortihm to draw a line
 * between two pixels that are more horizontally distant from each other than
 * they are vertically distant. That is, the absolute value of the difference
 * between the x coordinates of the two pixels is greater than the absolute
 * value of the difference between the y coordinates of the two pixels.
 * @param line_info Struct that contains the information needed to draw the line.
 * @param image Struct that contains the pointer to the image that is being
 * drawn into.
 */
void	draw_shallow_line(t_line_info line_info, mlx_image_t *image)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(image, line_info.start[X], line_info.start[Y],
		line_info.color);
	decision = 2 * line_info.abs[Y] - line_info.abs[X];
	i = 0;
	while (i < line_info.abs[X])
	{
		move_coordinate(&line_info.start[X], line_info.delta[X]);
		if (decision < 0)
			decision = decision + 2 * line_info.abs[Y];
		else
		{
			move_coordinate(&line_info.start[Y], line_info.delta[Y]);
			decision = decision + (2 * line_info.abs[Y] - 2 * line_info.abs[X]);
		}
		put_valid_pixel(image, line_info.start[X], line_info.start[Y],
			line_info.color);
		i++;
	}
}

/**
 * @brief Function that uses the Bresenham's line algortihm to draw a line
 * between two pixels that are more vertically distant from each other than
 * they are horizontally distant. That is, the absolute value of the difference
 * between the y coordinates of the two pixels is greater than the absolute
 * value of the difference between the x coordinates of the two pixels.
 * @param line_info Struct that contains the information needed to draw the line.
 * @param image Struct that contains the pointer to the image that is being
 * drawn into.
 */
void	draw_steep_line(t_line_info line_info, mlx_image_t *image)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(image, line_info.start[X], line_info.start[Y],
		line_info.color);
	decision = 2 * line_info.abs[X] - line_info.abs[Y];
	i = 0;
	while (i < line_info.abs[Y])
	{
		move_coordinate(&line_info.start[Y], line_info.delta[Y]);
		if (decision < 0)
			decision = decision + 2 * line_info.abs[X];
		else
		{
			move_coordinate(&line_info.start[X], line_info.delta[X]);
			decision = decision + (2 * line_info.abs[X] - 2 * line_info.abs[Y]);
		}
		put_valid_pixel(image, line_info.start[X], line_info.start[Y],
			line_info.color);
		i++;
	}
}
