/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:34:09 by pehenri2          #+#    #+#             */
/*   Updated: 2023/07/19 15:20:12 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		s_size;

	s_size = ft_strlen((char *)s) + 1;
	dup = malloc(sizeof(char) * s_size);
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, s_size);
	return (dup);
}
