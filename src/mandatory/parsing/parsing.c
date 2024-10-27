/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:04:19 by codespace         #+#    #+#             */
/*   Updated: 2024/10/27 21:29:07 by codespace        ###   ########.fr       */
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
		}
		free(line);
	}
	close(fd);
	if (!validate_all_textures(game))
		handle_error("Missing mandatory texture.");
	if (!validate_floor_ceiling(game))
		handle_error("Missing floor or ceiling color.");
	fake_load_map_params(game, argv[1]);
	load_player_params(game);
}
