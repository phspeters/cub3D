/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/11 00:01:09 by codespace        ###   ########.fr       */
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
		if (ft_strle(line) > 0)
		{
			if (is_texture_line(line))
			{
				if (!validate_textures(game, line))
					handle_error("Invalid resolution values");
			}
		}
		free(line);
	}
	close(fd);
}