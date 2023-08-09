/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:03:10 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:29:30 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_function(char **splited_command, t_list *arg,
	int outfile, t_env **envs)
{
	int		new_line_flag;
	t_list	*temp_arg;

	temp_arg = arg;
	(void)splited_command;
	new_line_flag = 0;
	if (!temp_arg->next)
	{
		write(outfile, "\n", 1);
		return ;
	}
	temp_arg = temp_arg->next;
	if (temp_arg)
		while_temp_arg(&temp_arg, outfile, envs, &new_line_flag);
	if_temp_arg2(&temp_arg, outfile, envs, new_line_flag);
}

void	while_temp_arg(t_list **temp_arg, int outfile,
	t_env **envs, int *new_line_flag)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	(void)outfile;
	(void)envs;
	while ((*temp_arg) && (*temp_arg)->str[0] == '-'
		&& (*temp_arg)->str[1] == 'n')
	{
		j = 1;
		while ((*temp_arg)->str[j] == 'n')
		{
			j++;
		}
		if ((*temp_arg)->str[j] && (*temp_arg)->str[j] != 'n')
			break ;
		if (!(*temp_arg)->str[j])
		{
			*new_line_flag = 1;
		}
		(*temp_arg) = (*temp_arg)->next;
	}
}

void	if_temp_arg2(t_list **temp_arg, int outfile,
	t_env **envs, int new_line_flag)
{
	if ((*temp_arg))
	{
		while ((*temp_arg))
		{
			if ((*temp_arg)->type == 2)
				break ;
			if ((*temp_arg)->str[0] == '~' && !(*temp_arg)->str[1])
			{
				(*temp_arg)->str = get_env_str(ft_strdup("HOME"), envs);
			}
			write(outfile, (*temp_arg)->str, ft_strlen((*temp_arg)->str));
			if ((*temp_arg)->next && (*temp_arg)->next->type != 2)
				write(outfile, " ", 1);
			(*temp_arg) = (*temp_arg)->next;
		}
		if (!new_line_flag)
			write(outfile, "\n", 1);
	}
}
