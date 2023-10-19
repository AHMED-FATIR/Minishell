/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:28:57 by afatir            #+#    #+#             */
/*   Updated: 2023/10/19 11:22:26 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int i)
{
	(void)i;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_reset_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_reset_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_reset_hdl(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
