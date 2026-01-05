/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 13:17:15 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_error.h"

void	ft_putchar_count_err(char c, int ***count)
{
	write(2, &c, 1);
	(***count)++;
}

void	ft_putnbr_count_err(int n, int ***count)
{
	char	c;
	long	nbr;

	nbr = n;
	if (n < 0)
	{
		write(2, "-", 1);
		(***count)++;
		nbr *= -1;
	}
	c = nbr % 10 + '0';
	if (nbr / 10)
	{
		ft_putnbr_count_err(nbr / 10, count);
	}
	write(2, &c, 1);
	(***count)++;
}

void	ft_putnbr_count_unsigned_err(unsigned int n, int ***count)
{
	char	c;
	long	nbr;

	nbr = n;
	c = nbr % 10 + '0';
	if (nbr / 10)
	{
		ft_putnbr_count_err(nbr / 10, count);
	}
	write(2, &c, 1);
	(***count)++;
}

void	ft_putstr_count_err(char *s, int ***count)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
		(***count)++;
	}
	write(2, s, i);
}
