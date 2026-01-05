/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:18:08 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 13:18:52 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_error.h"

int	check_int_err(int **counter, va_list copy, const char *conversion, int *i)
{
	va_list	new_copy;

	va_copy(new_copy, copy);
	if (ft_strnstr(conversion, "%d", 2)
		|| ft_strnstr(conversion, "%i", 2))
	{
		ft_putnbr_count_err(va_arg(new_copy, int), &counter);
		return (*i += 2);
	}
	if (ft_strnstr(conversion, "%u", 2))
	{
		ft_putnbr_count_unsigned_err(va_arg(new_copy, unsigned int), &counter);
		return (*i += 2);
	}
	return (0);
}

int	check_str_or_char_err(int **c, va_list copy, const char *conv, int *i)
{
	va_list	new_copy;
	char	*str;

	va_copy(new_copy, copy);
	if (ft_strnstr(conv, "%s", 2))
	{
		str = va_arg(new_copy, char *);
		if (!str)
			ft_putstr_count_err("(null)", &c);
		else
			ft_putstr_count_err(str, &c);
		return (*i += 2);
	}
	if (ft_strnstr(conv, "%c", 2))
	{
		ft_putchar_count_err(va_arg(new_copy, int), &c);
		return (*i += 2);
	}
	return (0);
}

int	check_ptr_err(int **counter, va_list copy, const char *conversion, int *i)
{
	va_list				new_copy;
	void				*ptr;
	unsigned long long	addr;
	char				*hexa_tout_court;

	va_copy(new_copy, copy);
	if (ft_strnstr(conversion, "%p", 2))
	{
		ptr = va_arg(new_copy, void *);
		if (ptr == 0)
		{
			ft_putstr_count_err("(nil)", &counter);
			return (*i += 2);
		}
		addr = (unsigned long long)ptr;
		hexa_tout_court = to_hexa_lowercase_err(addr);
		ft_putstr_count_err("0x", &counter);
		ft_putstr_count_err(hexa_tout_court, &counter);
		free(hexa_tout_court);
		return (*i += 2);
	}
	return (0);
}

int	check_hexa_err(int **counter, va_list copy, const char *conversion, int *i)
{
	va_list	new_copy;
	char	*hexa_lower;
	char	*hexa_tout_court;

	va_copy(new_copy, copy);
	if (ft_strnstr(conversion, "%x", 2))
	{
		hexa_lower = to_hexa_lowercase_err(va_arg(new_copy, long long));
		ft_putstr_count_err(hexa_lower, &counter);
		free(hexa_lower);
		return (*i += 2);
	}
	if (ft_strnstr(conversion, "%X", 2))
	{
		hexa_tout_court = to_hexa_err(va_arg(new_copy, long long));
		ft_putstr_count_err(hexa_tout_court, &counter);
		free(hexa_tout_court);
		return (*i += 2);
	}
	return (0);
}

int	check_percent_err(int **counter, const char *conversion, int *i)
{
	if (ft_strnstr(conversion, "%%", 2))
	{
		ft_putchar_count_err('%', &counter);
		return (*i += 2);
	}
	return (0);
}
