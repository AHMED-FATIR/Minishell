/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:56:50 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 09:05:15 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_fill_env(void)
{
	char	**env;
	char	path[1024];

	env = ft_calloc(sizeof(char *), 5);
	env[0] = ft_strdup("PWD=");
	env[0] = dupping(env[0], ft_strdup(getcwd(path, sizeof(path))));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	env[3] = ft_strdup("_=/usr/bin/env");
	return (env);
}

void	free_listt(t_env **list)
{
	t_env	*tmp;
	t_env	*tmp1;

	if (list)
	{
		tmp = *list;
		while (tmp != NULL)
		{
			tmp1 = tmp->next;
			free(tmp->cmd);
			free(tmp->str);
			free(tmp);
			tmp = tmp1;
		}
		tmp = NULL;
	}
}

t_env	*ft_cr_listt(char *cmd, char *str, int i)
{
	t_env	*s;

	s = (t_env *)malloc(sizeof(t_env));
	if (!s)
		return (NULL);
	s->cmd = cmd;
	if (!str)
		s->str = NULL;
	else
		s->str = str;
	s->v = i;
	s->next = NULL;
	return (s);
}

void	ft_add_endd(t_env **a, t_env *n)
{
	t_env	*tmp;

	tmp = *a;
	if (*a == NULL)
	{
		*a = n;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = n;
}

t_env	*get_env(char **env, t_env *envs)
{
	t_env	*en;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (env[i])
	{
		j = 0;
		k = j;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				en = ft_cr_listt(ft_strndup(env[i], k, j), \
					ft_strndup(env[i], j + 1, ft_strlen(env[i])), 0);
				ft_add_endd(&envs, en);
				break ;
			}
			j++;
		}
		i++;
	}
	en = ft_cr_listt(ft_strdup("?"), ft_itoa(0), 1);
	return (ft_add_endd(&envs, en), envs);
}
