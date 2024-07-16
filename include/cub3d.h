/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:33:51 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/16 20:19:22 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <errno.h>

# define WIDTH 1024
# define HEIGHT 512
# define PI 3.14159

enum e_axis
{
	X,
	Y
};

typedef struct s_map
{
	int			width;
	int			height;
	int			block_size;
	int			*grid;
	uint32_t	color;
}				t_map;

typedef struct s_entity
{
	float		pos[2];
	float		movement_delta[2];
	float		dir_angle;
	uint32_t	color;
}				t_entity;

typedef struct s_cube
{
	mlx_t			*window;
	mlx_image_t		*image;
	t_map			map;
	t_entity		player;
}				t_cube;

typedef struct s_line_info
{
	int				start[2];
	int				end[2];
	int				delta[2];
	unsigned int	abs[2];
	uint32_t		color;
}					t_line_info;

/*------------draw_elements.c-------------*/

void		draw_loop(void *param);
void		draw_map(t_cube *cube, uint32_t color, t_map map);
void		draw_player(t_entity player, t_cube *cube);
void		draw_block(float start[2], int block_size, uint32_t color,
				t_cube *cube);

/*--------------draw_line.c---------------*/

void		draw_line(float start[2], float end[2], uint32_t color,
				t_cube *cube);
t_line_info	set_line_info(float start[2], float end[2], uint32_t color);
void		draw_shallow_line(t_line_info line_info, mlx_image_t *image);
void		draw_steep_line(t_line_info line_info, mlx_image_t *image);

/*-----------------hooks.c-----------------*/

void		action_hooks(void *param);
void		close_loop_hook(void *param);
void		move_player_loop_hook(void *param);

/*----------------raycasting.c-----------------*/

void		draw_rays(t_entity player, t_map map, t_cube *cube);
t_entity	calculate_vertical_collision_point(t_entity player, t_map map);
t_entity	calculate_horizontal_collision_point(t_entity player, t_map map);

/*----------------utils.c-----------------*/
void		put_valid_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		move_coordinate(int *coordinate, int direction);

#endif