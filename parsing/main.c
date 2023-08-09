/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:11:23 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 10:04:11 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eof_handling(char *cmd)
{
	if (!cmd)
	{
		write(1, "\033[1;32mexit\n", 12);
		exit(0);
	}
}

void	free_t_lst(t_list **list)
{
	if (!(*list))
		return ;
	if ((*list)->next)
		free_t_lst(&(*list)->next);
	free((*list)->str);
	free(*list);
	*list = NULL;
}

void	parsing(t_list *arg, t_env **envs, char **env)
{
	char		*cmd;

	arg = NULL;
	while (1)
	{
		cmd = readline("\033[1;34mminishell$\033[0m ");
		eof_handling(cmd);
		add_history(cmd);
		if (!token(env, cmd, &arg, envs))
		{
			ft_putstr_fd("\033[1;31mminishell$: syntax error\033[0m\n", 2);
			exit_func(2, envs);
		}
		free(cmd);
		free_t_lst(&arg);
	}
	free_listt(envs);
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_list	arg;
	char	**s;
	t_env	*envs;

	(void)ac;
	(void)av;
	envs = NULL;
	ft_reset_hdl();
	s = get_new_env(env);
	envs = get_env(s, envs);
	parsing(&arg, &envs, s);
	return (0);
}
