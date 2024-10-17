/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:07:02 by pehenri2          #+#    #+#             */
/*   Updated: 2024/10/17 16:17:15 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdio.h>

t_list	**ft_get_memory_list(void)
{
	static t_list	*head;

	return (&head);
}

void	ft_collect_memory(void *pointer)
{
	ft_lstadd_back(ft_get_memory_list(), ft_lstnew(pointer));
}

void	ft_free_all_memory(void)
{
	ft_get_next_line(-1);
	ft_lstclear(ft_get_memory_list(), &free);
}

void	*ft_safalloc(size_t nmemb, size_t size)
{
	void	*p;

	p = ft_calloc(nmemb, size);
	if (!p)
	{
		ft_free_all_memory();
		perror("Error\nMalloc failed\n");
		exit(EXIT_FAILURE);
	}
	ft_collect_memory(p);
	return (p);
}
