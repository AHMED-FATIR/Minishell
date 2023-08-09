/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:47:01 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 09:05:30 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reset_env(t_env **envs)
{
	t_env	*cur;
	t_env	*tmp;
	char	*p;
	char	path[1024];

	p = ft_strdup("");
	cur = *envs;
	while (cur)
	{
		if (!ft_strcmp(cur->cmd, "OLDPWD"))
		{
			free(cur->str);
			cur->str = ft_strdup(getcwd(path, sizeof(path)));
			return ;
		}
		cur = cur->next;
	}
	tmp = ft_cr_listt(ft_strdup("OLDPWD"), \
		ft_strdup(getcwd(path, sizeof(path))), 0);
	ft_add_endd(envs, tmp);
}

void	rm_node(t_env **envs)
{
	t_env	*head;
	t_env	*tmp;

	head = *envs;
	while (head)
	{
		if (!ft_strcmp(head->cmd, "OLDPWD"))
		{
			tmp = head;
			head = head->next;
			tmp->next = NULL;
			free_listt(&tmp);
			return ;
		}
		head = head->next;
	}
}
