/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:17:57 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/14 18:59:41 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include "../../libft.h"

char	*to_hexa_lowercase(unsigned long long base10);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);

int		check_int(int **counter, va_list copy, const char *conversion, int *i);
int		check_str_or_char(int **c, va_list copy, const char *conv, int *i);
int		check_ptr(int **counter, va_list copy, const char *conversion, int *i);
int		check_hexa(int **counter, va_list copy, const char *conversion, int *i);
int		check_percent(int **counter, const char *conversion, int *i);
int		ft_printf(const char *conversion, ...);

void	ft_putchar_count(char c, int ***count);
void	ft_putnbr_count(int n, int ***count);
void	ft_putnbr_count_unsigned(unsigned int n, int ***count);
void	ft_putstr_count(char *s, int ***count);
#endif
