/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_m_p_utils4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:43:46 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:28:22 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	freeying_command_array(char **command)
{
	int		i;

	i = 0;
	if (!command)
		return ;
	while (command[i])
		free(command[i++]);
}

int	sep_len(t_list **arg)
{
	t_list	*temp;
	int		counter;

	counter = 0;
	temp = *arg;
	while (temp)
	{
		if (temp->str[0] == '|' && ft_strlen(temp->str) == 1)
		{
			counter++;
		}
		temp = temp->next;
	}
	free(temp);
	return (counter);
}

pid_t	*creating_array_of_fds(t_list **argv)
{
	pid_t	*array;

	array = malloc(sizeof(pid_t) * sep_len(argv));
	return (array);
}

int	redirection_in_fork(char **envp, t_list *arg)
{
	int		fd;

	(void)envp;
	fd = open(arg->next->str, O_RDONLY, 0777);
	if (fd == -1)
	{
		perror(arg->next->str);
	}
	return (fd);
}

int	append(char **envp, t_list *arg)
{
	int		fd;

	(void)envp;
	fd = open(arg->next->str, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fd == -1)
	{
		perror(arg->next->str);
		exit(1);
	}
	return (fd);
}
