/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:44:49 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 10:04:57 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_list *list, char *cmd)
{
	t_list	*tmp;
	t_list	*tmp1;

	if (cmd)
		free(cmd);
	if (list)
	{
		tmp = list;
		while (tmp != NULL)
		{
			tmp1 = tmp->next;
			free(tmp->str);
			free(tmp);
			tmp = tmp1;
		}
	}
}

t_list	*ft_cr_list(char *cmd)
{
	t_list	*s;

	s = (t_list *)malloc(sizeof(t_list));
	if (!s || !*cmd)
		return (NULL);
	s->str = ft_strdup(cmd);
	s->next = NULL;
	free(cmd);
	return (s);
}

void	ft_add_end(t_list **a, t_list *n)
{
	t_list	*tmp;

	tmp = *a;
	if (*a == NULL)
	{
		*a = n;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = n;
}

int	ft_strlen_stack(t_list **a)
{
	t_list	*tmp;
	int		ln;

	ln = 0;
	tmp = *a;
	while (tmp != NULL)
	{
		ln++;
		tmp = tmp->next;
	}
	return (ln);
}
