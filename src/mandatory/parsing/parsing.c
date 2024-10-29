/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 01:27:24 by codespace        ###   ########.fr       */
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




void parse_map(t_game *game, int argc, char *argv[])
{
	t_game gam;
    if (argc != 2)
    {
        printf("Usage: %s <map.cub>\n", argv[0]);
    }

    if (calculate_map_dimensions(&gam, argv[1]) == FAILURE)
    {
        printf("Erro ao calcular as dimensões do mapa.\n");
    }
    // Aloca o grid do mapa com as dimensões calculadas
    allocate_map_grid(&gam);

    // Inicializa a linha atual
    gam.map.current[0] = 0;

    // Abra o arquivo e processe linha por linha do mapa
    int fd = open(argv[1], O_RDONLY);
    char *line;
    if (fd < 0)
    {
        handle_error("Error opening map file.");
    }

    while ((line = ft_get_next_line(fd)) != NULL)
    {
        if (is_map_line(line))
        {
            process_map_line(&gam, line);
        }
        free(line);
    }
    close(fd);
    // Imprime o grid do mapa para validar
    print_map_grid(&gam);

}


