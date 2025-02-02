/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:39:56 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/22 12:25:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base_and_get_length(char *base)
{
	int	base_len;
	int	i;

	base_len = 0;
	while (base[base_len] != '\0')
	{
		if (ft_issign(base[base_len]))
			return (0);
		i = base_len + 1;
		while (base[i] != '\0')
		{
			if (base[base_len] == base[i])
				return (0);
			i++;
		}
		base_len++;
	}
	if (base_len < 2)
		return (0);
	return (base_len);
}

static int	is_number_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static int	get_decimal_value(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	start;
	int	i;
	int	result;
	int	sign;
	int	base_length;

	sign = 1;
	base_length = check_base_and_get_length(base);
	if (base_length == 0)
		return (0);
	start = 0;
	while (str[start] != '\0' && ft_isspace(str[start]))
		start++;
	sign = get_sign(str[start]);
	i = start;
	result = 0;
	while (str[i] && is_number_in_base(str[i], base))
	{
		result = (result * base_length) + (get_decimal_value(str[i], base));
		i++;
	}
	return (result * sign);
}
