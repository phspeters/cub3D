/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:46:33 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/16 16:16:10 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief uses the Bresenham's line algorithm to draw a line between two pixels.
 * The set_line_info function is used to initialize the line information, and
 * the draw_shallow_line and draw_steep_line functions are used to draw the
 * line based on its type.
 *  
 * @param start x and y coordinates of the starting pixel.
 * @param end x and y coordinates of the ending pixel.
 * @param color rgba channel of the color of the line.
 * @param game struct that contains the pointer to the image that is being
 * drawn into.
 */
void	draw_line(int start[2], int end[2], uint32_t color, t_game *game)
{
	t_line_info	line_info;

	line_info = set_line_info(start, end, color);
	if (line_info.abs[X] > line_info.abs[Y])
		draw_shallow_line(line_info, game);
	else
		draw_steep_line(line_info, game);
}

/**
 * @brief sets the information needed to draw a line between two pixels
 * using the Bresenham's line algorithm.
 * 
 * @param start x and y coordinates of the starting pixel.
 * @param end x and y coordinates of the ending pixel.
 * @param color rgba channel of the color of the line.
 * @return t_line_info holds the information needed to draw a line.
 */
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
 * @brief uses the Bresenham's line algorithm to draw a line between two pixels
 * that are more horizontally distant from each other than vertically. That is,
 * the line is closer to the x axis than to the y axis.
 * It iterates through the x-coordinates of the line, using a decision variable
 * to determine whether to move vertically as well as horizontally.
 *
 * @param line_info Struct that contains the information needed to draw the line.
 * @param game Struct that contains the pointer to the image that is being
 * drawn into.
 */
void	draw_shallow_line(t_line_info line_info, t_game *game)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(game, line_info.start[X], line_info.start[Y],
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
		put_valid_pixel(game, line_info.start[X], line_info.start[Y],
			line_info.color);
		i++;
	}
}

/**
 * @brief uses the Bresenham's line algorithm to draw a line between two pixels
 * that are more vertically distant from each other than horizontally. That is,
 * the line is closer to the y axis than to the x axis.
 * It iterates through the y-coordinates of the line, using a decision variable
 * to determine whether to move horizontally as well as vertically.
 *
 * @param line_info Struct that contains the information needed to draw the line.
 * @param game Struct that contains the pointer to the image that is being
 * drawn into.
 */
void	draw_steep_line(t_line_info line_info, t_game *game)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(game, line_info.start[X], line_info.start[Y],
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
		put_valid_pixel(game, line_info.start[X], line_info.start[Y],
			line_info.color);
		i++;
	}
}

/**
 * @brief adjusts a coordinate value by either incrementing or decrementing it
 * based on the provided direction.
 * 
 * @param coordinate Pointer to the coordinate that will be moved.
 * @param direction Direction in which the coordinate will be moved.
 */
void	move_coordinate(int *coordinate, int direction)
{
	if (direction < 0)
		*coordinate -= 1;
	else
		*coordinate += 1;
}
