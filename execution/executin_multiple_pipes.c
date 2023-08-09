/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_multiple_pipes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:34:17 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 09:29:12 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_function_part_1(char **envp, char **command, char *x, t_env **envs)
{
	int		fd;

	if (opendir(command[0]))
	{
		write(2, command[0], ft_strlen(command[0]));
		write(2, ": is a directory\n", 17);
		exit_func(126, envs);
		exit(126);
	}
	fd = open(command[0], O_RDONLY, 0777);
	if (fd != -1)
	{
		close(fd);
		execve(x, command, envp);
		exit_func(0, envs);
		exit(0);
	}
}

void	exec_function_print_error(char *x, t_env **envs)
{
	perror(x);
	exit_func(127, envs);
	exit(127);
}

void	exec_function(char **envp, char **command, char *x, t_env **envs)
{
	int		flag;

	flag = 0;
	exec_function_part_1(envp, command, x, envs);
	if (!checking_path(command[0], envs, &flag, 0) && flag == 1)
	{
		write(2, x, ft_strlen(x));
		write(2, ": No such file or directory\n", \
		ft_strlen(": No such file or directory\n"));
		exit_func(127, envs);
		exit(127);
	}
	if (access((const char *)(checking_path(command[0], \
		envs, &flag, 0)), X_OK) != 0 && flag == 1)
	{
		exec_function_print_error(x, envs);
	}
	if (execve(checking_path(command[0], envs, &flag, 0), \
		command, envp) == -1)
	{
		write(2, x, ft_strlen(x));
		write(2, ": command not found\n", ft_strlen(": Command not found\n"));
		exit_func(127, envs);
		exit(127);
	}
}

void	shlvl_increment(t_env **envs)
{
	t_env	*tracker;
	int		shlvl;

	tracker = *envs;
	while (tracker)
	{
		if (!ft_strcmp(tracker->cmd, "SHLVL"))
		{
			free(tracker->str);
			shlvl = ft_atoi(tracker->str);
			shlvl++;
			tracker->str = ft_itoa(shlvl);
		}
		tracker = tracker->next;
	}
}

void	if_not_first_time(t_execution **exec_vars, int j)
{
	if ((*exec_vars)->infile != 0)
	{
		dup2((*exec_vars)->infile, 0);
		close((*exec_vars)->infile);
		(*exec_vars)->infile = 0;
	}
	else
		dup2((*exec_vars)->array[j - 1][0], 0);
	if ((*exec_vars)->outfile != 1)
	{
		dup2((*exec_vars)->outfile, 1);
		close((*exec_vars)->outfile);
		(*exec_vars)->outfile = 1;
	}
	else
		dup2((*exec_vars)->array[j][1], 1);
}

// t_list	*t_list_char_converter(char **splited_command)
// {
// 	t_list	*list;
// 	t_list	*head;
// 	t_list	*current;
// 	t_list	*new_node;
// 	int		i;

// 	head = NULL;
// 	i = 0;
// 	while (splited_command[i])
// 	{
// 		new_node = malloc(sizeof(t_list));
// 		new_node->str = ft_strdup(splited_command[i]);
// 		new_node->next = NULL;
// 		if (head == NULL)
// 		{
// 			head = new_node;
// 			current = new_node;
// 		}
// 		else
// 		{
// 			current->next = new_node;
// 			current = current->next;
// 		}
// 		i++;
// 	}
// 	list = head;
// 	return (list);
// }
