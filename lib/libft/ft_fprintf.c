/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:48:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 11:00:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_format(const int fd, const char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (specifier == '%')
		return (ft_putchar_fd('%', fd));
	else if (specifier == 'p')
		return (ft_putptr_fd(va_arg(args, long), fd));
	else if (specifier == 'u')
		return (ft_putnbr_fd((va_arg(args, unsigned int)), fd));
	else if (specifier == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789abcdef", fd));
	else if (specifier == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", fd));
	else
		return (0);
}

int	ft_fprintf(const int fd, const char *str, ...)
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
			counter += print_format(fd, *(++str), args);
		else
			counter += ft_putchar_fd(*str, fd);
		str++;
	}
	va_end(args);
	return (counter);
}
