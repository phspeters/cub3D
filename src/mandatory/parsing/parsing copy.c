/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/27 19:37:19 by codespace        ###   ########.fr       */
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

int validate_map(t_game *game)
{
    int i;
    int j;
    int player_count = 0; // Inicializando variável para contar jogadores

    i = 0;

    // Verifica se as bordas superiores e inferiores do mapa estão fechadas com paredes
    while (i < game->map.width)
    {
        if (game->map.grid[0][i] != 1 || game->map.grid[game->map.height - 1][i] != 1)
        {
            handle_error("Map is not closed (top or bottom row is open).");
            return FAILURE;  // Usando o enum FAILURE
        }
        i++;
    }

    // Verifica se as laterais do mapa estão fechadas
    i = 0;
    while (i < game->map.height)
    {
        if (game->map.grid[i][0] != 1 || game->map.grid[i][game->map.width - 1] != 1)
        {
            handle_error("Map is not closed (left or right column is open).");
            return FAILURE;  // Usando o enum FAILURE
        }

        // Verifica a presença do jogador e caracteres inválidos
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' ||
                game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
            {
                player_count++;
                game->player.pos[X] = i;  // Usando o enum e_axis para X e Y
                game->player.pos[Y] = j;
            }
            else if (game->map.grid[i][j] != 1 && game->map.grid[i][j] != 0)
            {
                handle_error("Invalid character in map.");
                return FAILURE;  // Usando o enum FAILURE
            }
            j++;
        }
        i++;
    }

    // Verifica se existe exatamente um jogador no mapa
    if (player_count != 1)
    {
        handle_error("Map must have exactly one player.");
        return FAILURE;  // Usando o enum FAILURE
    }

    return SUCCESS; // Retorna SUCCESS do enum
}


void allocate_map_grid(t_game *game)
{
    int i;

    game->map.grid = malloc(sizeof(int *) * game->map.height); // Aloca as linhas (ponteiros)
    if (!game->map.grid)
        handle_error("Memory allocation failed for map grid.");
    
    i = 0;
    while (i < game->map.height)
    {
        game->map.grid[i] = malloc(sizeof(int) * game->map.width); // Aloca colunas para cada linha
        if (!game->map.grid[i])
            handle_error("Memory allocation failed for map row.");
        i++;
    }
}

void set_player_start_dir(t_game *game, char start_dir)
{
    if (start_dir == 'N')
    {
        game->player.dir[X] = -1;
        game->player.dir[Y] = 0;
        game->player.plane[X] = 0;
        game->player.plane[Y] = 0.66;
    }
    else if (start_dir == 'S')
    {
        game->player.dir[X] = 1;
        game->player.dir[Y] = 0;
        game->player.plane[X] = 0;
        game->player.plane[Y] = -0.66;
    }
    else if (start_dir == 'E')
    {
        game->player.dir[X] = 0;
        game->player.dir[Y] = 1;
        game->player.plane[X] = 0.66;
        game->player.plane[Y] = 0;
    }
    else if (start_dir == 'W')
    {
        game->player.dir[X] = 0;
        game->player.dir[Y] = -1;
        game->player.plane[X] = -0.66;
        game->player.plane[Y] = 0;
    }
}

void process_map_line(t_game *game, char *line)
{
    int j = 0;

    if (game->map.grid == NULL)
        handle_error("Map grid is not allocated.");

    while (line[j] && j < game->map.width)
    {
        if (line[j] == '1')
            game->map.grid[game->map.current[0]][j] = 1; // Paredes
        else if (line[j] == '0')
            game->map.grid[game->map.current[0]][j] = 0; // Espaço vazio
        else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' || line[j] == 'W')
        {
            game->player.pos[X] = game->map.current[0];
            game->player.pos[Y] = j;
            game->map.grid[game->map.current[0]][j] = 0; // Espaço vazio onde o jogador está
            set_player_start_dir(game, line[j]);
        }
        else
        {
            handle_error("Invalid character in map.");
            return;
        }
        j++;
    }

    game->map.current[0]++; // Incrementa a linha atual do mapa
}


int is_map_line(char *line)
{
    int i = 0;

    // Ignora espaços em branco no início da linha
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    // Verifica se a linha começa com um caractere válido do mapa
    if (line[i] == '1' || line[i] == '0')
        return 1;  // É uma linha de mapa
    return 0;      // Não é uma linha de mapa
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
	allocate_map_grid(game);
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
			else if (is_map_line(line))
			{
				process_map_line(game, line);
				printf("Alocando mapa de tamanho %d x %d\n", game->map.height, game->map.width);
			}
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

void free_map_grid(t_game *game)
{
    int i;

    i = 0;
    while (i < game->map.height)
    {
        free(game->map.grid[i]);  // Libera cada linha
        i++;
    }
    free(game->map.grid);  // Libera o array de ponteiros para as linhas
}
