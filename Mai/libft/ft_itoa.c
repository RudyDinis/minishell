/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:13:28 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:16:03 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_int_length(int n)
{
	size_t	size;

	size = 1;
	while (n / 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int	is_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char		*number;
	int			i;
	long long	num;

	num = n;
	i = ft_int_length(num) - 1;
	number = malloc(ft_int_length(num) + 1 + is_negative(num));
	if (!number)
		return (NULL);
	if (is_negative(num) == 1)
	{
		number[0] = '-';
		num *= -1;
		i++;
	}
	number[ft_int_length(num) + is_negative(n)] = '\0';
	while (i >= is_negative(n))
	{
		number[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	return (number);
}
