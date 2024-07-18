/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:46:33 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/18 18:17:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_game *game, int x, t_ray ray)
{
	int	y;

	y = ray.wall_line_start;
	while (y < ray.wall_line_end)
	{
		put_valid_pixel(game->image, x, y, ray.wall_color);
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
 *
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
 *
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
