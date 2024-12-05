/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/19 20:13:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_ptr_array(void **ptr_array, size_t size)
{
	size_t	i;

	if (ptr_array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		free(ptr_array[i++]);
	free(ptr_array);
	return (NULL);
}
