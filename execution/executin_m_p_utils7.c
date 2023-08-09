/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_utils7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:46:33 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:29:01 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_exec_vars(t_execution **exec_vars)
{
	if ((*exec_vars)->command)
	{
		free((*exec_vars)->command);
		(*exec_vars)->command = NULL;
	}
}

void	init(t_execution **exec_vars, t_list **argv)
{
	declaration(argv, exec_vars);
	if (!sep_len(argv))
		(*exec_vars)->flag = 0;
}

void	outfile_infile_reset(t_execution **exec_vars)
{
	(*exec_vars)->infile = 0;
	(*exec_vars)->outfile = 1;
}

void	checking_if_pipe_exists(t_execution *exec_vars, \
	t_list **argv, int x, t_env **envs)
{
	t_list	*arg;

	arg = *argv;
	init(&exec_vars, argv);
	while (arg)
	{
		if_redirection_in_or_out(&arg, &exec_vars, envs);
		if_last(&arg, argv, &exec_vars, envs);
		if (arg->str[0] == '|' && arg->type == 2)
		{
			if (exec_vars->joined)
			{
				exec_vars->command = ft_strdup(exec_vars->joined);
				exec_vars->fd2 = while_loop_fork(argv, &exec_vars, &x, envs);
				free(exec_vars->joined);
				exec_vars->joined = NULL;
				if_exec_vars(&exec_vars);
			}
			else
				outfile_infile_reset(&exec_vars);
		}
		arg = arg->next;
	}
	ending(argv, &exec_vars, envs);
}

void	ending(t_list **argv, t_execution **exec_vars, t_env **envs)
{
	int		i;
	int		status;

	(*exec_vars)->flag_1 = 0;
	i = 0;
	while (i < sep_len(argv))
	{
		close((*exec_vars)->array[i][0]);
		close((*exec_vars)->array[i][1]);
		i++;
	}
	i = 0;
	while (i < sep_len(argv))
	{
		(*exec_vars)->flag_1 = 1;
		waitpid((*exec_vars)->array_of_pids[i++], NULL, 0);
	}
	if (waitpid((*exec_vars)->fd1, &status, 0) != -1)
	{
		g_exit_status = WEXITSTATUS(status);
		exit_func(g_exit_status, envs);
	}
	ft_reset_hdl();
	ending_2(argv, exec_vars, envs);
}
