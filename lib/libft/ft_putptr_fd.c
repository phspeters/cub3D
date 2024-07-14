/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:51:46 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/12 17:05:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_pointer(unsigned long nbr, int fd)
{
	int		counter;
	char	*base;

	counter = 0;
	base = "0123456789abcdef";
	if (nbr >= 16)
	{
		counter += print_pointer(nbr / 16, fd);
		counter += ft_putchar_fd(base[nbr % 16], fd);
	}
	else
	{
		counter += ft_putchar_fd(base[nbr % 16], fd);
	}
	return (counter);
}

int	ft_putptr_fd(unsigned long nbr, int fd)
{
	int	counter;

	counter = 0;
	if (nbr == 0)
		counter += write(fd, "(nil)", 5);
	else
	{
		counter += write(fd, "0x", 2);
		counter += print_pointer(nbr, fd);
	}
	return (counter);
}
