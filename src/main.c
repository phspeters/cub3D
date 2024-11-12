/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1014/07/14 10:33:41 by pehenri1          #+#    #+#             */
/*   Updated: 2024/11/12 16:15:33 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 && check_file(argv[1], true) == FAILURE)
		handle_error(&game,
			"Usage: ./cub3D <map.cub> or check if file end with .cub");
	init_params(&game);
	parse_map(&game, argv);
	load_params(&game);
	start_game(&game);
	run_game_loop(&game);
	end_game(&game);
	return (EXIT_SUCCESS);
}
