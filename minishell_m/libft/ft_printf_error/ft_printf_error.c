/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2026/01/24 19:57:09 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf_error.h"

void	print_arguments_err(int *counter, va_list arg, const char *c, ...)
{
	int		i;
	va_list	copy;

	i = 0;
	va_copy(copy, arg);
	while (c[i] && (size_t)i < ft_strlen(c))
	{
		if (check_int_err(&counter, copy, &c[i], &i)
			|| check_str_or_char_err(&counter, copy, &c[i], &i)
			|| check_ptr_err(&counter, copy, &c[i], &i)
			|| check_hexa_err(&counter, copy, &c[i], &i))
		{
			va_arg(copy, int);
			continue ;
		}
		if (check_percent_err(&counter, &c[i], &i))
			continue ;
		if ((size_t)i < ft_strlen(c))
		{
			write(2, &c[i], 1);
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
