/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/14 19:09:17 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_get_size(unsigned long long n)
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

char	*to_hexa(unsigned long long base10)
{
	size_t	len;
	int		i;
	char	*base16;
	char	*conv;

	len = ft_get_size(base10);
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

char	*to_hexa_lowercase(unsigned long long base10)
{
	size_t	len;
	int		i;
	char	*base16;
	char	*conv;

	len = ft_get_size(base10);
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
