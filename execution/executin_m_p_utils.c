/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:18:11 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:27:50 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closing_array(t_execution **exec_vars, t_list **argv)
{
	int		i;

	i = 0;
	while (i < sep_len(argv))
	{
		close((*exec_vars)->array[i][0]);
		close((*exec_vars)->array[i][1]);
		i++;
	}
}

void	while_init(int *x, int *j)
{
	if (*x == 0)
	{
		*j = 0;
		*x = -1;
	}
}

void	if_minishell(t_env **envs, t_execution **exec_vars, t_list **argv)
{
	shlvl_increment(envs);
	parsing(*argv, envs, (*exec_vars)->envp);
}

pid_t	while_loop_fork(t_list **argv, \
	t_execution **exec_vars, int *x, t_env **envs)
{
	static int		j;
	char			**splited_command;

	while_init(x, &j);
	splited_command = ft_split((*exec_vars)->command, ' ');
	ft_reset_ign();
	(*exec_vars)->fn = fork();
	if ((*exec_vars)->fn == 0)
	{
		ft_reset_dfl();
		if (j != 0)
			if_not_first_time(exec_vars, j);
		else
			if_first_time(exec_vars, j);
		closing_array(exec_vars, argv);
		if (checking_builting_functions(splited_command, \
			envs, argv, exec_vars) == 1)
			exit(1);
		else if (!ft_strcmp(splited_command[0], "./minishell"))
			if_minishell(envs, exec_vars, argv);
		else
			exec_function((*exec_vars)->envp, \
				splited_command, splited_command[0], envs);
	}
	return (while_finish(exec_vars, &j, splited_command, (*exec_vars)->fn));
}
