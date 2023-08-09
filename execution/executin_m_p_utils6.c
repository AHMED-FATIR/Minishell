/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_utils6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:45:45 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:30:02 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_redirection_in(t_list **arg, t_execution **exec_vars, t_env **envs)
{
	if ((*arg)->str[1] == '<')
	{
		(*exec_vars)->infile = heredoc_func((*exec_vars)->envp, \
			(*arg)->next, exec_vars, envs);
		if ((*exec_vars)->infile == -1)
			return ;
		(*arg) = (*arg)->next;
	}
	else
	{
		(*exec_vars)->infile = redirection_in_fork((*exec_vars)->envp, (*arg));
		(*arg) = (*arg)->next;
	}
}

void	if_redirection_out(t_list **arg, t_execution **exec_vars)
{
	if ((*arg)->str[1] == '>')
	{
		(*exec_vars)->outfile = append((*exec_vars)->envp, (*arg));
		(*arg) = (*arg)->next;
	}
	else
	{
		(*exec_vars)->outfile = \
			redirection_out_fork((*exec_vars)->envp, (*arg));
		if ((*arg)->next)
			(*arg) = (*arg)->next;
	}
}

void	if_last(t_list **arg, t_list **argv, \
	t_execution **exec_vars, t_env **envs)
{
	if (!(*arg)->next)
	{
		if ((*exec_vars)->joined)
		{
			(*exec_vars)->command = ft_strdup((*exec_vars)->joined);
			(*exec_vars)->fd1 = bonus_child_fork_1(argv, exec_vars, envs);
			free((*exec_vars)->joined);
			free((*exec_vars)->command);
			(*exec_vars)->command = NULL;
			(*exec_vars)->joined = NULL;
		}
	}
}

void	declaration(t_list **argv, t_execution **exec_vars)
{
	if (sep_len(argv) > 0)
		(*exec_vars)->array_of_pids = creating_array_of_fds(argv);
	(*exec_vars)->joined = NULL;
	(*exec_vars)->command = NULL;
	(*exec_vars)->flag = 1;
	(*exec_vars)->fd = -1;
	(*exec_vars)->infile = 0;
	(*exec_vars)->outfile = 1;
}

void	if_redirection_in_or_out(t_list **arg, \
	t_execution **exec_vars, t_env **envs)
{
	if (((*arg)->str[0] == '<' || (*arg)->str[0] == '>') && ((*arg)->type == 2))
	{
		if ((*arg)->str[0] == '<')
			if_redirection_in(&(*arg), exec_vars, envs);
		else
			if_redirection_out(&(*arg), exec_vars);
	}
	else if ((*arg)->type != 2)
	{
		if ((*exec_vars)->joined == NULL)
			(*exec_vars)->joined = ft_strdup((*arg)->str);
		else
		{
			(*exec_vars)->joined = ft_strjoin((*exec_vars)->joined, " ");
			(*exec_vars)->joined = ft_strjoin((*exec_vars)->joined, \
				(*arg)->str);
		}
	}
}
