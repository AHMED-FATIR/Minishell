/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_util2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:38:52 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:27:37 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_first_time(t_execution **exec_vars, int j)
{
	(void)j;
	if ((*exec_vars)->infile != 0 && (*exec_vars)->infile != -1)
	{
		dup2((*exec_vars)->infile, 0);
		close((*exec_vars)->infile);
		(*exec_vars)->infile = 0;
	}
	if ((*exec_vars)->outfile != 1 && (*exec_vars)->outfile != -1)
	{
		dup2((*exec_vars)->outfile, 1);
		close((*exec_vars)->outfile);
		(*exec_vars)->outfile = 1;
	}
	else
		dup2((*exec_vars)->array[0][1], (*exec_vars)->outfile);
}

pid_t	while_finish(t_execution **exec_vars, int *j, \
	char **splited_command, pid_t fn)
{
	(*exec_vars)->array_of_pids[*j] = fn;
	(*exec_vars)->fd = *j;
	(*exec_vars)->outfile = 1;
	(*exec_vars)->infile = 0;
	(*j)++;
	ft_free(splited_command);
	return (fn);
}

t_list	**last_arg(t_list **arg, char **splited_command)
{
	int		i;

	i = 0;
	while ((*arg))
	{
		if (!ft_strcmp((*arg)->str, splited_command[0]))
			return (arg);
		*arg = (*arg)->next;
	}
	return (NULL);
}

int	splited_builting_functions(char **splited_command, t_env **envs, \
	t_list **arg, t_execution **exec_vars)
{
	char	*trash;

	trash = NULL;
	(void)arg;
	if (!splited_command[0])
	{
		write (2, "minishell: : command not found\n", 31);
		g_exit_status = 127;
		exit_func(g_exit_status, envs);
		return (1);
	}
	if (!ft_strcmp(splited_command[0], "exit"))
	{
		g_exit_status = exit_function(envs, splited_command);
		return (1);
	}
	if (ft_strlen(splited_command[0]) == ft_strlen("cd") && \
		!ft_strncmp(splited_command[0], "cd", ft_strlen("cd")))
		return (cd_function(splited_command, envs, exec_vars), 1);
	if (ft_strlen(splited_command[0]) == ft_strlen("pwd") && \
		!ft_strncmp(splited_command[0], "pwd", ft_strlen("pwd")))
		return (pwd((*exec_vars)->outfile, &trash), free(trash), 1);
	return (0);
}

int	splited_builting_functions2(char **splited_command, t_env **envs, \
	t_list **arg, t_execution **exec_vars)
{
	int		flag;

	flag = 0;
	if ((*exec_vars)->flag_)
		flag = export_unset(arg, envs, (*exec_vars)->outfile);
	else if (!(*exec_vars)->flag_)
		flag = export_unset(last_arg(arg, splited_command), \
			envs, (*exec_vars)->outfile);
	return (flag);
}
