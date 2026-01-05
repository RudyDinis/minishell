/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/09 11:55:11 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	print_arguments(int *counter, va_list arg, const char *conversion, ...)
{
	int		i;
	va_list	copy;

	i = 0;
	va_copy(copy, arg);
	while (conversion[i] && (size_t)i < ft_strlen(conversion))
	{
		if (check_int(&counter, copy, &conversion[i], &i)
			|| check_str_or_char(&counter, copy, &conversion[i], &i)
			|| check_ptr(&counter, copy, &conversion[i], &i)
			|| check_hexa(&counter, copy, &conversion[i], &i))
		{
			va_arg(copy, int);
			continue ;
		}
		if (check_percent(&counter, &conversion[i], &i))
			continue ;
		if ((size_t)i < ft_strlen(conversion))
		{
			write(1, &conversion[i], 1);
			(*counter)++;
			i++;
		}
	}
}

int	ft_printf(const char *conversion, ...)
{
	va_list	arguments;
	int		counter;

	va_start(arguments, conversion);
	counter = 0;
	print_arguments(&counter, arguments, conversion);
	va_end(arguments);
	return (counter);
}
