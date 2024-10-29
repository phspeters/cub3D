/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 23:39:25 by codespace        ###   ########.fr       */
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

void allocate_map_grid(t_game *game)
{
    int i;

    // Aloca um array de ponteiros para as linhas
    game->map.grid = malloc(sizeof(int *) * game->map.height);
    if (!game->map.grid)
    {
        handle_error("Memory allocation failed for map grid.");
        return;
    }

    // Aloca um array de inteiros para cada linha do grid
    i = 0;
    while (i < game->map.height)
    {
        game->map.grid[i] = malloc(sizeof(int) * game->map.width);
        if (!game->map.grid[i])
        {
            handle_error("Memory allocation failed for map row.");
            return;
        }
        i++;
    }
}

void process_map_line(t_game *game, char *line)
{
    int j = 0;

    if (game->map.current[0] >= game->map.height)
    {
        handle_error("Map exceeds allocated height.");
        return;
    }

    // Itera sobre cada caractere da linha do mapa
    while (line[j] && j < game->map.width)
    {
        if (line[j] == '1')
            game->map.grid[game->map.current[0]][j] = 1; // Paredes
        else if (line[j] == '0')
            game->map.grid[game->map.current[0]][j] = 0; // Espaço vazio
        else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' || line[j] == 'W')
        {
            // Exibe o caractere do jogador detectado e sua posição
            printf("Jogador detectado: %c na posição (%d, %d)\n", line[j], game->map.current[0], j);
            game->player.pos[X] = game->map.current[0];
            game->player.pos[Y] = j;
            game->map.grid[game->map.current[0]][j] = 0; // Marca a posição do jogador como espaço vazio
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


int is_map_line_2(char *line)
{
    int i = 0;

    // Ignora espaços em branco no início da linha
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    // Verifica se a linha começa com caracteres válidos do mapa (1, 0, ou direções N, S, E, W)
    if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' ||
        line[i] == 'E' || line[i] == 'W')
        return 1;  // Retorna 1 se for uma linha de mapa
    return 0;      // Retorna 0 se não for uma linha de mapa
}

int is_map_line(char *line)
{
    int i = 0;

    // Ignora espaços em branco no início da linha
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    // Verifica se a linha começa com caracteres válidos do mapa (1, 0, ou direções N, S, E, W)
    if (line[i] == '1' || line[i] == '0')
        return 1;  // Retorna 1 se for uma linha de mapa
    return 0;      // Retorna 0 se não for uma linha de mapa
}

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>  // Para usar printf para depuração

int calculate_map_dimensions(t_game *game, char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    char *line;
    int width = 0;
    int height = 0;

    //game->map.height = 0;
    //game->map.width = 0;
    if (fd < 0)
    {
        handle_error("Failed to open map file.");
        return FAILURE;
    }
    while ((line = ft_get_next_line(fd)) != NULL)
    {
        // Verifica se a linha é uma linha de mapa
        if (is_map_line(line))
        {
            int current_width = 0;
            // Conta o número de caracteres válidos na linha
            while (line[current_width] && line[current_width] != '\n')
                current_width++;
            
            // Atualiza a largura máxima se necessário
            if (current_width > width)
                width = current_width;

            // Incrementa a altura do mapa para cada linha válida
            height++;
        }
        free(line);
    }
    close(fd);

    // Atribui as dimensões calculadas para o jogo
    game->map.width = width;
    game->map.height = height;

    // Depuração: imprime as dimensões calculadas
    printf("Dimensões calculadas - Largura: %d, Altura: %d\n", game->map.width, game->map.height);

    return SUCCESS;
}


void	print_map_grid(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	printf("Map grid:\n");
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			printf("%d ", game->map.grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("Player start position: (X: %d, Y: %d)\n", (int)game->player.pos[X],
		   (int)game->player.pos[Y]);
	printf("Player direction: (dir[X]: %f, dir[Y]: %f)\n",
		   game->player.dir[X], game->player.dir[Y]);
}

/// implemetation validate map

int validate_map_borders(t_game *game)
{
    int i;

    // Verificação de depuração para altura e largura
    printf("Map height: %d, Map width: %d\n", game->map.height, game->map.width);

    // Valida as bordas superior e inferior
    i = 0;
    while (i < game->map.width)
    {
        printf("Top border - grid[0][%d]: %d\n", i, game->map.grid[0][i]);
        printf("Bottom border - grid[%d][%d]: %d\n", game->map.height - 1, i,
               game->map.grid[game->map.height - 1][i]);

        if (game->map.grid[0][i] != 1 || game->map.grid[game->map.height - 1][i] != 1)
        {
            handle_error("Map is not closed (top or bottom row is open).");
            return FAILURE;
        }
        i++;
    }

    // Valida as bordas laterais
    i = 0;
    while (i < game->map.height)
    {
        printf("Left border - grid[%d][0]: %d\n", i, game->map.grid[i][0]);
        printf("Right border - grid[%d][%d]: %d\n", i, game->map.width - 1,
               game->map.grid[i][game->map.width - 1]);

        if (game->map.grid[i][0] != 1 || game->map.grid[i][game->map.width - 1] != 1)
        {
            handle_error("Map is not closed (left or right column is open).");
            return FAILURE;
        }
        i++;
    }

    return SUCCESS;
}


int validate_single_player(t_game *game)
{
    int i, j;
    int player_count = 0;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.grid[i][j] == 0 && 
                (game->player.pos[X] == i && game->player.pos[Y] == j))
            {
                player_count++;
            }
            j++;
        }
        i++;
    }

    if (player_count != 1)
    {
        handle_error("Map must have exactly one player.");
        return FAILURE;
    }
    return SUCCESS;
}

int validate_map_characters(t_game *game)
{
    int i, j;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.grid[i][j] != 1 && game->map.grid[i][j] != 0 &&
                !(i == game->player.pos[X] && j == game->player.pos[Y]))
            {
                handle_error("Invalid character in map.");
                return FAILURE;
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}

int validate_map_neighbors(t_game *game)
{
    int i, j;

    i = 1; // Começa na segunda linha para evitar acessar fora do limite
    while (i < game->map.height - 1)
    {
        j = 1; // Começa na segunda coluna para evitar acessar fora do limite
        while (j < game->map.width - 1)
        {
            if (game->map.grid[i][j] == 0)
            {
                if (game->map.grid[i - 1][j] == -1 || game->map.grid[i + 1][j] == -1 ||
                    game->map.grid[i][j - 1] == -1 || game->map.grid[i][j + 1] == -1)
                {
                    handle_error("Map has open spaces around interior walls.");
                    return FAILURE;
                }
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}

int validate_map(t_game *game)
{
    if (validate_map_borders(game) == FAILURE)
    {
        printf("Board ok\n");
        return FAILURE;
    }
    if (validate_single_player(game) == FAILURE)
        return FAILURE;
    if (validate_map_characters(game) == FAILURE)
        return FAILURE;
    if (validate_map_neighbors(game) == FAILURE)
        return FAILURE;

    return SUCCESS;
}


void parse_map(t_game *game, int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <map.cub>\n", argv[0]);
        return;
    }

    // Calcula as dimensões do mapa e atribui diretamente a game->map
    if (calculate_map_dimensions(game, argv[1]) == FAILURE)
    {
        printf("Erro ao calcular as dimensões do mapa.\n");
        return;
    }

    // Verifica se as dimensões foram armazenadas corretamente
    printf("Dimensões calculadas - Largura: %d, Altura: %d\n", game->map.width, game->map.height);

    // Aloca o grid do mapa com as dimensões calculadas
    allocate_map_grid(game);

    // Inicializa a linha atual do grid para o preenchimento
    game->map.current[0] = 0;

    // Abre o arquivo e processa cada linha do mapa
    int fd = open(argv[1], O_RDONLY);
    char *line;
    if (fd < 0)
    {
        handle_error("Error opening map file.");
        return;
    }

    while ((line = ft_get_next_line(fd)) != NULL)
    {
        if (is_map_line(line))
        {
            process_map_line(game, line);
        }
        free(line);
    }
    close(fd);

    // Valida as bordas e a estrutura do mapa
    if (validate_map(game) == FAILURE)
    {
        handle_error("Map validation failed.");
        return;
    }

    // Imprime o grid do mapa para depuração
    print_map_grid(game);
}


