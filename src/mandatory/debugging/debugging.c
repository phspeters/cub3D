/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:31:48 by roglopes          #+#    #+#             */
/*   Updated: 2024/10/20 14:56:28 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_texture_paths(t_game *game)
{
	const char	*texture_name[5] = {"NORTH", "SOUTH", "WEST", "EAST", "DOOR"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (game->map.texture_path[i] != NULL)
		{
			ft_printf("Texture for %s:  %s", texture_name[i], \
			game->map.texture_path[i]);
		}
		else
			ft_printf("Texture for %s not set. ", texture_name[i]);
		i++;
	}
}

void	print_rgb_values(t_game *game)
{
	if (game->map.ceiling == 0)
		ft_printf("Ceiling color not set. \n");
	else
		ft_printf("Ceiling color: %#010x\n", game->map.ceiling);
	if (game->map.floor == 0)
		ft_printf("Floor color not set. \n");
	else
		ft_printf("Floor color: %#010x\n", game->map.floor);
}
