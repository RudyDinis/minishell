/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 13:18:19 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_error.h"

size_t	ft_get_size_err(unsigned long long n)
{
	size_t	size;

	size = 1;
	while (n / 16)
	{
		n /= 16;
		size++;
	}
	return (size);
}

char	*to_hexa_err(unsigned long long base10)
{
	size_t	len;
	int		i;
	char	*base16;
	char	*conv;

	len = ft_get_size_err(base10);
	i = len - 1;
	base16 = "0123456789ABCDEF";
	conv = malloc(len + 1);
	if (!conv)
	{
		free(conv);
		return (NULL);
	}
	conv[len] = 0;
	while (i >= 0)
	{
		conv[i] = base16[base10 % 16];
		base10 /= 16;
		i--;
	}
	return (conv);
}

char	*to_hexa_lowercase_err(unsigned long long base10)
{
	size_t	len;
	int		i;
	char	*base16;
	char	*conv;

	len = ft_get_size_err(base10);
	i = len - 1;
	base16 = "0123456789abcdef";
	conv = malloc(len + 1);
	if (!conv)
	{
		free(conv);
		return (NULL);
	}
	conv[len] = 0;
	while (i >= 0)
	{
		conv[i] = base16[base10 % 16];
		base10 /= 16;
		i--;
	}
	return (conv);
}
