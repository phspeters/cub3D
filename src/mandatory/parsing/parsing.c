/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/26 20:18:24 by codespace        ###   ########.fr       */
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

// Função que valida a estrutura do mapa
int validate_map(t_game *game)
{
	int	i;
	int	j;
	int	player_count; // Inicializando variáveis

	i = 0;
	j = 0;
	player_count = 0;
	// Verifica se as bordas do mapa são paredes
	while (i < game->map.height)
	{
		if (game->map.grid[i][0] != 1 || game->map.grid[i][game->map.width - 1] != 1)
			return (0); // Mapa inválido
		i++;
	}
	// Verifica as primeiras e últimas linhas
	i = 0; // Reinicia i
	while (i < game->map.width)
	{
		if (game->map.grid[0][i] != 1 || game->map.grid[game->map.height - 1][i] != 1)
			return (0); // Mapa inválido
		i++;
	}
	// Verifica a presença do jogador e caracteres inválidos
	i = 0; // Reinicia i
	while (i < game->map.height)
	{
		j = 0; // Reinicia j
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' ||
				game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1) // Verifica se existe exatamente um jogador
		return (0); // Mapa inválido

	return (1); // Mapa válido
}

void	set_player_start_dir(t_game *game, int start_dir)
{
	if (start_dir == 'W')
	{
		game->player.dir[X] = -1;
		game->player.dir[Y] = 0;
		game->player.plane[X] = 0;
		game->player.plane[Y] = -0.66;
	}
	else if (start_dir == 'E')
	{
		game->player.dir[X] = 1;
		game->player.dir[Y] = 0;
		game->player.plane[X] = 0;
		game->player.plane[Y] = 0.66;
	}
	else if (start_dir == 'S')
	{
		game->player.dir[Y] = 1;
		game->player.dir[Y] = 0;
		game->player.plane[X] = 0;
		game->player.plane[X] = -0.66;
	}
	else if (start_dir == 'N')
	{
		game->player.dir[Y] = -1;
		game->player.dir[Y] = 0;
		game->player.plane[X] = 0;
		game->player.plane[X] = 0.66;
	}
}

void process_map_line(t_game *game, char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		printf("Line: %c\n", line[j]);
		// Valida o caractere atual
		if (line[j] == '1')
			game->map.grid[game->map.current[0]][j] = 1; // Paredes
		else if (line[j] == '0')
			game->map.grid[game->map.current[0]][j] = 0; // Espaço vazio
		else if (line[j] == 'N' || line[j] == 'S' ||
				line[j] == 'E' || line[j] == 'W')
		{
			// Posição inicial do jogador
			game->player.pos[X] = game->map.current[0];
			game->player.pos[Y] = j;
			game->map.grid[game->map.current[0]][j] = 0; // Espaço vazio onde o jogador está
			set_player_start_dir(game, line[j]);
		}
		else
		{
			handle_error("Invalid character in map.");
			return ; // Não continua se há caracteres inválidos
		}
		j++;
	}
	game->map.current[0]++; // Incrementa a linha atual
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
				if (!validate_rgb(game, line))
					handle_error("Invalid RGB values.");
			}
			else
				process_map_line(game, line);
		}
		free(line);
	}
	close(fd);
	if (!validate_all_textures(game))
		handle_error("Missing mandatory texture.");
	if (!validate_floor_ceiling(game))
		handle_error("Missing floor or ceiling color.");
	if (!validate_map(game))
		handle_error("Map validation failed");
}
