/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:58:20 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:29:44 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	checking_values(char *str)
{
	int	x;
	int	counter;

	counter = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '+' || str[x] == '-')
			counter++;
		else if (str[x] < '0' || str[x] > '9' || counter > 1)
		{
			ft_putstr_fd(str, 2);
			write(2, ": numeric argument required\n", 28);
			return (0);
		}
		x++;
	}
	return (1);
}

int	while_atoi(char *str, int *s)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*s = *s * -1;
		i++;
	}
	return (i);
}

long long	ft_atoi_long_long(char *str)
{
	int							i;
	int							s;
	long long					res;

	i = 0;
	s = 1;
	res = 0;
	i = while_atoi(str, &s);
	if (ft_strlen(str + i) > 19)
		ft_atoi_error(str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (i >= 18)
		{
			if ((s == 1 && str[i] > '7') || (s == -1 && str[i] > '8'))
				ft_atoi_error(str);
		}
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * s);
}

void	ft_atoi_error(char *str)
{
	ft_putstr_fd(str, 2);
	write(2, ": numeric argument required\n", 28);
	g_exit_status = 255;
	exit(255);
}

int	if_splitedcommand2(char **splited_command, t_env **envs)
{
	if (checking_values(splited_command[1]) == 0)
	{
		g_exit_status = 255;
		write(2, "exit\n", 5);
		exit(255);
	}
	write(2, splited_command[2], ft_strlen(splited_command[2]));
	write(2, ": too many arguments\n", ft_strlen(": too many arguments\n"));
	g_exit_status = 1;
	write(2, "exit\n", 5);
	exit_func(g_exit_status, envs);
	return (1);
}
