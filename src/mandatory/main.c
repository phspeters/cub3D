/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1014/07/14 10:33:41 by pehenri1          #+#    #+#             */
/*   Updated: 2024/10/18 16:29:45 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_game	game;

	init_params(&game);
	load_params(&game);
	start_game(&game);
	run_game_loop(&game);
	end_game(&game);
	return (EXIT_SUCCESS);
}
