/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/10 22:41:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		//trimmed_line = strtrim(line);
		char	**map_lines;
		map_lines[i] = line;
		printf("Linha %d: %s\n", i, map_lines[i]);
		i++;
	}
	
}