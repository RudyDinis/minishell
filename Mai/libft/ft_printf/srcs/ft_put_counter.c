/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/09 12:04:35 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar_count(char c, int ***count)
{
	write(1, &c, 1);
	(***count)++;
}

void	ft_putnbr_count(int n, int ***count)
{
	char	c;
	long	nbr;

	nbr = n;
	if (n < 0)
	{
		write(1, "-", 1);
		(***count)++;
		nbr *= -1;
	}
	c = nbr % 10 + '0';
	if (nbr / 10)
	{
		ft_putnbr_count(nbr / 10, count);
	}
	write(1, &c, 1);
	(***count)++;
}

void	ft_putnbr_count_unsigned(unsigned int n, int ***count)
{
	char	c;
	long	nbr;

	nbr = n;
	c = nbr % 10 + '0';
	if (nbr / 10)
	{
		ft_putnbr_count(nbr / 10, count);
	}
	write(1, &c, 1);
	(***count)++;
}

void	ft_putstr_count(char *s, int ***count)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
		(***count)++;
	}
	write(1, s, i);
}
