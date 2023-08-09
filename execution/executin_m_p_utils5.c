/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_utils5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:44:55 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 08:46:27 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	detecting_space(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (is_sep(s[i++], 3))
			return (1);
	}
	return (0);
}

int	redirection_out_fork(char **envp, t_list *arg)
{
	int		fd;

	(void)envp;
	if (!arg->next || detecting_space(arg->next->str))
	{
		write(2, "ambiguous redirect\n", 19);
		return (-1);
	}
	fd = open(arg->next->str, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
	{
		perror(arg->next->str);
	}
	return (fd);
}

int	if_status_2(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	ft_reset_hdl();
	return (-1);
}

void	heredoc_loop(t_execution **exec_vars, t_list *delimiter, t_env **envs)
{
	((*exec_vars)->buffer) = readline("heredoc>");
	if (!((*exec_vars)->buffer))
		exit(0);
	if (!ft_strcmp(((*exec_vars)->buffer), delimiter->str))
	{
		free(((*exec_vars)->buffer));
		exit(0);
	}
	if (check_if_expandable((*exec_vars)->buffer) && delimiter->type == 5)
		(*exec_vars)->buffer = expander((*exec_vars)->buffer, envs);
	write((*exec_vars)->pips[1], ((*exec_vars)->buffer), \
		ft_strlen(((*exec_vars)->buffer)));
	write((*exec_vars)->pips[1], "\n", 1);
	free(((*exec_vars)->buffer));
}

int	heredoc_func(char *envp[], t_list *delimiter, \
	t_execution **exec_vars, t_env **envs)
{
	pid_t	pid;

	(void)envp;
	pipe((*exec_vars)->pips);
	ft_reset_ign();
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		ft_reset_dfl();
		close((*exec_vars)->pips[0]);
		while (1)
			heredoc_loop(exec_vars, delimiter, envs);
	}
	waitpid(pid, &(*exec_vars)->status, 0);
	close((*exec_vars)->pips[1]);
	if ((*exec_vars)->status == 2)
		return (if_status_2());
	ft_reset_hdl();
	return ((*exec_vars)->pips[0]);
}
