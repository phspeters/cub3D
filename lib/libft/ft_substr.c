/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:30:51 by pehenri2          #+#    #+#             */
/*   Updated: 2024/11/24 15:07:14 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	if (start > s_len)
		return (ft_calloc(1, 1));
	if (s_len - start >= len)
		substr = ft_safalloc((len + 1), sizeof(char));
	else
		substr = ft_safalloc((s_len - start + 1), sizeof(char));
	if (substr != NULL)
	{
		ft_strlcpy(substr, (&s[start]), (len + 1));
		return (substr);
	}
	return (NULL);
}
