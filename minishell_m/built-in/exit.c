/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:27:10 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/23 16:15:04 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

long	ft_atol(char *str, t_cmd *cmd)
{
	int		i;
	long	result;
	int		is_negative;

	i = 0;
	result = 0;
	is_negative = 1;
	if (!str[i])
		return (-1);
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '-')
		is_negative = -1;
	i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (ft_printf_error("exit: %s: numeric argument required\n", str), 2147483648);
		i++;
	}
	return (result * is_negative);
}

int	check_valid_num(char *str)
{
	int i;
	int sign;

	sign = 0;
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			sign++;
			i++;
		}
		if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	if (sign > 1)
		return (0);
	return (1);
}

void	exit_shell(t_cmd *cmd, char **argv)
{
	long	exit;

	printf("exit\n");
	if (!argv[1])
		exit = 0;
	else
	{
		if (!check_valid_num(argv[1]))
			return (ft_printf_error("exit: %s: numeric argument required\n",
					argv[1]), free_ms(cmd->token, NULL, 0), (void)1);
		if (argv[2])
			return (ft_printf_error("exit: too many arguments\n"), (void)1);
		if (ft_atol(argv[1], cmd) == 2147483648)
			return (free_ms(cmd->token, NULL, 0), (void)1);
		exit = ft_atol(argv[1], cmd) % 256;
	}
	free_ms(cmd->token, NULL, exit);
}
