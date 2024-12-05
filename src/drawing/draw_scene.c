/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:17:01 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/24 18:43:38 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief handles the rendering of the game scene by deleting the old image,
 * creating a new image, attaching it to the window, and then drawing the 3D
 * scene, minimap, player on the minimap, and sprites. All in a loop.
 * 
 * @param param pointer to the game struct holding all game information
 */
void	draw_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_delete_image(game->window, game->image);
	game->image = mlx_new_image(game->window, game->screen_size[X],
			game->screen_size[Y]);
	if (!game->image)
		handle_mlx_error(game, "mlx_new_image");
	if (mlx_image_to_window(game->window, game->image, 0, 0) == -1)
		handle_mlx_error(game, "mlx_image_to_window");
	draw_3d_scene(game);
	draw_minimap(game);
	draw_player_on_minimap(game);
	draw_sprites(game);
}

/**
 * @brief iterates through each horizontal pixel column of the screen,
 * casting a ray for each column to determine what is visible from the
 * player's perspective and rendering the 3D view accordingly.
 * 
 * @param game struct with game information
 */
void	draw_3d_scene(t_game *game)
{
	int	x_coordinate;

	x_coordinate = 0;
	while (x_coordinate <= game->screen_size[X])
	{
		cast_ray(game, x_coordinate);
		x_coordinate++;
	}
}

/**
 * @brief called at the end of the cast_ray function. Draws a vertical slice of
 * the 3D scene on the x coordinate of the screen according to the ray
 * information provided. Starts drawing the line from the top of the screen to
 * the start of the wall, then draws the wall texture and finally draws the
 * floor from the end of the wall to the bottom of the screen.
 * 
 * @param game struct with game information
 * @param x x coordinate of the screen
 * @param ray information about the ray casted on the x coordinate
 */
void	draw_vertical_line(t_game *game, int x, t_ray ray)
{
	int				y;
	t_texture_info	texture_info;

	y = -1;
	while (++y < ray.wall_line_start)
		put_valid_pixel(game, x, y, game->map.ceiling);
	calculate_texture_coordinates(game, &ray, &texture_info);
	game->player.wall_distance_on_camera_x[x] = ray.perpendicular_wall_distance;
	while (++y < ray.wall_line_end)
	{
		texture_info.texture_coord[Y] = (int)texture_info.texture_pos & \
		(ray.wall_texture->height - 1);
		texture_info.texture_pos += texture_info.step;
		put_valid_pixel(game, x, y, get_texel_color(ray.wall_texture,
				texture_info.texture_coord[X], texture_info.texture_coord[Y]));
	}
	while (++y < game->screen_size[Y])
		put_valid_pixel(game, x, y, game->map.floor);
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
		wall_x = game->player.pos[Y] + ray->perpendicular_wall_distance
			* ray->ray_dir[Y];
	else
		wall_x = game->player.pos[X] + ray->perpendicular_wall_distance
			* ray->ray_dir[X];
	wall_x -= floor(wall_x);
	texture_info->texture_coord[X] = (int)(wall_x
			* (double)(ray->wall_texture->width));
	if (ray->side_hit == WEST_EAST && ray->ray_dir[X] > 0)
		texture_info->texture_coord[X] = ray->wall_texture->width
			- texture_info->texture_coord[X] - 1;
	if (ray->side_hit == NORTH_SOUTH && ray->ray_dir[Y] < 0)
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
