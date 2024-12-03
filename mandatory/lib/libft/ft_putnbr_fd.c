/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:35:11 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/12 17:05:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long nbr, int fd)
{
	int		counter;

	counter = 0;
	if (nbr < 0)
	{
		counter += ft_putchar_fd('-', fd);
		nbr = nbr * -1;
	}
	if (nbr > 9)
		counter += ft_putnbr_fd(nbr / 10, fd);
	counter += ft_putchar_fd(nbr % 10 + '0', fd);
	return (counter);
}
