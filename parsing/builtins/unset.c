/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:24:58 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 09:05:34 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_func(int exit, t_env **envs)
{
	t_env	*cur;

	cur = *envs;
	while (cur)
	{
		if (!ft_strcmp(cur->cmd, "?"))
		{
			free(cur->str);
			cur->str = ft_itoa(exit);
			return ;
		}
		cur = cur->next;
	}
}

char	*get_env_str(char *cmd, t_env **env)
{
	t_env	*cur;
	char	*str;

	cur = *env;
	while (cur != NULL)
	{
		if (!ft_strcmp(cur->cmd, cmd))
		{
			str = ft_strdup(cur->str);
			return (free(cmd), str);
		}
		cur = cur->next;
	}
	return (free(cmd), NULL);
}

int	check_path(t_env **envs, int outfile)
{
	t_env	*cur;

	cur = *envs;
	while (cur)
	{
		if (!ft_strcmp(cur->cmd, "PATH"))
			return (print_env(*envs, outfile), 1);
		cur = cur->next;
	}
	ft_putstr_fd("env: or directory\n", 2);
	return (1);
}

int	is_valid_uns(char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset(char *arg, t_env **envs)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*prev;

	env = *envs;
	prev = NULL;
	if (!is_valid_uns(arg))
		return (0);
	while (env)
	{
		if (!ft_strcmp(arg, env->cmd))
		{
			if (!prev)
				*envs = (*envs)->next;
			else
				prev->next = env->next;
			tmp = env;
			env = env->next;
			tmp->next = NULL;
			return (free_listt(&tmp), 1);
		}
		prev = env;
		env = env->next;
	}
	return (1);
}
