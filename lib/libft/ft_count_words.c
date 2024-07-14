/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:33:36 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/12 12:33:48 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *string, const char delimiter)
{
	int	word_count;

	if (*string == '\0' || string == NULL)
		return (0);
	word_count = 0;
	while (*string != '\0')
	{
		if (*string != delimiter)
		{
			word_count++;
			while ((*string != delimiter) && (*string != '\0'))
				string++;
		}
		else
			string++;
	}
	return (word_count);
}
