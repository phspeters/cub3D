/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:33:51 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/03 16:54:00 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MAX_MAP_SIZE 1000
# define MINIMAP_SIZE 25
# define MOVEMENT_SPEED_MULTIPLIER 5.0
# define ROTATION_SPEED_MULTIPLIER 2.0
# define COLLISION_DISTANCE_MULTIPLIER 2

#define WALL 1         // Caracter que representa uma parede
#define EMPTY 0        // Caracter que representa um espaço vazio

// Estrutura de posição
typedef struct {
    int x;
    int y;
} t_pos;

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
};

enum e_axis
{
	X,
	Y
};

enum e_direction
{
	RIGHT = 1,
	LEFT = -1
};

enum e_texture_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR
};

enum e_minimap_colors
{
	WALL_COLOR = 0xFFFFFFFF,
	FLOOR_COLOR = 0x000000FF,
	DOOR_COLOR = 0x0000FFFF,
	PLAYER_COLOR = 0xFF0000FF
};

typedef struct s_line_info
{
	int				start[2];
	int				end[2];
	int				delta[2];
	unsigned int	abs[2];
}					t_line_info;

typedef struct s_sprite
{
	double			pos[2];
	double			transform[2];
	double			inverse_projection_determinant;
	int				draw_start[2];
	int				draw_end[2];
	int				texture_coord[2];
	int				screen_x;
	int				texture_y_position;
	int				frames_per_texture;
	int				width;
	int				height;
	int				killed;
}					t_sprite;

typedef struct s_ray
{
	double			ray_dir[2];
	double			distance_to_side[2];
	double			delta_distance[2];
	double			camera_x_coordinate;
	double			perpendicular_wall_distance;
	int				wall_height;
	int				wall_line_start;
	int				wall_line_end;
	int				grid_step[2];
	int				hit;
	int				side_hit;
}					t_ray;

typedef struct s_texture_info
{
	int				texture_coord[2];
	double			step;
	double			texture_pos;
	double			wall_x;
}					t_texture_info;

typedef struct s_player
{
	char			start_dir;
	double			pos[2];
	double			dir[2];
	double			plane[2];
	double			*wall_distance_on_camera_x;
	char			player_start_char;
}					t_player;

typedef struct s_map
{
	char			*texture_path[5];
	t_sprite		sprite;
	int				**grid;
	int				current[2];
	uint32_t		ceiling;
	uint32_t		floor;
	int				width;
	int				height;
	int				minimap_block_size;
}					t_map;

typedef struct s_game
{
	t_map			map;
	t_player		player;
}					t_game;

char	*trim_line(char *line);


/*--------------debugging.c---------------*/
void	print_texture_paths(t_game *game);
void	print_rgb_values(t_game *game);
void	print_map_grid(t_game *game);
void	print_validate_map_borders(t_game *game);

/*--------------chack_file.c---------------*/
int		check_file(char *argv_file, bool cub);

/*--------------check_texture.c---------------*/
int		is_texture_line(char *line);
int		is_texture_exists(char *texture_path);
int		validate_textures(t_game *game, char *line);
int		validate_all_textures(t_game *game);
int		set_texture_path(char **texture_dest, char *line);

/*--------------check_rgb.c---------------*/
int		is_rgb_line(char *line);
int		parse_rgb_value(char **line_ptr, int *value);
int		parse_rgb(t_game *game, char *line);
int		validate_rgb(t_game *game, char *line);
int		validate_all_floor_ceiling(t_game *game);

/*--------------calculate_allocate_map.c---------------*/
int		calculate_map_dimensions(t_game *game, char *file_path);
int		is_map_line(char *line);
void	allocate_map_grid(t_game *game);

/*--------------process_map.c---------------*/
void	process_map_line(t_game *game, char *line);
void	set_player_start_dir(t_game *game, char start_dir);

/*--------------check_map.c---------------*/
int		validate_map_borders(t_game *game);
int		validate_single_player(t_game *game);
int		validate_map_characters(t_game *game);
int		validate_map_neighbors(t_game *game);
int		validate_all_map(t_game *game);

/*--------------parsing.c---------------*/
void	parse_map(t_game *game, char *argv[]);


/*--------------draw_line.c---------------*/

void		draw_shallow_line(t_line_info line_info, t_game *game);
void		draw_steep_line(t_line_info line_info, t_game *game);
void		move_coordinate(int *coordinate, int direction);

/*-------------draw_minimap.c-------------*/

void		draw_minimap(t_game *game);
void		draw_minimap_block(int start[2], int counter[2], double x_offset,
				t_game *game);
void		draw_player_on_minimap(t_game *game);

/*--------------draw_scene.c--------------*/

void		draw_loop(void *param);
void		draw_3d_scene(t_game *game);
void		draw_vertical_line(t_game *game, int x, t_ray ray);
void		calculate_texture_coordinates(t_game *game, t_ray *ray,
				t_texture_info *texture_info);

/*-------------draw_sprites.c-------------*/

void		draw_sprites(t_game *game);
void		initialize_sprite(t_game *game, t_sprite *sprite);
void		calculate_sprite_dimensions(t_game *game, t_sprite *sprite);

/*----------draw_sprites_utils.c----------*/

void		draw_death_animation_and_respawn(t_game *game, t_sprite sprite);
void		respawn_sprite(t_game *game);
int			get_random_map_coordinate(int max);

/*----------------game.c------------------*/

void		start_game(t_game *game);
void		run_game_loop(t_game *game);
void		end_game(t_game *game);

/*----------------hooks.c-----------------*/

void		close_loop_hook(void *param);
void		move_player_loop_hook(void *param);

/*-------------load_params.c--------------*/

void		load_game_params(t_game *game);
void		load_map_and_screen_params(t_game *game);
void		load_player_params(t_game *game);

void		set_player_start_dir(t_game *game, char start_dir);

/*------------load_textures.c-------------*/

void		load_map_textures(t_game *game);
void		load_sprite_textures(t_game *game);

/*-----------player_movement.c------------*/

void		move_player_forward_backward(t_game *game, t_player *player,
				double move_speed, double collision_distance);
void		strafe_player_left_right(t_game *game, t_player *player,
				double move_speed, double collision_distance);
void		keyboard_rotate_player(t_game *game, t_player *player,
				double rot_speed);
void		mouse_rotate_player(t_game *game, t_player *player,
				double rot_speed);
void		rotate_direction_and_plane(t_player *player, double rot_speed,
				int direction);

/*------------player_action.c-------------*/

void		open_doors(t_game *game, double pos[2]);
void		kill_sprites(t_game *game, double pos[2]);

/*--------------raycasting.c--------------*/

void		cast_ray(t_game *game, int x_coordinate);
void		initialize_ray_and_player(t_game *game, t_ray *ray,
				int x_coordinate);
void		calculate_step_and_initial_side_distance(t_game *game,
				t_player *player, t_ray *ray);
void		perform_dda(t_map *map, t_ray *ray);
void		calculate_wall_distance_and_draw(t_game *game, t_ray *ray,
				int x_coordinate);

/*----------------utils.c-----------------*/

void		handle_mlx_error(t_game *game);
void		handle_error(char *message);

#endif