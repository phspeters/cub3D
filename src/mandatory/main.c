/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1014/07/14 10:33:41 by pehenri1          #+#    #+#             */
/*   Updated: 2024/10/29 22:07:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_texture_params(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 5)
		game->map.texture_path[i] = NULL;
	game->map.ceiling = 0;
	game->map.floor = 0;
	//game->map.current[0] = 0;
}


int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2 && check_file(argv[1], true) == FAILURE)
	{
		handle_error("Usage: ./cub3D <map.cub> or check if file end with .cub");
		return (EXIT_FAILURE);
	}
	init_texture_params(&game);
	parse_map(&game, argc, argv);
	print_texture_paths(&game);
	print_rgb_values(&game);

	//load_game_params(&game);
	//start_game(&game);
	//run_game_loop(&game);
	//end_game(&game);
	return (EXIT_SUCCESS);
}
