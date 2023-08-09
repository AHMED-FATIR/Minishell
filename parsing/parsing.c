/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:55:03 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 10:04:51 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_empty_nodes(t_list **args)
{
	t_list	*arg;
	t_list	*tmp;
	t_list	*prev;

	arg = *args;
	prev = NULL;
	while (arg)
	{
		if (*arg->str == '\0')
		{
			if (!prev)
				*args = (*args)->next;
			else
				prev->next = arg->next;
			tmp = arg;
			arg = arg->next;
			tmp->next = NULL;
			free_list(tmp, NULL);
		}
		else
		{
			prev = arg;
			arg = arg->next;
		}
	}
}

void	token_to(char *cmd, t_list **arg)
{
	int		i;
	int		k;

	i = 0;
	k = ft_strlen(cmd);
	while (i < k)
	{
		if (cmd[i] && is_sep(cmd[i], 3))
			i++;
		if (cmd[i] && is_sep(cmd[i], 1))
			i = handle_sep(arg, cmd, i);
		if (cmd[i] && is_sep(cmd[i], 2))
			i = handle_quote(arg, cmd, i);
		if (cmd[i] && not_sep(cmd[i]))
			i = is_char(arg, cmd, i);
	}
}

int	token(char **env, char *cmd, t_list **arg, t_env	**envs)
{
	char	*str;

	str = ft_strtrim(cmd, " ");
	token_to(str, arg);
	free(str);
	if (!check_nodes(*arg) || !check_syntax(arg))
		return (free_t_lst(arg), 0);
	expanding(arg, envs);
	quote_rm(arg);
	execution(env, *arg, envs);
	return (1);
}

void	execution(char **env, t_list *arg, t_env **envs)
{
	int			i;
	t_execution	*exec_vars;

	i = 0;
	exec_vars = malloc(sizeof(t_execution));
	exec_vars->array = handling_multiple_pipes(&arg);
	exec_vars->envp = env;
	while (i < sep_len(&arg))
	{
		if (pipe(exec_vars->array[i++]) == -1)
			exit(1);
	}
	checking_if_pipe_exists(exec_vars, &arg, 0, envs);
}
