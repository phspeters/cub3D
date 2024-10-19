/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/19 15:08:56 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	handle_error(char *message)
{
	if (errno)
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		perror(message);
		exit(errno);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error\n");
		ft_fprintf(STDERR_FILENO, "%s.\n", message);
		exit(EXIT_FAILURE);
	}
}

int	is_rgb_line(char *line)
{
	return (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0);
}

int	validate_rgb(char *line)
{
	int	r;
	int	g;
	int	b;

	r = -1;
	g = -1;
	b = -1;
	if (sscanf(line, "C %d,%d,%d", &r, &g, &b) != 3 && \
		sscanf(line, "F %d,%d,%d", &r, &g, &b) != 3)
		return (FAILURE);
	if ((r < 0 || r > 255) || (g < 0 || g >  255) || (b < 0 || b > 255))
		return (FAILURE);
	return (SUCCESS);
}

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}

int	is_texture_exists(char *texture_path)
{
	if (access(texture_path, F_OK) != -1)
	{
		printf("%s \n", texture_path);
		return (1);
	}
	else
		return (0);
}

int	validate_textures(t_game *game, char *line)
{
	char	*texture_path;
	int		valid;

	valid = 1;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		//game->map.texture_path[NORTH] = texture_path;
		printf("NO \n");
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		//game->map.texture_path[SOUTH] = texture_path;
		printf("SO \n");
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		//game->map.texture_path[WEST] = texture_path;
		printf("WE \n");
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		texture_path = ft_strdup(line + 3);
		//game->map.texture_path[EAST] = texture_path;
		printf("EA \n");
	}
	else
		return (0);
	if (!is_texture_exists(texture_path))
		valid = 0;
	free (texture_path);
	return (valid);
}

void	parse_map(t_game *game, int argc, char *argv[])
{
	char	*line;
	char	*trimmed_line;
	int		fd;
	int		i;

	(void)argc;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		handle_error("Error opening map file.");
		return ;
	}
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		//printf("Linha lida: %s", line);  // Imprime a linha lida
		if (ft_strlen(line) > 0)
		{
			if (is_texture_line(line))
			{
				if (!validate_textures(game, line))
					handle_error("Invalid texture path or type");
			}
/* 			else if (is_rgb_line(line))
			{
				if (!validate_rgb(line))
					handle_error("Invalid RGB values");
			} */
		}
		free(line);
	}
	close(fd);
}
