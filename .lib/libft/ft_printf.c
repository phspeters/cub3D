/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:48:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/12 17:04:51 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_format(const char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (specifier == '%')
		return (ft_putchar_fd('%', 1));
	else if (specifier == 'p')
		return (ft_putptr_fd(va_arg(args, long), 1));
	else if (specifier == 'u')
		return (ft_putnbr_fd((va_arg(args, unsigned int)), 1));
	else if (specifier == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789abcdef", 1));
	else if (specifier == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", 1));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		counter;

	if (str == NULL)
		return (-1);
	va_start(args, str);
	counter = 0;
	while (*str)
	{
		if (*str == '%')
			counter += print_format(*(++str), args);
		else
			counter += ft_putchar_fd(*str, 1);
		str++;
	}
	va_end(args);
	return (counter);
}
