/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 13:18:01 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf_error.h"

void	print_arguments_err(int *counter, va_list arg, const char *conversion, ...)
{
	int		i;
	va_list	copy;

	i = 0;
	va_copy(copy, arg);
	while (conversion[i] && (size_t)i < ft_strlen(conversion))
	{
		if (check_int_err(&counter, copy, &conversion[i], &i)
			|| check_str_or_char_err(&counter, copy, &conversion[i], &i)
			|| check_ptr_err(&counter, copy, &conversion[i], &i)
			|| check_hexa_err(&counter, copy, &conversion[i], &i))
		{
			va_arg(copy, int);
			continue ;
		}
		if (check_percent_err(&counter, &conversion[i], &i))
			continue ;
		if ((size_t)i < ft_strlen(conversion))
		{
			write(1, &conversion[i], 1);
			(*counter)++;
			i++;
		}
	}
}

int	ft_printf_error(const char *conversion, ...)
{
	va_list	arguments;
	int		counter;

	va_start(arguments, conversion);
	counter = 0;
	print_arguments_err(&counter, arguments, conversion);
	va_end(arguments);
	return (counter);
}
