/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:59:23 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 09:33:54 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_qoute(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] && !is_sep(cmd[i], 2))
		i++;
	return (i);
}

char	*resize(char *cmd, int i, int b)
{
	char	*f;
	char	*l;

	i = first_qoute(cmd);
	f = ft_strndup(cmd, b, i);
	while (cmd[i])
	{
		if (cmd[i] && is_sep(cmd[i], 2))
		{
			b = i;
			i = get_index(i, cmd);
			l = ft_strndup(cmd, b + 1, i);
			f = dupping(f, l);
			i++;
		}
		if (cmd[i] && !is_sep(cmd[i], 2))
		{
			b = i;
			while (cmd[i] && !is_sep(cmd[i], 2))
				i++;
			l = ft_strndup(cmd, b, i);
			f = dupping(f, l);
		}
	}
	return (f);
}

void	quote_rm(t_list **arg)
{
	int		i;
	t_list	*cur;
	char	*p;

	i = 0;
	p = NULL;
	cur = *arg;
	while (cur != NULL)
	{
		while (cur->str[i])
		{
			if (is_sep(cur->str[i], 2))
			{
				p = resize(cur->str, 0, 0);
				free(cur->str);
				cur->str = ft_strdup(p);
				free(p);
				break ;
			}
			i++;
		}
		i = 0;
		cur = cur->next;
	}
}

int	quote_num(char *cmd, int flag)
{
	int		j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\"')
		{
			flag = 0;
			j = get_index(j, cmd);
			if (cmd[j] && cmd[j] == '\"')
				flag = 1;
		}
		if (cmd[j] == '\'')
		{
			flag = 0;
			j = get_index(j, cmd);
			if (cmd[j] && cmd[j] == '\'')
				flag = 1;
		}
		if (cmd[j])
			j++;
	}
	if (!flag)
		return (0);
	return (1);
}

int	check_nodes(t_list *arg)
{
	t_list	*cur;
	int		i;

	cur = arg;
	while (cur != NULL)
	{
		i = 0;
		while (cur->str[i])
		{
			if (is_sep(cur->str[i], 2))
			{
				if (!quote_num(cur->str, 0))
					return (0);
			}
			i++;
		}
		cur = cur->next;
	}
	return (1);
}
