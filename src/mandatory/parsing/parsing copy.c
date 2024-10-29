/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/29 00:00:48 by codespace        ###   ########.fr       */
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

// 

t_list	**ft_get_memory_list(void)
{
	static t_list	*head;

	return (&head);
}

void	ft_collect_memory(void *pointer)
{
	ft_lstadd_back(ft_get_memory_list(), ft_lstnew(pointer));
}

void	ft_free_all_memory(void)
{
	ft_get_next_line(-1);
	ft_lstclear(ft_get_memory_list(), &free);
}

void	*ft_safalloc(size_t nmemb, size_t size)
{
	void	*p;

	p = ft_calloc(nmemb, size);
	if (!p)
	{
		ft_free_all_memory();
		perror("Error\nMalloc failed\n");
		exit(EXIT_FAILURE);
	}
	ft_collect_memory(p);
	return (p);
}






void fake_load_map_params(t_game *game, char *argv)
{
    int row;
    int col;
    int len;
    int file;
    char *line;

    file = open(argv, O_RDONLY);
    if (file < 0)
    {
        handle_error("Error opening map file.");
        return ;
    }
    
    line = ft_get_next_line(file);
    len = ft_strlen(line);
    game->map.height = len - 1;
    game->map.width = len - 1;
    game->map.grid = ft_safalloc(sizeof(int *), len);
	if (!game->map.grid)
	{
    	handle_error("Failed to allocate memory for map grid.");
    	return;
	}
    row = 0;
    while (line)
	{
		if (row >= game->map.height) // Verifica se estamos dentro dos limites
		{
			handle_error("Exceeded map height during loading.");
			break;
		}
		
		game->map.grid[row] = ft_safalloc(sizeof(int), len);
		if (!game->map.grid[row]) // Verifica se a alocação foi bem-sucedida
		{
			handle_error("Failed to allocate memory for grid row.");
			break;
		}
		
		col = 0;
		while (col < len)
		{
			if (line[col] == 'N' || line[col] == 'S' || line[col] == 'W' || line[col] == 'E')
			{
				game->player.pos[X] = col;
				game->player.pos[Y] = row;
				game->player.start_dir = line[col];
				line[col] = '0';
			}
			game->map.grid[row][col] = line[col] - '0';
			col++;
		}

		// Libere a linha antes de ir para a próxima
		free(line);
		line = ft_get_next_line(file);
		
		printf("Row %d: ", row);
		col = 0;
		while (col < len)
		{
			printf("%d ", game->map.grid[row][col]);
			col++;
		}
		printf("\n"); // Nova linha após imprimir a linha do mapa
		row++;
	}

    close(file);
}


/**
 * @brief sets the player's direction and plane vectors based on the starting
 * direction (start_dir).
 * 
 * @param game struct containing game data
 */
void	load_player_params(t_game *game)
{
	if (game->player.start_dir == 'W')
	{
		game->player.dir[X] = -1;
		game->player.plane[Y] = -0.66;
	}
	else if (game->player.start_dir == 'E')
	{
		game->player.dir[X] = 1;
		game->player.plane[Y] = 0.66;
	}
	else if (game->player.start_dir == 'S')
	{
		game->player.dir[Y] = 1;
		game->player.plane[X] = -0.66;
	}
	else if (game->player.start_dir == 'N')
	{
		game->player.dir[Y] = -1;
		game->player.plane[X] = 0.66;
	}
}


////////////

#include <stdbool.h>
#include <string.h>

#define WALL 1 // Defina WALL como o valor que representa paredes no seu mapa

bool check_map_dimensions(t_game *game) {
    if (game->map.grid == NULL || game->map.height <= 0 || game->map.width <= 0) {
        return false; // Verifica se o mapa é nulo ou tem dimensões não válidas
    }

    for (int row = 0; row < game->map.height; row++) {
        // Verifica se a linha não é nula e se o comprimento corresponde à largura do mapa
        if (game->map.grid[row] == NULL || (sizeof(game->map.grid[row]) / sizeof(game->map.grid[row][0])) != game->map.width) {
            return false; // Retorna falso se a linha não for válida
        }
    }

    return true; // Todas as linhas têm o comprimento esperado
}

bool check_border_walls(t_game *game) {
    int row;
    int col;

    // Check top and bottom borders
    for (col = 0; col < game->map.width; col++) {
        if (game->map.grid[0][col] != WALL || game->map.grid[game->map.height - 1][col] != WALL)
            return false;
    }
    
    // Check left and right borders
    for (row = 0; row < game->map.height; row++) {
        if (game->map.grid[row][0] != WALL || game->map.grid[row][game->map.width - 1] != WALL)
            return false;
    }

    return true;
}

bool check_player_position(t_game *game) {
    if (game->player.start_dir == '\0') // Caso a direção inicial não tenha sido definida
        return false;

    // Verifique se a posição do jogador é válida e única
    int player_count = 0;
    for (int row = 0; row < game->map.height; row++) {
        for (int col = 0; col < game->map.width; col++) {
            if (game->map.grid[row][col] == game->player.start_dir)
                player_count++;
        }
    }
    return player_count == 1; // O jogador deve aparecer apenas uma vez
}

bool is_map_valid(t_game *game)
{
    if (!check_map_dimensions(game))
    {
        handle_error("Map dimensions are inconsistent.");
        return false;
    }
    
    if (!check_border_walls(game))
    {
        handle_error("Map borders are not valid.");
        return false;
    }
    
    if (!check_player_position(game))
    {
        handle_error("Invalid player position.");
        return false;
    }

    return true;
}

// Função para verificar se uma posição é válida e acessível
bool is_valid_pos(t_game *game, int x, int y) {
    return (x >= 0 && x < game->map.width && 
            y >= 0 && y < game->map.height && 
            game->map.grid[y][x] != WALL);
}