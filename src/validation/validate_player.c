/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:18:43 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/23 19:18:52 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_player(t_game *game)
{
	if (game->player.player_count != 1)
	{
		if (game->player.player_count == 0)
			handle_error(game, "No player detected on the map");
		else
			handle_error(game, "Multiple players detected on the map");
	}
}
