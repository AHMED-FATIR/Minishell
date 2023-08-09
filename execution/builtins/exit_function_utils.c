/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:11:49 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 08:54:35 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_exit_exit(t_env **envs, char **splited_command)
{
	(void)envs;
	ft_putstr_fd(splited_command[1], 2);
	write(2, ": numeric argument required\n", 28);
	g_exit_status = 255;
	write(2, "exit\n", 5);
	exit(255);
}

void	exit_print(int status)
{
	g_exit_status = status;
	write(2, "exit\n", 5);
	exit(status);
}

long long	exit_function(t_env **envs, char **splited_command)
{
	long long	status;

	status = 0;
	if (!splited_command[1])
		exit_print(status);
	if (splited_command[2])
		return (if_splitedcommand2(splited_command, envs));
	if (!ft_strcmp("exit", splited_command[1]))
		if_exit_exit(envs, splited_command);
	if (checking_values(splited_command[1]) == 0)
	{
		g_exit_status = 255;
		write(2, "exit\n", 5);
		exit(255);
	}
	status = ft_atoi_long_long(splited_command[1]);
	write(2, "exit\n", 5);
	return (exit_function_util1(status));
}

long long	exit_function_util1(long long status)
{
	if ((status > 255))
	{
		while (status > 255)
			status = status -256;
		exit(status);
	}
	else if ((status < -255) && status != -9223372036854775807)
		exit(status >> 8);
	else
		exit(status);
	return (status);
}
