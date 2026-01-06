/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:17:57 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/17 13:14:29 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include "../../libft.h"

char	*to_hexa_err(unsigned long long base10);
char	*to_hexa_lowercase_err(unsigned long long base10);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);

int		check_int_err(int **counter, va_list copy, const char *conversion, int *i);
int		check_str_or_char_err(int **c, va_list copy, const char *conv, int *i);
int		check_ptr_err(int **counter, va_list copy, const char *conversion, int *i);
int		check_hexa_err(int **counter, va_list copy, const char *conversion, int *i);
int		check_percent_err(int **counter, const char *conversion, int *i);
int		ft_printf_error(const char *conversion, ...);

void	ft_putchar_count_err(char c, int ***count);
void	ft_putnbr_count_err(int n, int ***count);
void	ft_putnbr_count_unsigned_err(unsigned int n, int ***count);
void	ft_putstr_count_err(char *s, int ***count);
#endif
