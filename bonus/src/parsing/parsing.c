/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/11/28 17:08:02 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Parse the cub file and fill the game struct with the information for
 * the game to run. Reads and validates the map information, wall textures and 
 * floor and ceiling colors.
 * 
 * @param game struct with the game information
 * @param argv array with the arguments passed to the program
 */
void	parse_cub_file(t_game *game, char *argv[])
{
	int		fd;
	char	*line;

	get_map_dimensions(game, argv[1]);
	allocate_map_grid(game);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_error(game, "Error opening map file");
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		if (!is_valid_line(line))
			handle_error(game, ft_strjoin("Invalid line in map file: ",
					ft_strtrim(line, "\n\r\f\v")));
		parse_textures(game, line);
		parse_rgb(game, line);
		parse_map_line(game, line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	validate_textures(game);
	validate_rgb(game);
	validate_map(game);
	validate_player(game);
}

void	parse_textures(t_game *game, char *line)
{
	if (!is_texture_line(line))
		return ;
	line = ft_strtrim(line, " \t\n\f\r\v");
	if (ft_strncmp(line, "NO", 2) == 0)
		set_texture_path(game, &game->map.texture_path[NORTH], line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		set_texture_path(game, &game->map.texture_path[SOUTH], line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		set_texture_path(game, &game->map.texture_path[WEST], line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		set_texture_path(game, &game->map.texture_path[EAST], line);
}

void	parse_rgb(t_game *game, char *line)
{
	int			r;
	int			g;
	int			b;
	uint32_t	color;

	if (!is_rgb_line(line))
		return ;
	line = ft_strtrim(line, " \t\n\f\r\v");
	validate_rgb_line(game, line + 1);
	r = validate_rgb_value(game, line + 1);
	g = validate_rgb_value(game, ft_strchr(line, ',') + 1);
	b = validate_rgb_value(game, ft_strrchr(line, ',') + 1);
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	if (line[0] == 'C')
		game->map.ceiling = color;
	else
		game->map.floor = color;
}

void	parse_map_line(t_game *game, char *line)
{
	static int	i;
	int			j;

	if (!is_map_line(line))
		return ;
	j = 0;
	line = ft_strtrim(line, "\n");
	while (line[j] && j < game->map.width)
	{
		parse_map_char(game, line[j], i, j);
		j++;
	}
	while (j < game->map.width)
	{
		game->map.grid[i][j] = VOID;
		j++;
	}
	i++;
}

void	parse_map_char(t_game *game, char c, int i, int j)
{
	if (c == '1')
		game->map.grid[i][j] = WALL;
	else if (c == '0')
		game->map.grid[i][j] = EMPTY;
	else if (c == '2')
		game->map.grid[i][j] = CLOSED_DOOR;
	else if (c == ' ')
		game->map.grid[i][j] = VOID;
	else if (ft_strchr("NSEW", c))
	{
		game->player.pos[Y] = i + 0.5;
		game->player.pos[X] = j + 0.5;
		game->player.start_dir = c;
		game->map.grid[i][j] = EMPTY;
		game->player.player_count++;
	}
	else
		handle_error(game, "Invalid character in map");
}
