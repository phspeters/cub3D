/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1014/07/14 10:33:41 by pehenri1          #+#    #+#             */
/*   Updated: 2024/11/11 15:22:23 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_game	game;

	if (argc != 2 && check_file(argv[1], true) == FAILURE)
	{
		handle_error("Usage: ./cub3D <map.cub> or check if file end with .cub");
		return (EXIT_FAILURE);
	}
	init_params(&game);
	//
	parse_map(&game, argv);
	print_texture_paths(&game);
	print_rgb_values(&game);
	print_map_grid(&game);
	//
	load_params(&game);
	start_game(&game);
	run_game_loop(&game);
	end_game(&game);
	return (EXIT_SUCCESS);
}
