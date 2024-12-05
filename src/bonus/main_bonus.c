/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1014/07/14 10:33:41 by pehenri1          #+#    #+#             */
/*   Updated: 2024/12/05 19:16:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init_params(&game);
	validate_arguments(&game, argc, argv);
	parse_cub_file(&game, argv);
	load_params(&game);
	start_game(&game);
	run_game_loop(&game);
	end_game(&game);
	return (EXIT_SUCCESS);
}
