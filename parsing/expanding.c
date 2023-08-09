/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:19 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 09:33:31 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_free_expand(t_var *v)
{
	char	*cmd;

	cmd = ft_strdup(v->c);
	free(v->c);
	free(v);
	return (cmd);
}

char	*expander(char *cmd, t_env **env)
{
	int		i;
	t_var	*v;

	i = 0;
	v = (t_var *)malloc(sizeof(t_var));
	v->c = ft_strdup("");
	v->k = ft_strlen(cmd);
	while (i < v->k)
	{
		if (cmd[i] && is_sep(cmd[i], 2))
			i = sep_case(cmd, i, v, env);
		else
			i = else_case(cmd, i, v, env);
		i++;
	}
	return (ft_free_expand(v));
}

int	expandable_in_herdoc(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_sep(str[i], 2))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_heredoc(t_list *arg)
{
	t_list	*cur;

	cur = arg;
	while (cur)
	{
		if (!ft_strcmp(cur->str, "<<") && cur->type == 2 \
			&& cur->next->type != DEL)
		{
			if (expandable_in_herdoc(cur->next->str))
				cur->next->type = 5;
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

void	expanding(t_list **arg, t_env **envs)
{
	int		i;
	t_list	*cur;
	char	*p;

	i = 0;
	p = NULL;
	cur = *arg;
	if (!ft_check_heredoc(*arg))
		return ;
	while (cur != NULL)
	{
		while (cur->str[i])
		{
			if (cur->str[i++] == '$')
			{
				p = expander(cur->str, envs);
				free(cur->str);
				cur->str = ft_strdup(p);
				free(p);
				break ;
			}
		}
		i = 0;
		cur = cur->next;
	}
}
