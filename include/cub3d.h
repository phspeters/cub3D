/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:33:51 by pehenri2          #+#    #+#             */
/*   Updated: 2024/07/20 21:59:05 by pehenri2         ###   ########.fr       */
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

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

enum e_axis
{
	X,
	Y
};

typedef struct s_map
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	uint32_t		ceiling;
	uint32_t		floor;
	int				grid[MAP_HEIGHT][MAP_WIDTH];
	int				current[2];
	int				width;
	int				height;
	int				minimap_block_size;
}				t_map;

typedef struct s_player
{
	double		pos[2];
	double		dir[2];
	double		plane[2];
	uint32_t	color;
}				t_player;

typedef struct s_ray
{
	double			ray_dir[2];
	double			camera_x_coordinate;
	double			distance_to_side[2];
	double			delta_distance[2];
	double			perpendicular_wall_distance;
	mlx_texture_t	*wall_texture;
	int				wall_height;
	int				wall_line_start;
	int				wall_line_end;
	int				grid_step[2];
	int				hit;
	int				side_hit;
}				t_ray;

typedef struct s_game
{
	mlx_t			*window;
	mlx_image_t		*image;
	t_map			map;
	t_player		player;
}					t_game;

typedef struct s_line_info
{
	int				start[2];
	int				end[2];
	int				delta[2];
	unsigned int	abs[2];
	uint32_t		color;
}					t_line_info;

extern int	g_map[MAP_HEIGHT][MAP_WIDTH];

/*------------draw_elements.c-------------*/

void		draw_loop(void *param);
void		draw_3d_scene(t_game *game);
void		draw_minimap(t_game *game);
void		draw_player(t_game *game);
void		draw_block(double start[2], int block_size, uint32_t color,
				t_game *game);

/*--------------draw_line.c---------------*/

void		draw_vertical_line(t_game *game, int x, t_ray ray);
void		draw_line(int start[2], int end[2], uint32_t color,
				t_game *game);
t_line_info	set_line_info(int start[2], int end[2], uint32_t color);
void		draw_shallow_line(t_line_info line_info, mlx_image_t *image);
void		draw_steep_line(t_line_info line_info, mlx_image_t *image);

/*-----------------hooks.c-----------------*/

void		action_hooks(void *param);
void		close_loop_hook(void *param);
void		move_player_loop_hook(void *param);

/*player.c*/

void		move_player(t_game *game, t_player *player, double move_speed,
				double collision_distance);
void		rotate_player_left(t_game *game, t_player *player,
				double rot_speed);
void		rotate_player_right(t_game *game, t_player *player,
				double rot_speed);

/*----------------raycasting.c-----------------*/

void		cast_ray(t_game *game, int x_coordinate);
void		initialize_ray_and_player(t_game *game, t_ray *ray,
				int x_coordinate);
void		calculate_step_and_initial_side_distance(t_game *game,
				t_player *player, t_ray *ray);
void		perform_dda(t_map *map, t_ray *ray);
void		calculate_wall_distance_and_draw(t_game *game, t_ray *ray,
				int x_coordinate);

/*----------------utils.c-----------------*/
void		put_valid_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		move_coordinate(int *coordinate, int direction);

#endif