/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:48:03 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 08:53:02 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
}

void	cd_error(char **splited_command, t_env **envs, int i)
{
	g_exit_status = 1;
	exit_func(g_exit_status, envs);
	perror(splited_command[i + 1]);
}

int	cd_function_if(char **splited_command, t_env **envs,
	t_execution **exec_vars)
{
	(*exec_vars)->j_cd = 0;
	(*exec_vars)->i_cd = 0;
	if (splited_command[(*exec_vars)->i_cd + 1][1] == '.'
		&& !splited_command[(*exec_vars)->i_cd + 1][2])
	{
		while ((*exec_vars)->splited_old_pwd[(*exec_vars)->j_cd])
		{
			if (!(*exec_vars)->splited_old_pwd[(*exec_vars)->j_cd + 1])
				break ;
			if ((*exec_vars)->j_cd == 0)
				(*exec_vars)->new_pwd = ft_strdup("");
			(*exec_vars)->new_pwd = ft_strjoin((*exec_vars)->new_pwd, "/");
			(*exec_vars)->new_pwd = ft_strjoin((*exec_vars)->new_pwd,
					(*exec_vars)->splited_old_pwd[(*exec_vars)->j_cd]);
			(*exec_vars)->j_cd++;
		}
		if (chdir(splited_command[(*exec_vars)->i_cd + 1]) == -1)
			cd_error(splited_command, envs, (*exec_vars)->i_cd);
	}
	else
	{
		if (chdir(splited_command[(*exec_vars)->i_cd + 1]) == -1)
			cd_error(splited_command, envs, (*exec_vars)->i_cd);
	}
	return ((*exec_vars)->i_cd);
}

void	cd_function_else(char **splited_command,
	t_env **envs, t_execution **exec_vars, int i)
{
	if (splited_command[i + 1])
	{
		if (chdir(splited_command[i + 1]) == -1)
			cd_error(splited_command, envs, i);
	}
	else
	{
		if (!(*exec_vars)->head_cd)
		{
			write(2, "cd: Home: Not set\n", 18);
			g_exit_status = 1;
			exit_func(g_exit_status, envs);
		}
		else if (ft_strlen((*exec_vars)->head_cd->str)
			&& chdir((*exec_vars)->head_cd->str) == -1)
		{
			g_exit_status = 1;
			exit_func(g_exit_status, envs);
			perror("lol");
		}
	}
}

void	cd_function(char **splited_command,
	t_env **envs, t_execution **exec_vars)
{
	int			j;
	int			i;

	(*exec_vars)->head_cd = *envs;
	while ((*exec_vars)->head_cd)
	{
		if (!ft_strcmp((*exec_vars)->head_cd->cmd, "HOME"))
			break ;
		(*exec_vars)->head_cd = (*exec_vars)->head_cd->next;
	}
	pwd(-1, &(*exec_vars)->current_pwd);
	(*exec_vars)->splited_old_pwd = ft_split((*exec_vars)->current_pwd, '/');
	(*exec_vars)->new_pwd = NULL;
	i = 0;
	j = 0;
	if (splited_command[i + 1] && splited_command[i + 1][0] == '.')
		i = cd_function_if(splited_command, envs, exec_vars);
	else
		cd_function_else(splited_command, envs, exec_vars, i);
	if ((*exec_vars)->new_pwd)
		free((*exec_vars)->new_pwd);
	free((*exec_vars)->current_pwd);
	ft_free((*exec_vars)->splited_old_pwd);
}
