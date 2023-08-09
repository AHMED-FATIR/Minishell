/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:12:54 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 09:05:22 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expo_exist_norm(char *str, t_env **env, int i)
{
	char	*c;
	t_env	*cur;

	cur = *env;
	if (i == 1)
	{
		if (str)
		{
			c = ft_strdup(cur->str);
			free(cur->str);
			cur->str = dupping(c, ft_strdup(str + 1));
		}
	}
	else if (i == 2)
	{
		free(cur->str);
		cur->str = ft_strdup(str + 1);
	}
	else if (i == 3)
	{
		cur->str = ft_strdup(str + 1);
		cur->v = 0;
	}
}

int	expo_exist(char *arg, int i, t_env **envs)
{
	t_env	*cur;
	char	*str;
	char	*s;

	s = ft_strndup(arg, 0, i);
	if (!ft_strcmp("_", s))
		return (free(s), 1);
	cur = *envs;
	while (cur != NULL)
	{
		if (!ft_strcmp(cur->cmd, s))
		{
			str = ft_strchr(arg, '=');
			if (*(str - 1) == '+')
				return (expo_exist_norm(str, &cur, 1), free(s), 1);
			else if (*(str - 1) != '+' && cur->v == 0)
				return (expo_exist_norm(str, &cur, 2), free(s), 1);
			else
				return (expo_exist_norm(str, &cur, 3), free(s), 1);
		}
		cur = cur->next;
	}
	return (free(s), 0);
}

int	export_valid(char *arg, t_env **envs)
{
	t_env	*en;
	int		i;

	i = 0;
	if (is_valide(arg) == 2)
		return (ft_export(arg, envs));
	if (!is_valide(arg))
		return (0);
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		i--;
	if (expo_exist(arg, i, envs))
		return (1);
	en = ft_cr_listt(ft_strndup(arg, 0, i), \
		ft_strndup(arg, i + 1, ft_strlen(arg)), 0);
	ft_add_endd(envs, en);
	return (1);
}

int	export_unset_to(t_list *arg, t_env **envs, int i)
{
	if (!arg->next)
		return (1);
	arg = arg->next;
	if (i == 1)
	{
		while (arg)
		{
			if (!unset(arg->str, envs))
				return (0);
			arg = arg->next;
		}
	}
	if (i == 2 && check_sep(arg))
	{
		while (arg)
		{
			if (is_sep(*arg->str, 1) && *arg->str != '|')
				break ;
			if (!export_valid(arg->str, envs))
				return (0);
			arg = arg->next;
		}
	}
	return (1);
}

int	export_unset(t_list **args, t_env **envs, int outfile)
{
	t_list	*arg;

	if (!args)
		return (3);
	arg = *args;
	if (arg && !ft_strcmp(arg->str, "unset"))
		return (export_unset_to(arg, envs, 1));
	else if (arg && arg->next && !is_sep(*arg->next->str, 1) \
		&& !ft_strcmp(arg->str, "export"))
		return (export_unset_to(arg, envs, 2));
	else if (arg && !ft_strcmp(arg->str, "export"))
		return (print_env_xp(*envs, outfile), 1);
	else if (arg && !ft_strcmp(arg->str, "env"))
		return (check_path(envs, outfile));
	return (3);
}
