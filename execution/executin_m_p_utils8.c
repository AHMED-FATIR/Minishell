/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_utils8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:51:27 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 08:46:36 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ending_2(t_list **argv, t_execution **exec_vars, t_env **envs)
{
	int		i;

	(void)envs;
	if (sep_len(argv) == 0)
		free((*exec_vars)->array[0]);
	else
	{
		i = 0;
		while (i < sep_len(argv))
			free((*exec_vars)->array[i++]);
	}
	if ((*exec_vars)->array)
		free((*exec_vars)->array);
	if ((*exec_vars)->flag_1 == 1)
	{
		free((*exec_vars)->array_of_pids);
	}
	if (*exec_vars)
		free((*exec_vars));
}
