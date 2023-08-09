/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:41:51 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:28:06 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checking_builting_functions(char **splited_command, t_env **envs, \
	t_list **arg, t_execution **exec_vars)
{
	int		flag;

	if (splited_builting_functions(splited_command, envs, arg, exec_vars) == 1)
		return (1);
	if (ft_strlen(splited_command[0]) == ft_strlen("echo") && \
		!ft_strncmp(splited_command[0], "echo", ft_strlen("echo")))
	{
		echo_function(splited_command, *arg, (*exec_vars)->outfile, envs);
		(*exec_vars)->outfile = 1;
		return (1);
	}
	flag = splited_builting_functions2(splited_command, envs, arg, exec_vars);
	if (flag == 1)
		return (1);
	else if (flag == 0)
	{
		exit_func(1, envs);
		return (ft_putstr_fd("\033[1;31mminishell$: not a \
			valid identifier\033[0m\n", 2), 1);
	}
	else
		return (0);
}

void	child_fork_if(t_execution **exec_vars, t_env **env, t_list **arg, int i)
{
	(void)env;
	ft_reset_dfl();
	if ((*exec_vars)->infile != 0)
	{
		dup2((*exec_vars)->infile, 0);
		close((*exec_vars)->infile);
	}
	else if ((*exec_vars)->fd != -1)
		dup2((*exec_vars)->array[(*exec_vars)->fd][0], 0);
	if ((*exec_vars)->outfile != 1)
	{
		dup2((*exec_vars)->outfile, 1);
		close((*exec_vars)->outfile);
	}
	if ((*exec_vars)->outfile == -1)
		exit(1);
	else if ((*exec_vars)->infile == 0 && (*exec_vars)->fd == -1)
		dup2((*exec_vars)->array[0][0], 0);
	while (i < sep_len(arg))
	{
		close((*exec_vars)->array[i][0]);
		close((*exec_vars)->array[i][1]);
		i++;
	}
}

char	**child_fork_init(t_execution **exec_vars, t_env **envs)
{
	char	**splited_command;

	splited_command = NULL;
	splited_command = ft_split((*exec_vars)->command, ' ');
	if ((*exec_vars)->fd == -1)
	{
		(*exec_vars)->flag_ = 0;
		(*exec_vars)->f = checking_builting_functions(splited_command, envs, \
			&(*exec_vars)->head, exec_vars);
	}
	return (splited_command);
}

pid_t	bonus_child_fork_1(t_list **arg, t_execution **exec_vars, t_env **envs)
{
	pid_t	f1;
	char	**splited_command;

	(*exec_vars)->head = *arg;
	(*exec_vars)->f = 0;
	splited_command = child_fork_init(exec_vars, envs);
	if ((*exec_vars)->f != 0)
		return (ft_free(splited_command), -1);
	ft_reset_ign();
	f1 = fork();
	if (f1 == 0)
	{
		child_fork_if(exec_vars, envs, arg, 0);
		if (!ft_strcmp(splited_command[0], "./minishell"))
		{
			shlvl_increment(envs);
			parsing(*arg, envs, (*exec_vars)->envp);
		}
		else
			exec_function((*exec_vars)->envp, splited_command, \
				splited_command[0], envs);
	}
	return (ft_free(splited_command), f1);
}

int	**handling_multiple_pipes(t_list **arg)
{
	int	number_of_pipes;
	int	**array_of_pipes;
	int	i;	

	if (!sep_len(arg))
	{
		number_of_pipes = 1;
	}
	else
		number_of_pipes = sep_len(arg);
	i = 0;
	array_of_pipes = malloc(sizeof(int *) * (number_of_pipes));
	while (i < number_of_pipes)
	{
		array_of_pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (array_of_pipes);
}
