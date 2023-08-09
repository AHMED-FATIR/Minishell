/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:12:32 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 09:34:31 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_env *arg, int outfile)
{
	t_env	*current;

	if (arg)
	{
		current = arg;
		while (current)
		{
			if (!current->v)
			{
				ft_putstr_fd(current->cmd, outfile);
				write(outfile, "=", 1);
				ft_putstr_fd(current->str, outfile);
				write(outfile, "\n", 1);
			}
			current = current->next;
		}
	}
}

void	print_env_xp(t_env *arg, int outfile)
{
	t_env	*current;

	current = arg;
	while (current)
	{
		if (!ft_strcmp(current->cmd, "?"))
			;
		else if (!current->v)
		{
			write(outfile, "declare -x ", 11);
			ft_putstr_fd(current->cmd, outfile);
			write(outfile, "=\"", 2);
			ft_putstr_fd(current->str, outfile);
			write(outfile, "\"\n", 2);
		}
		else
		{
			write(outfile, "declare -x ", 11);
			ft_putstr_fd(current->cmd, outfile);
			write(outfile, "\n", 1);
		}
		current = current->next;
	}
}

int	is_valide(char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && (arg[i + 1] != '='))
			return (0);
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+')
			return (0);
		i++;
	}
	if (arg[i] == '\0')
		return (2);
	return (1);
}

int	ft_export(char *arg, t_env **envs)
{
	t_env	*en;
	t_env	*cur;

	cur = *envs;
	while (cur)
	{
		if (!ft_strcmp(cur->cmd, arg))
			return (1);
		cur = cur->next;
	}
	en = ft_cr_listt(ft_strdup(arg), NULL, 1);
	ft_add_endd(envs, en);
	return (1);
}

int	check_sep(t_list *arg)
{
	t_list	*cur;

	cur = arg;
	while (cur)
	{
		if (cur->type == SEP)
		{
			if (*cur->str == '|')
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}
