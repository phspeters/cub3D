/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/19 18:02:38 by roglopes         ###   ########.fr       */
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
		return (0);
	if ((r < 0 || r > 255) || (g < 0 || g >  255) || (b < 0 || b > 255))
		return (0);
	return (1);
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
		//printf("Linha lida: %s", line); // Imprime a linha lida
		if (ft_strlen(line) > 0)
		{
			if (is_texture_line(line))
			{
				if (!validate_textures(game, line))
					handle_error("Invalid texture path or type.");
			}
			else if (is_rgb_line(line))
			{
				if (!validate_rgb(line))
					handle_error("Invalid RGB values.");
			}
		}
		free(line);
	}
	close(fd);
	if (!validate_all_textures(game))
		handle_error("Missing mandatory texture.");
}
